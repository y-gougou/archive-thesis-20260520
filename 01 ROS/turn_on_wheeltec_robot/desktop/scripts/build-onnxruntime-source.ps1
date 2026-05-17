param(
  [string]$Version = "1.18.1",
  [string]$LlvmMingwVersion = "20260505",
  [string]$Config = "Release",
  [string]$ToolchainDir = "",
  [string]$PythonVenvDir = "",
  [switch]$BuildInference,
  [switch]$Force
)

$ErrorActionPreference = "Stop"

$ProjectRoot = Resolve-Path (Join-Path $PSScriptRoot "..")
if (-not $ToolchainDir) {
  $ToolchainDir = Join-Path $ProjectRoot ".toolchain"
}
if (-not $PythonVenvDir) {
  $PythonVenvDir = Join-Path $ProjectRoot "python"
}

$DownloadsDir = Join-Path $ToolchainDir "downloads"
$SourceRoot = Join-Path $ToolchainDir "onnxruntime-src"
$BuildRoot = Join-Path $ToolchainDir "onnxruntime-build"
$InstallRoot = Join-Path $ToolchainDir "onnxruntime-v$Version-mingw"
$LlvmMingwRoot = Join-Path $ToolchainDir "llvm-mingw"

function Write-Step {
  param([string]$Message)
  Write-Host ""
  Write-Host "==> $Message" -ForegroundColor Cyan
}

