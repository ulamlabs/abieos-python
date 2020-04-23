from setuptools import setup, Extension

setup(
    name='abieos-python',
    description='Python bindings for abieos library.',
    author='Maciej Janiszewski',
    author_email='maciej@ulam.io',
    version='1.0',
    ext_modules=[
        Extension(
            'abieos',
            include_dirs=['external/abieos/include'],
            sources=['abieosmodule.c'],
            extra_objects=['external/abieos/build/libabieos.a'],
            libraries=['stdc++']
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
