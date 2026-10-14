clean:
	rm -rf build
	rm -rf install
	rm -rf build-debug
	clear

install:
	cmake -S . -B build -DCMAKE_INSTALL_PREFIX=install
	cmake --build build --parallel
	cmake --install build

run: 
	install/bin/testpp

print:
	install/bin/testpp --help
	install/bin/testpp --diagnostics
	install/bin/testpp --version
	install/bin/testpp --list

debug:
	cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=install
	cmake --build build-debug
	cmake --install build-debug

test:
	install/bin/testpp /Users/oliverlie/Documents/GitHub/TestPlusPlus/V20.2.0/tests/src/assert.cpp

impl:
	testpp tests/src/cli.cpp cli/src/Config/Metadata.cpp cli/src/Config/Serialize.cpp cli/src/Config/Stream.cpp cli/src/Helpers/split.cpp