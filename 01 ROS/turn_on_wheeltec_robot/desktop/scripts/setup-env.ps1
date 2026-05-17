param(
  [switch]$SkipSystemTools,
  [switch]$SkipNodeInstall,
  [switch]$SkipBundledPython,
  [switch]$SkipPythonDeps,
  [switch]$BuildInference,
  [switch]$OfflineInference,
  [switch]$CheckOnly,
  [switch]$Force,
  [switch]$UseSystemTools,
  [string]$PythonCommand = "python",
  [string]$PythonVenvDir = "",
  [string]$ToolchainDir = "",
  [string]$PipIndexUrl = "",
  [string[]]$ExtraPipArgs = @()
)

$ErrorActionPreference = "Stop"

$ProjectRoot = Resolve-Path (Join-Path $PSScriptRoot "..")
$DefaultToolchainDir = Join-Path $ProjectRoot ".toolchain"
$DefaultVenvDir = Join-Path $ProjectRoot "python"
if (-not $ToolchainDir) {
  $ToolchainDir = $DefaultToolchainDir
}
if (-not $PythonVenvDir) {
  $PythonVenvDir = $DefaultVenvDir
}
if ($CheckOnly) {
  $SkipSystemTools = $true
  $SkipNodeInstall = $true
  $SkipBundledPython = $true
  $SkipPythonDeps = $true
  $BuildInference = $false
}

$NodeVersion = "20.18.1"
$CMakeVersion = "3.28.1"
$NinjaVersion = "1.12.1"
$PythonVersion = "3.11.9"
$LlvmVersion = "18.1.8"
$script:NodeExe = ""
$script:NpmCmd = ""
$script:CMakeExe = ""
$script:NinjaExe = ""
$script:PythonExe = ""
$script:ClangExe = ""
$script:ClangxxExe = ""
$script:ClangClExe = ""
$script:LldExe = ""
$UvVersion = "0.11.11"
$script:UvExe = ""

function Write-Step {
  param([string]$Message)
  Write-Host ""
  Write-Host "==> $Message" -ForegroundColor Cyan
}

function Write-Ok {
  param([string]$Message)
  Write-Host "OK  $Message" -ForegroundColor Green
}

function Write-Warn {
  param([string]$Message)
  Write-Host "WARN $Message" -ForegroundColor Yellow
}

function Test-Command {
  param([string]$Name)
  $null -ne (Get-Command $Name -ErrorAction SilentlyContinue)
}

function Download-File {
  param(
    [string]$Url,
    [string]$Destination
  )
  if ((Test-Path $Destination) -and -not $Force) {
    Write-Ok "Using cached download: $Destination"
    return
  }
  New-Item -ItemType Directory -Force -Path (Split-Path $Destination -Parent) | Out-Null
  Write-Host ">> download $Url"
  $ProgressPreference = "SilentlyContinue"
  Invoke-WebRequest -Uri $Url -OutFile $Destination -UseBasicParsing
}

function Expand-Zip {
  param(
    [string]$Archive,
    [string]$Destination
  )
  if ((Test-Path $Destination) -and -not $Force) {
    Write-Ok "Using existing tool directory: $Destination"
    return
  }
  if (Test-Path $Destination) {
    Remove-Item -LiteralPath $Destination -Recurse -Force
  }
  New-Item -ItemType Directory -Force -Path $Destination | Out-Null
  Expand-Archive -LiteralPath $Archive -DestinationPath $Destination -Force
}

function Expand-ArchiveFile {
  param(
    [string]$Archive,
    [string]$Destination
  )
  if ((Test-Path $Destination) -and -not $Force) {
    Write-Ok "Using existing tool directory: $Destination"
    return
  }
  if (Test-Path $Destination) {
    Remove-Item -LiteralPath $Destination -Recurse -Force
  }
  New-Item -ItemType Directory -Force -Path $Destination | Out-Null
  if ($Archive.EndsWith(".zip")) {
    Expand-Archive -LiteralPath $Archive -DestinationPath $Destination -Force
    return
  }
  if ($Archive.EndsWith(".tar.xz") -or $Archive.EndsWith(".txz") -or $Archive.EndsWith(".tar.gz") -or $Archive.EndsWith(".tgz")) {
    & tar -xf $Archive -C $Destination
    if ($LASTEXITCODE -ne 0) {
      throw "Failed to extract archive: $Archive"
    }
    return
  }
  throw "Unsupported archive: $Archive"
}

