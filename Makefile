default: streamline-engine

streamline-engine: build
	cd build && cmake -DCMAKE_BUILD_TYPE=Debug .. && make -j `nproc`

build:
	mkdir -p build

format:
	clang-format -i `find src -name "*.cpp"` `find src -name "*.hpp"`

run: streamline-engine
	build/streamline-engine

.PHONY: clean
clean:
	rm -rf build .cache