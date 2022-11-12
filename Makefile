build:
	cmake --build build --target all -j
configure:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo
.PHONY: build configure

