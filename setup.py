from setuptools import setup, Extension, find_packages

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
    packages=find_packages(),
    include_package_data=True,
    license='MIT License',
    ext_modules=[
        Extension(
            'abieos._private',
            include_dirs=['external/abieos/src'],
            sources=['private/_abieos_private.c'],
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
