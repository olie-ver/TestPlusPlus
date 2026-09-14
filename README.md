# Test++
It is available for download and installation on Mac, Windows, and Linux, 
however, its development is done on Mac, and its usage in other operating 
systems is largely untested. It is completely open source and free to use. 
It is currently built using C++20, and usage with other languages/C++ standards 
has not yet been tested.

# Installation

In order to use Test++ as a CLI tool, you will need CMake installed on your system.
This CMake requirement is not present when you use Test++ as a library. 

## Homebrew (Preferred)
If you have a Mac, you can install Test++ via Homebrew.

```bash
brew trust olie-ver/testpp
brew tap olie-ver/testpp
brew install testpp
```
After this you can start using the testpp command immediately without needing to register the path. 
To uninstall, run 

```bash
brew uninstall testpp
```

## Manual Installation (Mac)

In order to manually install Test++, go to the Downloads folder and download the V20.1.4.zip file.
Extract the files. Open a new terminal inside the V20.1.4 folder and then run the following commands:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
sudo cmake --install build
```

Then to register the `testpp` command in your Mac system, you can run:
```bash
echo 'export PATH="$HOME/testpp-install/bin:$PATH"' >> ~/.zshrc
```

## Installer (Windows ARM)

Go into the installer/installs folder and run the TestPlusPlus-20.1.4-win-arm64.exe file. This will automatically 
install Test++, the VC++ runtime (if needed) and register the `testpp` command automatically.

## Manual Installation (Windows)

In order to manually install Test++, go to the Downloads folder and download the V20.1.4.zip file.
Extract the files. Open a new terminal inside the V20.1.4 folder and then run the following commands:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel --config Release
sudo cmake --install build --config Release
```

For Windows, you can register the `testpp` command by going to your 
Environment Variables, finding the PATH variable and then adding in a 
new environment variable to `C:\Program Files (x86)\testpp\bin`.