function First-ExistingPath {
  param([string[]]$Paths)
  foreach ($candidate in $Paths) {
    if (Test-Path $candidate) {
      return $candidate
    }
  }
  return ""
}

function Wait-ForFile {
  param(
    [string]$Path,
    [int]$TimeoutSeconds = 90
  )
  $deadline = (Get-Date).AddSeconds($TimeoutSeconds)
  while ((Get-Date) -lt $deadline) {
    if (Test-Path $Path) {
      return $Path
    }
    Start-Sleep -Milliseconds 500
  }
  return ""
}

function Invoke-Checked {
  param(
    [string]$FilePath,
    [string[]]$Arguments,
    [string]$WorkingDirectory = $ProjectRoot
  )
  Write-Host ">> $FilePath $($Arguments -join ' ')"
  Push-Location $WorkingDirectory
  try {
    & $FilePath @Arguments
    $exitCode = if ($null -eq $LASTEXITCODE) { 0 } else { $LASTEXITCODE }
  } finally {
    Pop-Location
  }
  if ($exitCode -ne 0) {
    throw "Command failed with exit code ${exitCode}: $FilePath $($Arguments -join ' ')"
  }
}

function Install-WithWinget {
  param(
    [string]$PackageId,
    [string]$DisplayName,
    [string[]]$ExtraArgs = @()
  )

  if (-not (Test-Command "winget")) {
    throw "winget was not found. Install App Installer from Microsoft Store, then rerun this script."
  }

  Write-Step "Installing $DisplayName"
  $args = @(
    "install",
    "--id", $PackageId,
    "--exact",
    "--source", "winget",
    "--accept-package-agreements",
    "--accept-source-agreements"
  ) + $ExtraArgs
  Invoke-Checked "winget" $args
}

function Ensure-SystemTool {
  param(
    [string]$Command,
    [string]$PackageId,
    [string]$DisplayName,
    [string[]]$ExtraArgs = @()
  )

  if ((Test-Command $Command) -and -not $Force) {
    Write-Ok "$DisplayName already available: $Command"
    return
  }
  Install-WithWinget -PackageId $PackageId -DisplayName $DisplayName -ExtraArgs $ExtraArgs
}

