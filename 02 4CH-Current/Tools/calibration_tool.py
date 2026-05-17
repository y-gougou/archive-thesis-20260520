#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
4通道电流传感器校准工具 - GUI版本
===================================

功能：
1. 图形化界面操作
2. 实时显示4通道电流数据
3. 选择要校准的通道
4. 采集校准数据点
5. 自动计算最佳GAIN和OFFSET参数
6. 生成C代码并复制到剪贴板

作者: 4CH-Current Project
日期: 2025-12-29
"""

import tkinter as tk
from tkinter import ttk, messagebox, scrolledtext
import serial
import serial.tools.list_ports
import threading
import time
import numpy as np
from dataclasses import dataclass
from typing import List, Tuple, Optional
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure


plt.rcParams['font.sans-serif'] = ['Microsoft YaHei', 'SimHei', 'Arial']
plt.rcParams['axes.unicode_minus'] = False
# ============================================================================
# 常量定义
# ============================================================================

CHANNEL_COUNT = 4
CHANNEL_NAMES = ["通道0 (PA0/M1)", "通道1 (PA1/M2)", "通道2 (PA4/M3)", "通道3 (PA5/M4)"]
DEFAULT_BAUDRATE = 115200
SAMPLE_COUNT = 20

# ============================================================================
# 数据结构
# ============================================================================

@dataclass
class CalibrationPoint:
    """单个校准点数据"""
    reference: float
    measured: float


class ChannelCalibration:
    """单个通道的校准数据"""
    def __init__(self, channel_id: int, channel_name: str):
        self.channel_id = channel_id
        self.channel_name = channel_name
        self.points: List[CalibrationPoint] = []
    
    def add_point(self, reference: float, measured: float):
        """添加校准点"""
        self.points.append(CalibrationPoint(reference, measured))
    
    def calculate_parameters(self) -> Tuple[float, float, float]:
        """计算GAIN和OFFSET参数"""
        if len(self.points) < 2:
            return 1.0, 0.0, 0.0
        
        measured = np.array([p.measured for p in self.points])
        reference = np.array([p.reference for p in self.points])
        
        A = np.vstack([measured, np.ones(len(measured))]).T
        gain, offset = np.linalg.lstsq(A, reference, rcond=None)[0]
        
        reference_pred = gain * measured + offset
        ss_res = np.sum((reference - reference_pred) ** 2)
        ss_tot = np.sum((reference - np.mean(reference)) ** 2)
        r_squared = 1 - (ss_res / ss_tot) if ss_tot != 0 else 1.0
        
        return gain, offset, r_squared


# ============================================================================
# 主GUI应用
# ============================================================================

class CalibrationToolGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("4通道电流传感器校准工具")
        self.root.geometry("1000x700")
        
        # 数据
        self.serial_port: Optional[serial.Serial] = None
        self.is_connected = False
        self.is_monitoring = False
        self.current_values = [0.0] * CHANNEL_COUNT
        self.selected_channels = []
        self.calibration_data = {}  # {channel_id: ChannelCalibration}
        
        # 创建UI
        self.create_widgets()
        
        # 监控线程
        self.monitor_thread = None
        
    def create_widgets(self):
        """创建UI组件"""
        # 创建主容器
        main_frame = ttk.Frame(self.root, padding="10")
        main_frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
        
        self.root.columnconfigure(0, weight=1)
        self.root.rowconfigure(0, weight=1)
        main_frame.columnconfigure(0, weight=1)
        main_frame.rowconfigure(2, weight=1)
        
        # ===== 1. 串口连接区域 =====
        conn_frame = ttk.LabelFrame(main_frame, text="串口连接", padding="10")
        conn_frame.grid(row=0, column=0, sticky=(tk.W, tk.E), pady=(0, 10))
        
        ttk.Label(conn_frame, text="串口:").grid(row=0, column=0, padx=5)
        self.port_combo = ttk.Combobox(conn_frame, width=30, state='readonly')
        self.port_combo.grid(row=0, column=1, padx=5)
        
        self.refresh_btn = ttk.Button(conn_frame, text="刷新", command=self.refresh_ports)
        self.refresh_btn.grid(row=0, column=2, padx=5)
        
        self.connect_btn = ttk.Button(conn_frame, text="连接", command=self.toggle_connection)
        self.connect_btn.grid(row=0, column=3, padx=5)
        
        self.status_label = ttk.Label(conn_frame, text="● 未连接", foreground="red")
        self.status_label.grid(row=0, column=4, padx=10)
        
        # ===== 2. 实时数据显示区域 =====
        data_frame = ttk.LabelFrame(main_frame, text="实时数据", padding="10")
        data_frame.grid(row=1, column=0, sticky=(tk.W, tk.E), pady=(0, 10))
        
        self.channel_labels = []
        self.channel_values = []
        self.channel_checks = []
        self.channel_vars = []
        
        for i in range(CHANNEL_COUNT):
            # 复选框
            var = tk.BooleanVar()
            check = ttk.Checkbutton(data_frame, text="", variable=var)
            check.grid(row=i, column=0, padx=5)
            self.channel_vars.append(var)
            self.channel_checks.append(check)
            
            # 通道名称
            label = ttk.Label(data_frame, text=CHANNEL_NAMES[i], width=20)
            label.grid(row=i, column=1, padx=5, sticky=tk.W)
            self.channel_labels.append(label)
            
            # 电流值
            value_label = ttk.Label(data_frame, text="0.000 A", width=15, 
                                   font=('Consolas', 12, 'bold'))
            value_label.grid(row=i, column=2, padx=5)
            self.channel_values.append(value_label)
        
        ttk.Label(data_frame, text="← 勾选要校准的通道", foreground="blue").grid(
            row=CHANNEL_COUNT, column=0, columnspan=3, pady=5)
        
        # ===== 3. 校准控制区域 =====
        control_frame = ttk.LabelFrame(main_frame, text="校准控制", padding="10")
        control_frame.grid(row=2, column=0, sticky=(tk.W, tk.E, tk.N, tk.S), pady=(0, 10))
        control_frame.columnconfigure(0, weight=1)
        control_frame.rowconfigure(1, weight=1)
        
        # 输入区
        input_frame = ttk.Frame(control_frame)
        input_frame.grid(row=0, column=0, sticky=(tk.W, tk.E), pady=(0, 5))
        
        ttk.Label(input_frame, text="参考电流 (A):").pack(side=tk.LEFT, padx=5)
        self.ref_entry = ttk.Entry(input_frame, width=15)
        self.ref_entry.pack(side=tk.LEFT, padx=5)
        
        self.add_point_btn = ttk.Button(input_frame, text="添加校准点", 
                                        command=self.add_calibration_point, state='disabled')
        self.add_point_btn.pack(side=tk.LEFT, padx=5)
        
        self.clear_btn = ttk.Button(input_frame, text="清除数据", 
                                    command=self.clear_calibration_data, state='disabled')
        self.clear_btn.pack(side=tk.LEFT, padx=5)
        
        self.calculate_btn = ttk.Button(input_frame, text="计算参数", 
                                        command=self.calculate_parameters, state='disabled')
        self.calculate_btn.pack(side=tk.LEFT, padx=5)
        
        # 数据点列表
        list_frame = ttk.Frame(control_frame)
        list_frame.grid(row=1, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
        list_frame.columnconfigure(0, weight=1)
        list_frame.rowconfigure(0, weight=1)
        
        self.data_text = scrolledtext.ScrolledText(list_frame, height=10, width=70, 
                                                   font=('Consolas', 9))
        self.data_text.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
        self.data_text.config(state='disabled')
        
        # ===== 4. 结果显示区域 =====
        result_frame = ttk.LabelFrame(main_frame, text="校准结果", padding="10")
        result_frame.grid(row=3, column=0, sticky=(tk.W, tk.E), pady=(0, 10))
        result_frame.columnconfigure(0, weight=1)
        
        self.result_text = scrolledtext.ScrolledText(result_frame, height=8, width=70,
                                                     font=('Consolas', 9))
        self.result_text.grid(row=0, column=0, sticky=(tk.W, tk.E))
        self.result_text.config(state='disabled')
        
        btn_frame = ttk.Frame(result_frame)
        btn_frame.grid(row=1, column=0, pady=5)
        
        self.copy_btn = ttk.Button(btn_frame, text="复制C代码", 
                                   command=self.copy_c_code, state='disabled')
        self.copy_btn.pack(side=tk.LEFT, padx=5)
        
        self.plot_btn = ttk.Button(btn_frame, text="显示曲线", 
                                   command=self.plot_calibration, state='disabled')
        self.plot_btn.pack(side=tk.LEFT, padx=5)
        
        # 初始刷新串口
        self.refresh_ports()
    
    def refresh_ports(self):
        """刷新串口列表"""
        ports = serial.tools.list_ports.comports()
        port_list = [f"{p.device} - {p.description}" for p in ports]
        self.port_combo['values'] = port_list
        if port_list:
            self.port_combo.current(0)
    
    def toggle_connection(self):
        """切换连接状态"""
        if self.is_connected:
            self.disconnect()
        else:
            self.connect()
    
    def connect(self):
        """连接串口"""
        selection = self.port_combo.get()
        if not selection:
            messagebox.showerror("错误", "请选择串口")
            return
        
        port = selection.split(' - ')[0]
        
        try:
            self.serial_port = serial.Serial(port, DEFAULT_BAUDRATE, timeout=1.0)
            time.sleep(0.5)
            self.serial_port.reset_input_buffer()
            
            self.is_connected = True
            self.connect_btn.config(text="断开")
            self.status_label.config(text="● 已连接", foreground="green")
            self.port_combo.config(state='disabled')
            self.refresh_btn.config(state='disabled')
            
            # 启动监控
            self.start_monitoring()
            
            # 启用控制按钮
            self.add_point_btn.config(state='normal')
            self.clear_btn.config(state='normal')
            self.calculate_btn.config(state='normal')
            
        except Exception as e:
            messagebox.showerror("连接失败", f"无法打开串口:\n{e}")
    
    def disconnect(self):
        """断开串口"""
        self.stop_monitoring()
        
        if self.serial_port:
            self.serial_port.close()
            self.serial_port = None
        
        self.is_connected = False
        self.connect_btn.config(text="连接")
        self.status_label.config(text="● 未连接", foreground="red")
        self.port_combo.config(state='readonly')
        self.refresh_btn.config(state='normal')
        
        # 禁用控制按钮
        self.add_point_btn.config(state='disabled')
        self.clear_btn.config(state='disabled')
        self.calculate_btn.config(state='disabled')
        
        # 清零显示
        for label in self.channel_values:
            label.config(text="0.000 A")
    
    def start_monitoring(self):
        """启动数据监控"""
        self.is_monitoring = True
        self.monitor_thread = threading.Thread(target=self.monitor_loop, daemon=True)
        self.monitor_thread.start()
    
    def stop_monitoring(self):
        """停止数据监控"""
        self.is_monitoring = False
        if self.monitor_thread:
            self.monitor_thread.join(timeout=2.0)
    
    def monitor_loop(self):
        """监控循环"""
        while self.is_monitoring and self.serial_port:
            try:
                line = self.serial_port.readline().decode('utf-8').strip()
                if line:
                    parts = line.split(',')
                    if len(parts) == CHANNEL_COUNT:
                        values = [float(x) for x in parts]
                        self.current_values = values
                        
                        # 更新UI（线程安全）
                        self.root.after(0, self.update_display, values)
            except:
                pass
            
            time.sleep(0.05)
    
    def update_display(self, values):
        """更新显示（在主线程中调用）"""
        for i, value in enumerate(values):
            self.channel_values[i].config(text=f"{value:.3f} A")
    
    def add_calibration_point(self):
        """添加校准点"""
        # 获取选中的通道
        selected = [i for i in range(CHANNEL_COUNT) if self.channel_vars[i].get()]
        
        if not selected:
            messagebox.showwarning("警告", "请先勾选要校准的通道！")
            return
        
        # 获取参考值
        try:
            ref_value = float(self.ref_entry.get())
        except ValueError:
            messagebox.showerror("错误", "请输入有效的参考电流值")
            return
        
        # 采集数据
        self.add_point_btn.config(state='disabled', text="采集中...")
        self.root.update()
        
        # 在后台线程采集
        def collect():
            samples = []
            while len(samples) < SAMPLE_COUNT:
                if len(self.current_values) == CHANNEL_COUNT:
                    samples.append(self.current_values.copy())
                time.sleep(0.01)
            
            avg_values = np.mean(samples, axis=0).tolist()
            
            # 添加到校准数据
            for ch_id in selected:
                if ch_id not in self.calibration_data:
                    self.calibration_data[ch_id] = ChannelCalibration(ch_id, CHANNEL_NAMES[ch_id])
                
                self.calibration_data[ch_id].add_point(ref_value, avg_values[ch_id])
            
            # 更新UI
            self.root.after(0, lambda: self.on_point_added(ref_value, avg_values, selected))
        
        threading.Thread(target=collect, daemon=True).start()
    
    def on_point_added(self, ref_value, measured_values, selected_channels):
        """采集点添加完成回调"""
        # 更新文本显示
        self.data_text.config(state='normal')
        self.data_text.insert(tk.END, f"\n参考值: {ref_value:.3f} A\n")
        for ch_id in selected_channels:
            self.data_text.insert(tk.END, 
                f"  {CHANNEL_NAMES[ch_id]}: {measured_values[ch_id]:.3f} A\n")
        self.data_text.see(tk.END)
        self.data_text.config(state='disabled')
        
        # 恢复按钮
        self.add_point_btn.config(state='normal', text="添加校准点")
        
        # 清空输入框
        self.ref_entry.delete(0, tk.END)
        
        messagebox.showinfo("成功", "校准点已添加！")
    
    def clear_calibration_data(self):
        """清除校准数据"""
        if messagebox.askyesno("确认", "确定要清除所有校准数据吗？"):
            self.calibration_data.clear()
            self.data_text.config(state='normal')
            self.data_text.delete(1.0, tk.END)
            self.data_text.config(state='disabled')
            
            self.result_text.config(state='normal')
            self.result_text.delete(1.0, tk.END)
            self.result_text.config(state='disabled')
            
            self.copy_btn.config(state='disabled')
            self.plot_btn.config(state='disabled')
    
    def calculate_parameters(self):
        """计算校准参数"""
        if not self.calibration_data:
            messagebox.showwarning("警告", "没有校准数据！")
            return
        
        # 检查数据点数量
        for ch_id, cal_data in self.calibration_data.items():
            if len(cal_data.points) < 2:
                messagebox.showwarning("警告", 
                    f"{CHANNEL_NAMES[ch_id]} 数据点不足（至少需要2个点）")
                return
        
        # 计算参数
        results = {}
        result_text = "=" * 60 + "\n"
        result_text += "校准结果\n"
        result_text += "=" * 60 + "\n\n"
        
        for ch_id, cal_data in self.calibration_data.items():
            gain, offset, r2 = cal_data.calculate_parameters()
            results[ch_id] = (gain, offset, r2)
            
            result_text += f"{cal_data.channel_name}:\n"
            result_text += f"  数据点数: {len(cal_data.points)}\n"
            result_text += f"  GAIN:     {gain:.6f}\n"
            result_text += f"  OFFSET:   {offset:.6f} A\n"
            result_text += f"  R²:       {r2:.6f}\n"
            
            if r2 < 0.95:
                result_text += f"  ⚠️ 警告：拟合优度较低！\n"
            
            result_text += "\n"
        
        # 生成C代码
        result_text += "=" * 60 + "\n"
        result_text += "C代码（可直接粘贴到 current_types.h）\n"
        result_text += "=" * 60 + "\n\n"
        
        pins = ["PA0/M1", "PA1/M2", "PA4/M3", "PA5/M4"]
        
        for ch_id in range(CHANNEL_COUNT):
            if ch_id in results:
                gain, offset, _ = results[ch_id]
            else:
                gain, offset = 1.0, 0.0
            
            result_text += f"/** 通道{ch_id} ({pins[ch_id]}) 增益补偿 */\n"
            result_text += f"#define CAL_CH{ch_id}_GAIN                {gain:.6f}f\n"
            result_text += f"/** 通道{ch_id} ({pins[ch_id]}) 偏移补偿 (A) */\n"
            result_text += f"#define CAL_CH{ch_id}_OFFSET              {offset:.6f}f\n\n"
        
        # 未校准通道提示
        uncalibrated = [i for i in range(CHANNEL_COUNT) if i not in results]
        if uncalibrated:
            result_text += "\n⚠️ 未校准通道（使用默认值）:\n"
            for ch_id in uncalibrated:
                result_text += f"  - {CHANNEL_NAMES[ch_id]}\n"
        
        # 显示结果
        self.result_text.config(state='normal')
        self.result_text.delete(1.0, tk.END)
        self.result_text.insert(tk.END, result_text)
        self.result_text.config(state='disabled')
        
        # 启用按钮
        self.copy_btn.config(state='normal')
        self.plot_btn.config(state='normal')
        
        # 保存结果供复制
        self.latest_results = results
    
    def copy_c_code(self):
        """复制C代码到剪贴板"""
        # 提取C代码部分
        text = self.result_text.get(1.0, tk.END)
        
        # 找到C代码部分
        start_marker = "C代码（可直接粘贴到 current_types.h）"
        start_idx = text.find(start_marker)
        if start_idx == -1:
            return
        
        # 跳过分隔线
        code_start = text.find("#define", start_idx)
        if code_start == -1:
            return
        
        # 提取到末尾（去除警告部分）
        code_end = text.find("\n⚠️", code_start)
        if code_end != -1:
            c_code = text[code_start:code_end].strip()
        else:
            c_code = text[code_start:].strip()
        
        # 复制到剪贴板
        self.root.clipboard_clear()
        self.root.clipboard_append(c_code)
        
        messagebox.showinfo("成功", "C代码已复制到剪贴板！")
    
    def plot_calibration(self):
        """绘制校准曲线"""
        if not self.calibration_data:
            return
        
        # 创建新窗口
        plot_window = tk.Toplevel(self.root)
        plot_window.title("校准曲线")
        plot_window.geometry("900x700")
        
        # 创建图表
        fig = Figure(figsize=(9, 7))
        
        calibrated_channels = list(self.calibration_data.keys())
        num_channels = len(calibrated_channels)
        
        # 根据通道数决定布局
        if num_channels == 1:
            rows, cols = 1, 1
        elif num_channels == 2:
            rows, cols = 1, 2
        elif num_channels <= 4:
            rows, cols = 2, 2
        else:
            rows, cols = 2, 2
        
        for idx, ch_id in enumerate(calibrated_channels):
            cal_data = self.calibration_data[ch_id]
            
            if len(cal_data.points) < 2:
                continue
            
            ax = fig.add_subplot(rows, cols, idx + 1)
            
            # 数据
            measured = np.array([p.measured for p in cal_data.points])
            reference = np.array([p.reference for p in cal_data.points])
            
            # 拟合参数
            gain, offset, r2 = cal_data.calculate_parameters()
            
            # 绘图范围
            min_val = min(measured.min(), reference.min())
            max_val = max(measured.max(), reference.max())
            line_x = np.linspace(min_val, max_val, 100)
            
            # 理想线和拟合线
            ideal_y = line_x
            fit_y = gain * line_x + offset
            
            # 绘图
            ax.scatter(measured, reference, s=80, alpha=0.7, label='数据点', color='blue', zorder=3)
            ax.plot(line_x, ideal_y, '--', color='gray', linewidth=1.5, label='理想线 (y=x)', zorder=1)
            ax.plot(line_x, fit_y, '-', color='red', linewidth=2,
                   label=f'拟合: y={gain:.3f}x+{offset:.3f}\nR²={r2:.4f}', zorder=2)
            
            ax.set_xlabel('测量值 (A)', fontsize=10)
            ax.set_ylabel('参考值 (A)', fontsize=10)
            ax.set_title(cal_data.channel_name, fontsize=11, fontweight='bold')
            ax.legend(loc='best', fontsize=8)
            ax.grid(True, alpha=0.3)
            ax.axhline(0, color='black', linewidth=0.5)
            ax.axvline(0, color='black', linewidth=0.5)
        
        fig.suptitle('4通道电流传感器校准曲线', fontsize=14, fontweight='bold')
        fig.tight_layout()
        
        # 嵌入到窗口
        canvas = FigureCanvasTkAgg(fig, master=plot_window)
        canvas.draw()
        canvas.get_tk_widget().pack(fill=tk.BOTH, expand=True)
        
        # 保存按钮
        def save_plot():
            filename = f"calibration_curves_{time.strftime('%Y%m%d_%H%M%S')}.png"
            fig.savefig(filename, dpi=150, bbox_inches='tight')
            messagebox.showinfo("成功", f"图表已保存: {filename}")
        
        btn_frame = ttk.Frame(plot_window)
        btn_frame.pack(fill=tk.X, padx=10, pady=5)
        ttk.Button(btn_frame, text="保存图表", command=save_plot).pack(side=tk.LEFT, padx=5)
    
    def on_closing(self):
        """窗口关闭事件"""
        if self.is_connected:
            self.disconnect()
        self.root.destroy()


# ============================================================================
# 主程序
# ============================================================================

def main():
    root = tk.Tk()
    app = CalibrationToolGUI(root)
    root.protocol("WM_DELETE_WINDOW", app.on_closing)
    root.mainloop()


if __name__ == "__main__":
    main()
