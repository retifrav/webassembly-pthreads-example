# WebAssembly with pthreads

<https://web.dev/articles/webassembly-threads>

## Emscripten

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

$ emcc -std=c++17 ./src/without-pthreads.cpp -o ./web/some-without-pthreads.js

$ emcc -std=c++17 ./src/with-pthreads.cpp -o ./web/some-with-pthreads.js \
    -pthread -s PROXY_TO_PTHREAD 
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
$ cd /path/to/project/web
$ python ./server.py
```
