from setuptools import setup, Extension
import sys

extra_objects = []
libraries = ['stdc++']
library_dirs = []


# Hacky but are there really any docs for this?
if '--static' in sys.argv:
    extra_objects = ['external/abieos/build/libabieos.a']
    sys.argv.remove('--static')
else:
    libraries.append('abieos')
    library_dirs.append('external/abieos/build')


with open("README.md", "r") as fh:
    long_description = fh.read()

setup(
    name='abieos-python',
    description='Python bindings for abieos library.',
    long_description=long_description,
    long_description_content_type='text/markdown',
    author='Maciej Janiszewski',
    author_email='maciej@ulam.io',
    url="https://github.com/ulamlabs/abieos-python",
    version='1.0.0',
    packages=['abieos'],
    include_package_data=True,
    license='MIT License',
    ext_modules=[
        Extension(
            'abieos._private',
            include_dirs=['external/abieos/src'],
            sources=['abieos/_private.c'],
            extra_objects=extra_objects,
            library_dirs=library_dirs,
            libraries=libraries
        )
    ],
    extras_require={
        'dev': [
            'wheel',
            'flake8',
            'pytest',
            'pytest-cov'
        ]
    }
)