function Write-Ok {
  param([string]$Message)
  Write-Host "OK  $Message" -ForegroundColor Green
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

function Expand-ZipArchive {
  param(
    [string]$Archive,
    [string]$Destination
  )
  if ((Test-Path $Destination) -and -not $Force) {
    Write-Ok "Using existing directory: $Destination"
    return
  }
  if (Test-Path $Destination) {
    Remove-Item -LiteralPath $Destination -Recurse -Force
  }
  New-Item -ItemType Directory -Force -Path $Destination | Out-Null
  Expand-Archive -LiteralPath $Archive -DestinationPath $Destination -Force
}

function Resolve-LocalTool {
  param(
    [string]$ToolGroup,
    [string]$Executable
  )
  $base = Join-Path $ToolchainDir $ToolGroup
  $direct = Join-Path $base $Executable
  if (Test-Path $direct) {
    return $direct
  }
  $match = Get-ChildItem -LiteralPath $base -Recurse -Filter $Executable -ErrorAction SilentlyContinue |
    Select-Object -First 1
  if ($match) {
    return $match.FullName
  }
  return $Executable
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

function Ensure-LlvmMingw {
  Write-Step "Preparing llvm-mingw toolchain"
  $archive = Join-Path $DownloadsDir "llvm-mingw-$LlvmMingwVersion-ucrt-x86_64.zip"
  Download-File "https://github.com/mstorsjo/llvm-mingw/releases/download/$LlvmMingwVersion/llvm-mingw-$LlvmMingwVersion-ucrt-x86_64.zip" $archive
  Expand-ZipArchive $archive $LlvmMingwRoot
  $bin = First-ExistingPath @(
    (Join-Path $LlvmMingwRoot "llvm-mingw-$LlvmMingwVersion-ucrt-x86_64\bin")
  )
  if (-not $bin) {
    throw "llvm-mingw bin directory was not found under $LlvmMingwRoot"
  }
  return $bin
}

function Ensure-OnnxRuntimeSource {
  Write-Step "Preparing ONNX Runtime source"
  $archive = Join-Path $DownloadsDir "onnxruntime-v$Version.zip"
  Download-File "https://github.com/microsoft/onnxruntime/archive/refs/tags/v$Version.zip" $archive
  Expand-ZipArchive $archive $SourceRoot
  $sourceDir = Join-Path $SourceRoot "onnxruntime-$Version"
  if (-not (Test-Path $sourceDir)) {
    throw "ONNX Runtime source directory was not found: $sourceDir"
  }
  return $sourceDir
}

function Install-BuildRequirements {
  param(
    [string]$SourceDir,
    [string]$PythonExe,
    [string]$UvExe
  )
  $requirements = Join-Path $SourceDir "requirements.txt"
  if (-not (Test-Path $requirements)) {
    return
  }
  Write-Step "Installing ONNX Runtime Python build requirements"
  Invoke-Checked $UvExe @("pip", "install", "--python", $PythonExe, "-r", $requirements)
}

function Find-BuiltFile {
  param(
    [string]$Root,
    [string[]]$Names
  )
  foreach ($name in $Names) {
    $match = Get-ChildItem -LiteralPath $Root -Recurse -File -Filter $name -ErrorAction SilentlyContinue |
      Select-Object -First 1
    if ($match) {
      return $match.FullName
    }
  }
  return ""
}

function Install-OnnxRuntimeArtifacts {
  param([string]$SourceDir)
  Write-Step "Installing ONNX Runtime artifacts"
  $includeDir = Join-Path $InstallRoot "include"
  $libDir = Join-Path $InstallRoot "lib"
  if (Test-Path $InstallRoot) {
    Remove-Item -LiteralPath $InstallRoot -Recurse -Force
  }
  New-Item -ItemType Directory -Force -Path $includeDir, $libDir | Out-Null

  $sessionInclude = Join-Path $SourceDir "include\onnxruntime\core\session"
  Copy-Item -LiteralPath (Join-Path $sessionInclude "*.h") -Destination $includeDir -Force

  $dll = Find-BuiltFile $BuildRoot @("onnxruntime.dll")
  $importLib = Find-BuiltFile $BuildRoot @("libonnxruntime.dll.a", "onnxruntime.lib")
  if (-not $dll -or -not $importLib) {
    throw "Could not find built ONNX Runtime dll/import library under $BuildRoot"
  }

  Copy-Item -LiteralPath $dll -Destination (Join-Path $libDir "onnxruntime.dll") -Force
  if ($importLib.EndsWith(".dll.a")) {
    Copy-Item -LiteralPath $importLib -Destination (Join-Path $libDir "libonnxruntime.dll.a") -Force
  } else {
    Copy-Item -LiteralPath $importLib -Destination (Join-Path $libDir "onnxruntime.lib") -Force
  }

  Write-Ok "ONNXRUNTIME_ROOT=$InstallRoot"
}

Push-Location $ProjectRoot
try {
  $llvmMingwBin = Ensure-LlvmMingw
  $sourceDir = Ensure-OnnxRuntimeSource
  $pythonExe = Join-Path $PythonVenvDir "Scripts\python.exe"
  if (-not (Test-Path $pythonExe)) {
    throw "Python venv was not found: $pythonExe. Run npm run setup:env first."
  }
  $uvExe = Resolve-LocalTool "uv" "uv.exe"
  $cmakeExe = Resolve-LocalTool "cmake" "cmake.exe"
  $ninjaExe = Resolve-LocalTool "ninja" "ninja.exe"

  $env:PATH = @(
    $llvmMingwBin,
    (Split-Path $cmakeExe -Parent),
    (Split-Path $ninjaExe -Parent),
    (Split-Path $uvExe -Parent),
    (Split-Path $pythonExe -Parent),
    $env:PATH
  ) -join [IO.Path]::PathSeparator
  $env:CC = Join-Path $llvmMingwBin "x86_64-w64-mingw32-clang.exe"
  $env:CXX = Join-Path $llvmMingwBin "x86_64-w64-mingw32-clang++.exe"
  $env:RC = Join-Path $llvmMingwBin "llvm-rc.exe"

  Install-BuildRequirements -SourceDir $sourceDir -PythonExe $pythonExe -UvExe $uvExe

  Write-Step "Building ONNX Runtime from source with llvm-mingw"
  Invoke-Checked $pythonExe @(
    (Join-Path $sourceDir "tools\ci_build\build.py"),
    "--config", $Config,
    "--build_dir", $BuildRoot,
    "--skip_tests",
    "--parallel",
    "--build_shared_lib",
    "--compile_no_warning_as_error",
    "--cmake_generator", "Ninja",
    "--cmake_extra_defines", "CMAKE_MAKE_PROGRAM=$($ninjaExe.Replace('\', '/'))",
    "--cmake_extra_defines", "CMAKE_C_COMPILER=$($env:CC.Replace('\', '/'))",
    "--cmake_extra_defines", "CMAKE_CXX_COMPILER=$($env:CXX.Replace('\', '/'))",
    "--cmake_extra_defines", "CMAKE_RC_COMPILER=$($env:RC.Replace('\', '/'))"
  ) $sourceDir

  Install-OnnxRuntimeArtifacts -SourceDir $sourceDir
  if ($BuildInference) {
    Write-Step "Building inference executable against source-built ONNX Runtime"
    $env:ONNXRUNTIME_ROOT = $InstallRoot
    Invoke-Checked "node" @((Join-Path $PSScriptRoot "build-infer.js"))
  }
  Write-Step "Done"
  Write-Ok "ONNX Runtime source build is ready: $InstallRoot"
} finally {
  Pop-Location
}
