# WebAssembly with pthreads example

An example of a C++ project compiling to WebAssembly with pthreads.

More details in the [following article](https://decovar.dev/blog/2023/11/20/webassembly-with-pthreads/).

<!-- MarkdownTOC -->

- [Emscripten](#emscripten)
- [Building](#building)
    - [Without CMake](#without-cmake)
    - [With CMake](#with-cmake)
- [Running](#running)

<!-- /MarkdownTOC -->

## Emscripten

You need to have Emscripten installed in your system:

``` sh
$ cd /path/to/programs
$ git clone https://github.com/emscripten-core/emsdk.git
$ cd emsdk
$ ./emsdk list
$ ./emsdk install latest
$ ./emsdk activate latest

$ source /path/to/programs/emsdk/emsdk_env.sh
$ emcc --version
emcc (Emscripten gcc/clang-like replacement + linker emulating GNU ld) 3.1.48 (e967e20b4727956a30592165a3c1cde5c67fa0a8)
```

## Building

### Without CMake

``` sh
$ cd /path/to/project

$ emcc ./src/without-pthreads.cpp ./src/some-shit.cpp \
    -o ./web/some-without-pthreads.js

$ emcc ./src/with-pthreads.cpp ./src/some-shit.cpp \
    -o ./web/some-with-pthreads.js \
    -pthread -sPROXY_TO_PTHREAD
```

### With CMake

``` sh
$ cd /path/to/project

$ cmake -G Ninja -DCMAKE_TOOLCHAIN_FILE="$EMSDK/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake" \
    -DCMAKE_BUILD_TYPE=Release -DWITH_PTHREADS=0 ..
$ cmake --build . --target install

$ cmake -G Ninja -DCMAKE_TOOLCHAIN_FILE="$EMSDK/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake" \
    -DCMAKE_BUILD_TYPE=Release -DWITH_PTHREADS=1 ..
$ cmake --build . --target install
```

## Running

``` sh
$ cd /path/to/project
$ python ./server.py
```
