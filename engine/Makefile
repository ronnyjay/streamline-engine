default: engine

build:
	mkdir -p build

engine: build
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
	cmake --build build -- -j$(shell nproc)

run: engine
	build/engine

test: engine
	build/test/engine-test

.PHONY: clean
clean:
	rm -rf build .cache
