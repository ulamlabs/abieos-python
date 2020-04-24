# abieos-python

[![PyPI version](https://badge.fury.io/py/abieos-python.svg)](https://badge.fury.io/py/abieos-python) [![codecov](https://codecov.io/gh/ulamlabs/abieos-python/branch/master/graph/badge.svg)](https://codecov.io/gh/ulamlabs/abieos-python) ![Python package](https://github.com/ulamlabs/abieos-python/workflows/Python%20package/badge.svg)

Python bindings for [abieos](https://github.com/EOSIO/abieos) library. Implements Binary <> JSON conversion of EOS action data using ABIs.

## Building

abieos depends on a recent version of CMake (>=3.11) and GCC8. Patch to `CMakeLists.txt` is required to be able to build abieos as a static library.

First you need to build abieos library itself:

```shell
$ git submodule update --init-recursive
$ mkdir external/abieos/build
$ cd external/abieos/build
$ sed -i 's/STATIC src\/abi.cpp/STATIC src\/abieos.cpp src\/abi.cpp/' ../CMakeLists.txt
$ cmake ..
$ make
```

Then you can simply build the package using `setuptools`.

```shell
$ python setup.py build
$ python setup.py sdist bdist bdist_wheel
```

It's recommended to install it using the resulting wheel file instead of `setup.py install`.

## Running tests

When running tests you can run into problems because a version without C extensions will be used. As a workaround, you can copy the built file to `abieos/`:

```shell
cp build/lib.*/abieos/_private* abieos  # workaround
flake8
mypy
pytest
```

## Usage

If you're running Python on Linux or macOS, you can skip building and use a wheel instead.

```shell
$ pip install abieos-python
```

It is recommended to use `EosAbiSerializer` class if possible, but if your use case requires access the original abieos API, it is available under `abieos.private`.

### With ABI in binary format (`bytes`)
```python
from abieos import EosAbiSerializer

s = EosAbiSerializer()
s.set_abi_from_bin('eosio.token', abi)
```

### With ABI in hex format (`str`)
```python
from abieos import EosAbiSerializer

s = EosAbiSerializer()
s.set_abi_from_hex('eosio.token', abi)
```

### With ABI in JSON format (`dict`)
```python
from abieos import EosAbiSerializer

s = EosAbiSerializer()
s.set_abi_from_json('eosio.token', abi)
```

### dict -> bytes
```python
s.json_to_bin(
    'eosio.token',
    s.get_type_for_action('eosio.token', 'transfer'),
    {
        'from': 'useraaaaaaaa',
        'to': 'useraaaaaaab',
        'quantity': '0.0001 SYS',
        'memo': '',
    }
)
```

### dict -> hex string
```python
s.json_to_hex(
    'eosio.token',
    s.get_type_for_action('eosio.token', 'transfer'),
    {
        'from': 'useraaaaaaaa',
        'to': 'useraaaaaaab',
        'quantity': '0.0001 SYS',
        'memo': '',
    }
)
```

### bytes -> dict
```python
s.bin_to_json(
    'eosio.token',
    s.get_type_for_action('eosio.token', 'transfer'),
    b'`\x8c1\xc6\x18s\x15\xd6p\x8c1\xc6\x18s\x15\xd6\x01\x00\x00\x00\x00'
    b'\x00\x00\x00\x04SYS\x00\x00\x00\x00\x00'
)
```

### hex string -> dict
```python
s.hex_to_json(
    'eosio.token',
    s.get_type_for_action('eosio.token', 'transfer'),
    '608C31C6187315D6708C31C6187315D60100000000000000045359530000000000'
)
```

### With custom JSON encoder/decoder
```python
from abieos import EosAbiSerializer

s = EosAbiSerializer(loads=simplejson.loads, dumps=simplejson.dumps)
```
