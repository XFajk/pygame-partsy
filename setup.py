from setuptools import setup, Extension

module = Extension('partsy',
                   sources=['c_src/pygame_partsy.c'])

setup(
    name='partsy',
    version='0.0.1',
    description='Fast particle system for pygame developers',
    ext_modules=[module],
    package_dir={'': 'py_src'},
    packages=['partsy'],
    package_data={'partsy': ['partsy.pyi']}
)
