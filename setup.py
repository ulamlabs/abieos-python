from distutils.core import setup, Extension
import glob


setup(
    name='py-abieos-python',
    version='1.0',
    ext_modules=[
        Extension(
            'abieos',
            include_dirs=['abieos/include'],
            library_dirs=['abieos/build'],
            sources=['abieosmodule.c'],
            libraries=['abieos']
        )
    ],
    data_files=[('/usr/local/lib', glob.glob('abieos/build/libabieos.dylib'))]
)
