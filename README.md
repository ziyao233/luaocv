# LuaOCV: OpenCV Bindng for Lua

A handwritten OpenCV binding for Lua.

## Build

To build LuaOCV, you need

- GNU Make
- pkg-config
- A C++11 compatible compiler
- OpenCV 4.x
- Lua 5.4 interpreter

installed on your system.

For the simplest build, run

```shell
 $ make
```

in the repository, this will produce `luaocv.so`, the loadable Lua module.

### Build Options and Defaults

- `LUA_PKGNAME`: pkg-config package name of Lua (`lua-5.4`)
- `CV_PKGNAME`: pkg-config package name of OpenCV (`opencv4`)
- `LUA_CXXFLAGS`: CXXFLAGS for Lua (detect with pkg-config)
- `CV_CXXFLAGS`: CXXFLAGS for OpenCV (detect with pkg-config)
- `LUA_LDFLAGS`: LDFLAGS for Lua (detect with pkg-config)
- `CV_LDFLAGS`: LDFLAGS for OpenCV (detect with pkg-config)
- `CROSS_COMPILE`: Prefix for cross-compilation toolchain (None)
- `CXX`: C++ Compiler (`$(CROSS_COMPILE)g++`)
- `CXXLD`: Linker (`$(CROSS_COMPILE)g++`)
- `DYN_FLAGS`: Flags for `CXX` and `CXXLD` to produce shared library
  (`-shared -fPIC`)
- `RELEASE`: Build a RELEASE library when set to 1 (None)

### Release Build

A release build disables boundary checks and enables optimization, make the
code faster to run, but harder to debug.

### Build Targets

- `default`: Build the library
- `clean`: Clean object files
- `disbuild`: Clean object files also with the library

## Run tests

There are some tests for LuaOCV in `tests`. Before run them, the library need
to be built first.

Use `run.sh` to do testing.

```shell
$ test/run.sh # run all tests
$ test/run.sh lua5.4 # run all tests with interpreter "lua5.4"
$ test/run.sh lua5.4 core # run test "core" with interpreter "lua5.4"
```

## Documentation

See `doc` directory.

## License and Copyright

Release under MIT License.
Copyright (c) 2024 Yao Zi. All rights reserved.
