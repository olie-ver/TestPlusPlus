clean:
	rm -rf build
	rm -rf install
	clear

install:
	cmake -S . -B build -DCMAKE_INSTALL_PREFIX=install
	cmake --build build --parallel
	cmake --install build
	rm -rf build

run: 
	install/bin/testpp

test:
	install/bin/testpp tests/src/assert.cpp