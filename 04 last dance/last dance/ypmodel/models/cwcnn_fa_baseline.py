import torch.nn as nn


class FALayer(nn.Module):
    """Feature Augmentation Layer used by CWCNN-FA."""

    def __init__(self, channels, hidden=8):
        super().__init__()
        # 求一整段时间序列的平均值，这一个平均值代表通道的全局特征[batch_size,channels,time_step]变为[batch_size,channels，1]
        self.avg_pool = nn.AdaptiveAvgPool1d(1)
        # 生成注意力权重，对于每个样本，每个通道生成一个注意力权重
        self.fc = nn.Sequential(
            nn.Linear(channels, hidden, bias=False),
            nn.ReLU(inplace=True),
            nn.Linear(hidden, channels, bias=False),
            nn.Sigmoid(),  #每个通道权重压缩到[0,1]之间
        )
        # 给注意力层的两个全连接层设置合理的权重，让训练更稳定，容易收敛
        nn.init.xavier_uniform_(self.fc[0].weight, gain=1.0)
        nn.init.xavier_uniform_(self.fc[2].weight, gain=1.0)
    def forward(self, x):
        batch_size, channels, _ = x.size()
        #压缩时间维度，同时[batch_size,channels,time_step]变为[batch_size,channels],
        #每个通道在时间维度上的信息做了平均，得到一个整体的强度值（全局响应强度）
        # .(view)相当于展平操作，删掉最后一个没用的维度。作为全连接层的输入，全连接层的输入就需要展平嘛
        pooled = self.avg_pool(x).view(batch_size, channels) 
        attention = self.fc(pooled) #生成通道注意力权重
        enhancement = (attention + pooled).view(batch_size, channels, 1) #构造特征增强向量，重塑形状，每通道一个数
        return x * enhancement  #逐通道增强特征  原数据*增强向量


def depthwise_block(channels, kernel_size, padding):
    return nn.Sequential(
        nn.Conv1d(
            channels,
            channels,
            kernel_size=kernel_size,
            stride=1,
            padding=padding,
            groups=channels,
        ),
        nn.BatchNorm1d(channels),
        nn.ReLU(inplace=True),
    )


class CWCNNFABaseline(nn.Module):
    """Baseline CWCNN-FA for four-class multi-source robot fault diagnosis."""

    def __init__(self, input_channels=15, num_classes=4, dropout=0.0):
        super().__init__()
        # Sample-level fusion: x=[batch, 15, 50] combines odom, wheel speed,
        # IMU, and motor current in the same time window.
        # Channel-wise convolution keeps heterogeneous sensor channels separate
        # during early temporal feature extraction.
        self.conv1 = depthwise_block(input_channels, kernel_size=7, padding=3)
        self.fa = FALayer(input_channels, hidden=8)
        self.conv2 = depthwise_block(input_channels, kernel_size=3, padding=1)
        self.conv3 = depthwise_block(input_channels, kernel_size=3, padding=1)
        self.conv4 = depthwise_block(input_channels, kernel_size=3, padding=1)
        self.pool = nn.AdaptiveAvgPool1d(1)
        # The fully connected layers fuse learned multi-source features and
        # output raw logits for CrossEntropyLoss.
        self.classifier = nn.Sequential(
            nn.Linear(input_channels, input_channels * 4),
            nn.ReLU(inplace=True),
            nn.Dropout(float(dropout)) if dropout > 0 else nn.Identity(),
            nn.Linear(input_channels * 4, num_classes),
        )

    def forward(self, x):
        x = self.conv1(x)
        x = self.fa(x)
        x = self.conv2(x)
        x = self.conv3(x)
        x = self.conv4(x)
        # 首先对每个通道的时间步做自适应平均池化，结果是每个时间维度被压缩为1，这样子多出来一个没用的冗余维度
        # 后面的.squeeze（dim）是删除张量中维度为1的维度，相当于展平，把数据喂给后面的全连接层
        x = self.pool(x).squeeze(-1)  
        return self.classifier(x)
