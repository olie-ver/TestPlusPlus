$ErrorActionPreference = "Stop"

$Version = "20.1.4"

$InstallerDir = $PSScriptRoot
$TestPPDir = Join-Path $InstallerDir "..\V$Version"
$TestPPDir = (Resolve-Path $TestPPDir).Path

$InstallerScript = Join-Path $InstallerDir "testpp.iss"
$StagingDir = Join-Path $TestPPDir "staging"

$InnoSetup = "C:\Program Files\Inno Setup 7\ISCC.exe"

$Architectures = @(
    @{
        Name = "x86"
        CMakeArchitecture = "Win32"
    },
    @{
        Name = "x64"
        CMakeArchitecture = "x64"
    },
    @{
        Name = "arm64"
        CMakeArchitecture = "ARM64"
    }
)

Write-Host "========================================"
Write-Host " Test++ Windows Installer Builder"
Write-Host " Version: $Version"
Write-Host "========================================"
Write-Host ""

# Verify required files/directories
if (-not (Test-Path $TestPPDir)) {
    throw "Test++ directory not found: $TestPPDir"
}

if (-not (Test-Path $InstallerScript)) {
    throw "Installer script not found: $InstallerScript"
}

if (-not (Test-Path $InnoSetup)) {
    throw "Inno Setup compiler not found: $InnoSetup"
}

foreach ($Architecture in $Architectures) {

    $Name = $Architecture.Name
    $CMakeArchitecture = $Architecture.CMakeArchitecture

    Write-Host ""
    Write-Host "----------------------------------------"
    Write-Host " Building $Name"
    Write-Host "----------------------------------------"

    $BuildDir = Join-Path $TestPPDir "build-$Name"

    # Start with a clean staging directory.
    if (Test-Path $StagingDir) {
        Write-Host "Cleaning staging directory..."
        Remove-Item $StagingDir -Recurse -Force
    }

    # Configure
    Write-Host "Configuring CMake for $CMakeArchitecture..."

    Push-Location $TestPPDir

    try {
        & cmake `
            -S . `
            -B $BuildDir `
            -A $CMakeArchitecture `
            -DCMAKE_BUILD_TYPE=Release

        if ($LASTEXITCODE -ne 0) {
            throw "CMake configuration failed for $Name."
        }

        # Build
        Write-Host "Building $Name..."

        & cmake `
            --build $BuildDir `
            --parallel `
            --config Release

        if ($LASTEXITCODE -ne 0) {
            throw "CMake build failed for $Name."
        }

        # Install into the shared staging directory
        Write-Host "Installing $Name into staging..."

        & cmake `
            --install $BuildDir `
            --config Release `
            --prefix staging

        if ($LASTEXITCODE -ne 0) {
            throw "CMake install failed for $Name."
        }
    }
    finally {
        Pop-Location
    }

    if (-not (Test-Path $StagingDir)) {
        throw "Staging directory was not created for $Name."
    }

    # Immediately package this architecture before staging is replaced.
    Write-Host "Creating $Name installer..."

    & $InnoSetup "/DArch=$Name" $InstallerScript

    if ($LASTEXITCODE -ne 0) {
        throw "Inno Setup failed while creating the $Name installer."
    }

    Write-Host "$Name installer created successfully."
}

Write-Host ""
Write-Host "========================================"
Write-Host " All installers built successfully!"
Write-Host "========================================"