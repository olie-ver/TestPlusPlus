clean:
	rm -rf build
	rm -rf install
	clear

install:
	cmake -S . -B build -DCMAKE_INSTALL_PREFIX=install
	cmake --build build --parallel
	cmake --install build

run: 
	install/bin/testpp

test:
	install/bin/testpp /Users/oliverlie/Documents/GitHub/TestPlusPlus/V20.2.0/tests/src/assert.cpp

impl:
	testpp tests/src/cli.cpp cli/src/Config/Metadata.cpp cli/src/Config/Serialize.cpp cli/src/Config/Stream.cpp cli/src/Helpers/split.cpp