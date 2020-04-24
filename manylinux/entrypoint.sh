#!/bin/bash
set -e -x

yum install -y devtoolset-8-libasan-devel.x86_64 devtoolset-8-libubsan-devel.x86_64

# Add newer version of CMake to path
export PATH=/cmake-$CMAKE_VERSION-Linux-x86_64/bin:$PATH

# Build abieos library
mkdir -p /github/workspace/external/abieos/build
cd /github/workspace/external/abieos/build
cmake ..
make

# Compile wheels
for PYBIN in /opt/python/cp3[6-8]*/bin; do
    "${PYBIN}/pip" wheel /github/workspace/ -w /github/workspace/wheelhouse/ --build-option --static
done

# Bundle external shared libraries into the wheels
for whl in /github/workspace/wheelhouse/*-linux*.whl; do
    auditwheel repair "$whl" --plat "${PLAT}" -w /github/workspace/wheelhouse/ || { echo "Repairing wheels failed."; auditwheel show "$whl"; exit 1; }
done

rm -rf /github/workspace/wheelhouse/*-linux_x86_64.whl

echo "Succesfully built wheels:"
ls /github/workspace/wheelhouse