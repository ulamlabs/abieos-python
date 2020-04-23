# abieos-python

Python bindings for [abieos](https://github.com/EOSIO/abieos) library.

## Build instructions

abieos depends on a recent version of CMake (>=3.11) and GCC8. Patch to `CMakeLists.txt` is required to be able to build abieos as a static library.

```shell
$ git submodule update --init-recursive
$ mkdir external/abieos/build
$ cd external/abieos/build
$ sed -i 's/STATIC src\/abi.cpp/STATIC src\/abieos.cpp src\/abi.cpp/' ../CMakeLists.txt
$ cmake ..
$ make
$ cd ../../
$ python setup.py build
```