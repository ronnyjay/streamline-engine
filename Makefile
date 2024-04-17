default: streamline-engine

streamline-engine: build
	cd build && cmake -DCMAKE_BUILD_TYPE=Debug .. && make

build:
	mkdir -p build

format:
	clang-format -i src/**/*.cpp

run: streamline-engine
	build/src/streamline-engine

.PHONY: clean
clean:
	rm -rf build .cache