function Ensure-LocalToolchain {
  Write-Step "Preparing project-local toolchain"
  $downloads = Join-Path $ToolchainDir "downloads"
  $nodeDir = Join-Path $ToolchainDir "node"
  $cmakeDir = Join-Path $ToolchainDir "cmake"
  $ninjaDir = Join-Path $ToolchainDir "ninja"
  $llvmDir = Join-Path $ToolchainDir "llvm"
  $uvDir = Join-Path $ToolchainDir "uv"
  $uvCacheDir = Join-Path $uvDir "cache"
  $uvPythonDir = Join-Path $uvDir "python"

  $nodeZip = Join-Path $downloads "node-v$NodeVersion-win-x64.zip"
  $cmakeZip = Join-Path $downloads "cmake-$CMakeVersion-windows-x86_64.zip"
  $ninjaZip = Join-Path $downloads "ninja-win-$NinjaVersion.zip"
  $llvmArchive = Join-Path $downloads "clang+llvm-$LlvmVersion-x86_64-pc-windows-msvc.tar.xz"
  $uvZip = Join-Path $downloads "uv-$UvVersion-x86_64-pc-windows-msvc.zip"

  Download-File "https://nodejs.org/dist/v$NodeVersion/node-v$NodeVersion-win-x64.zip" $nodeZip
  Expand-Zip $nodeZip $nodeDir
  $script:NodeExe = First-ExistingPath @(
    (Join-Path $nodeDir "node-v$NodeVersion-win-x64\node.exe")
  )
  $script:NpmCmd = First-ExistingPath @(
    (Join-Path $nodeDir "node-v$NodeVersion-win-x64\npm.cmd")
  )

  Download-File "https://github.com/Kitware/CMake/releases/download/v$CMakeVersion/cmake-$CMakeVersion-windows-x86_64.zip" $cmakeZip
  Expand-Zip $cmakeZip $cmakeDir
  $script:CMakeExe = First-ExistingPath @(
    (Join-Path $cmakeDir "cmake-$CMakeVersion-windows-x86_64\bin\cmake.exe")
  )

  Download-File "https://github.com/ninja-build/ninja/releases/download/v$NinjaVersion/ninja-win.zip" $ninjaZip
  Expand-Zip $ninjaZip $ninjaDir
  $script:NinjaExe = First-ExistingPath @(
    (Join-Path $ninjaDir "ninja.exe")
  )

  Download-File "https://github.com/llvm/llvm-project/releases/download/llvmorg-$LlvmVersion/clang+llvm-$LlvmVersion-x86_64-pc-windows-msvc.tar.xz" $llvmArchive
  Expand-ArchiveFile $llvmArchive $llvmDir
  $llvmBin = Join-Path $llvmDir "clang+llvm-$LlvmVersion-x86_64-pc-windows-msvc\bin"
  $script:ClangExe = First-ExistingPath @(
    (Join-Path $llvmBin "clang.exe")
  )
  $script:ClangxxExe = First-ExistingPath @(
    (Join-Path $llvmBin "clang++.exe")
  )
  $script:ClangClExe = First-ExistingPath @(
    (Join-Path $llvmBin "clang-cl.exe")
  )
  $script:LldExe = First-ExistingPath @(
    (Join-Path $llvmBin "lld.exe")
  )

  Download-File "https://github.com/astral-sh/uv/releases/download/$UvVersion/uv-x86_64-pc-windows-msvc.zip" $uvZip
  Expand-Zip $uvZip $uvDir
  $script:UvExe = First-ExistingPath @(
    (Join-Path $uvDir "uv.exe"),
    (Join-Path $uvDir "uv-x86_64-pc-windows-msvc\uv.exe")
  )

  New-Item -ItemType Directory -Force -Path $uvCacheDir, $uvPythonDir | Out-Null
  $env:UV_CACHE_DIR = $uvCacheDir
  $env:UV_PYTHON_INSTALL_DIR = $uvPythonDir
  $env:UV_NO_MODIFY_PATH = "1"
  if ($PipIndexUrl) {
    $env:UV_INDEX_URL = $PipIndexUrl
  }
  if ($script:UvExe) {
    Write-Step "Installing Python with uv"
    Invoke-Checked $script:UvExe @("python", "install", $PythonVersion)
  }

  $missing = @()
  if (-not $script:NodeExe) { $missing += "node" }
  if (-not $script:NpmCmd) { $missing += "npm" }
  if (-not $script:CMakeExe) { $missing += "cmake" }
  if (-not $script:NinjaExe) { $missing += "ninja" }
  if (-not $script:ClangExe) { $missing += "clang" }
  if (-not $script:ClangxxExe) { $missing += "clang++" }
  if (-not $script:ClangClExe) { $missing += "clang-cl" }
  if (-not $script:LldExe) { $missing += "lld" }
  if (-not $script:UvExe) { $missing += "uv" }
  if ($missing.Count -gt 0) {
    throw "Local toolchain is incomplete: $($missing -join ', ')"
  }

  $toolPath = @(
    (Split-Path $script:NodeExe -Parent),
    (Split-Path $script:CMakeExe -Parent),
    (Split-Path $script:NinjaExe -Parent),
    (Split-Path $script:ClangExe -Parent),
    (Split-Path $script:UvExe -Parent)
  ) -join [IO.Path]::PathSeparator
  $env:PATH = $toolPath + [IO.Path]::PathSeparator + $env:PATH
  Write-Ok "Local toolchain ready: $ToolchainDir"
}

function Resolve-Tool {
  param(
    [string]$LocalPath,
    [string]$Command
  )
  if ($LocalPath -and (Test-Path $LocalPath)) {
    return $LocalPath
  }
  return $Command
}

function Initialize-UvEnvironment {
  $uvDir = Join-Path $ToolchainDir "uv"
  if (-not $script:UvExe) {
    $script:UvExe = First-ExistingPath @(
      (Join-Path $uvDir "uv.exe"),
      (Join-Path $uvDir "uv-x86_64-pc-windows-msvc\uv.exe")
    )
  }

  $uvCacheDir = Join-Path $uvDir "cache"
  $uvPythonDir = Join-Path $uvDir "python"
  New-Item -ItemType Directory -Force -Path $uvCacheDir, $uvPythonDir | Out-Null
  $env:UV_CACHE_DIR = $uvCacheDir
  $env:UV_PYTHON_INSTALL_DIR = $uvPythonDir
  $env:UV_NO_MODIFY_PATH = "1"
  if ($PipIndexUrl) {
    $env:UV_INDEX_URL = $PipIndexUrl
  }
}

function Test-VsBuildTools {
  $pf86 = ${env:ProgramFiles(x86)}
  if (-not $pf86) {
    $pf86 = "C:\Program Files (x86)"
  }
  $vswhere = Join-Path $pf86 "Microsoft Visual Studio\Installer\vswhere.exe"
  if (-not (Test-Path $vswhere)) {
    return $false
  }

  $result = & $vswhere -latest -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
  return -not [string]::IsNullOrWhiteSpace(($result | Out-String).Trim())
}

function Ensure-VsBuildTools {
  if ((Test-VsBuildTools) -and -not $Force) {
    Write-Ok "Visual Studio C++ Build Tools already available"
    return
  }

  if (-not (Test-Command "winget")) {
    throw "winget was not found. Cannot install Visual Studio Build Tools automatically."
  }

  Write-Step "Installing Visual Studio Build Tools 2022 C++ workload"
  $override = "--quiet --wait --norestart --add Microsoft.VisualStudio.Workload.VCTools --includeRecommended"
  Invoke-Checked "winget" @(
    "install",
    "--id", "Microsoft.VisualStudio.2022.BuildTools",
    "--exact",
    "--source", "winget",
    "--accept-package-agreements",
    "--accept-source-agreements",
    "--override", $override
  )
}

function Get-VenvPython {
  if ($IsWindows -or $env:OS -eq "Windows_NT") {
    return Join-Path $PythonVenvDir "Scripts\python.exe"
  }
  return Join-Path $PythonVenvDir "bin/python3"
}

function Reset-PythonVenvDir {
  $readmePath = Join-Path $PythonVenvDir "README.md"
  $readmeBackup = Join-Path $ToolchainDir "python-README.md.tmp"
  if (Test-Path $readmePath) {
    New-Item -ItemType Directory -Force -Path $ToolchainDir | Out-Null
    Copy-Item -LiteralPath $readmePath -Destination $readmeBackup -Force
  }
  if (Test-Path $PythonVenvDir) {
    Remove-Item -LiteralPath $PythonVenvDir -Recurse -Force
  }
}

function Restore-PythonReadme {
  $readmePath = Join-Path $PythonVenvDir "README.md"
  $readmeBackup = Join-Path $ToolchainDir "python-README.md.tmp"
  if (Test-Path $readmeBackup) {
    Copy-Item -LiteralPath $readmeBackup -Destination $readmePath -Force
    Remove-Item -LiteralPath $readmeBackup -Force
  }
}

function Test-PythonVenvUsable {
  param([string]$VenvPython)
  $venvCfg = Join-Path $PythonVenvDir "pyvenv.cfg"
  if (-not (Test-Path $VenvPython) -or -not (Test-Path $venvCfg)) {
    return $false
  }

  $cfg = Get-Content -LiteralPath $venvCfg
  $executableLine = $cfg | Where-Object { $_ -match '^executable\s*=' } | Select-Object -First 1
  if ($executableLine) {
    $basePython = ($executableLine -replace '^executable\s*=\s*', '').Trim()
    if ($basePython -and -not (Test-Path $basePython)) {
      Write-Warn "Existing Python venv points to a missing base interpreter: $basePython"
      return $false
    }
  }

  return $true
}

function Ensure-NodeDeps {
  Write-Step "Installing Electron desktop dependencies"
  Invoke-Checked (Resolve-Tool $script:NpmCmd "npm") @("install")
}

function Ensure-PythonVenv {
  Initialize-UvEnvironment
  $venvPython = Get-VenvPython
  if ((Test-PythonVenvUsable -VenvPython $venvPython) -and -not $Force) {
    Write-Ok "uv-managed Python venv already exists: $venvPython"
  } else {
    Write-Step "Creating uv-managed Python venv"
    $uv = Resolve-Tool $script:UvExe "uv"
    if (-not (Test-Path $uv) -and -not (Test-Command $uv)) {
      throw "uv was not found"
    }
    Reset-PythonVenvDir
    Invoke-Checked $uv @("venv", "--python", $PythonVersion, $PythonVenvDir)
    Restore-PythonReadme
  }

  return $venvPython
}

function Install-PythonDeps {
  param([string]$VenvPython)

  Initialize-UvEnvironment
  Write-Step "Installing Python model export dependencies"
  $uv = Resolve-Tool $script:UvExe "uv"
  $pipArgs = @("pip", "install", "--python", $VenvPython, "--upgrade", "pip", "setuptools", "wheel")
  if ($PipIndexUrl) {
    $pipArgs += @("--index-url", $PipIndexUrl)
  }
  $pipArgs += $ExtraPipArgs
  Invoke-Checked $uv $pipArgs

  $deps = @("torch", "onnx", "joblib", "scikit-learn")
  $installArgs = @("pip", "install", "--python", $VenvPython) + $deps
  if ($PipIndexUrl) {
    $installArgs += @("--index-url", $PipIndexUrl)
  }
  $installArgs += $ExtraPipArgs
  Invoke-Checked $uv $installArgs
}

function Show-ToolVersions {
  Write-Step "Tool versions"
  foreach ($command in @("git", "node", "npm", "cmake", "ninja", "clang", "clang++", "clang-cl", "lld")) {
    $localPath = switch ($command) {
      "node" { $script:NodeExe }
      "npm" { $script:NpmCmd }
      "cmake" { $script:CMakeExe }
      "ninja" { $script:NinjaExe }
      "clang" { $script:ClangExe }
      "clang++" { $script:ClangxxExe }
      "clang-cl" { $script:ClangClExe }
      "lld" { $script:LldExe }
      default { "" }
    }
    $tool = Resolve-Tool $localPath $command
    if ((Test-Path $tool) -or (Test-Command $tool)) {
      try {
        & $tool --version | Select-Object -First 1
      } catch {
        Write-Warn "Could not read version for $command"
      }
    } else {
      Write-Warn "$command not found in PATH"
    }
  }

  $venvPython = Get-VenvPython
  if (Test-Path $venvPython) {
    & $venvPython --version
  }
  $uv = Resolve-Tool $script:UvExe "uv"
  if ((Test-Path $uv) -or (Test-Command $uv)) {
    & $uv --version
  }
}

Push-Location $ProjectRoot
try {
  if (-not $SkipSystemTools) {
    if ($UseSystemTools) {
      Write-Step "Checking system build tools"
      Ensure-SystemTool -Command "git" -PackageId "Git.Git" -DisplayName "Git"
      Ensure-SystemTool -Command "node" -PackageId "OpenJS.NodeJS.LTS" -DisplayName "Node.js LTS"
      Ensure-SystemTool -Command "python" -PackageId "Python.Python.3.11" -DisplayName "Python 3.11"
      Ensure-SystemTool -Command "cmake" -PackageId "Kitware.CMake" -DisplayName "CMake"
      Ensure-SystemTool -Command "ninja" -PackageId "Ninja-build.Ninja" -DisplayName "Ninja"
      Ensure-SystemTool -Command "clang" -PackageId "LLVM.LLVM" -DisplayName "LLVM/Clang"
      Ensure-VsBuildTools
      Write-Warn "If a tool was just installed, restart the terminal if PATH does not update immediately."
    } else {
      Ensure-LocalToolchain
      if (-not (Test-VsBuildTools)) {
        Write-Warn "LLVM/Clang is project-local. Real ONNX Runtime builds on Windows still need the Windows SDK/MSVC environment for the MSVC ABI, or use setup:env:offline-infer."
      }
    }
  }

  if (-not $SkipNodeInstall) {
    Ensure-NodeDeps
  }

  $venvPython = ""
  if (-not $SkipBundledPython) {
    $venvPython = Ensure-PythonVenv
    if (-not $SkipPythonDeps) {
      Install-PythonDeps -VenvPython $venvPython
    }
  }

  if ($BuildInference) {
    Write-Step "Building C++ inference runtime"
    if ($OfflineInference) {
      Invoke-Checked (Resolve-Tool $script:NpmCmd "npm") @("run", "build:infer:offline")
    } else {
      Invoke-Checked (Resolve-Tool $script:NpmCmd "npm") @("run", "build:infer")
    }
  }

  Show-ToolVersions
  Write-Step "Done"
  Write-Ok "Desktop build environment is ready."
  if ($venvPython) {
    Write-Ok "Bundled Python runtime: $venvPython"
  }
} finally {
  Pop-Location
}
