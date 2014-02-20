from distutils.core import setup

setup(
    name='pwncrypto',
    version='0.0.1',
    author='pwnies',
    author_email='pwnies@dikumail.dk',
    packages=['pwncrypto'],
    scripts=[],
    url='https://github.com/pwnies/pwncrypto',
    license='LICENSE.txt',
    description='A python library implementing crypto attacks and utility functions',
    long_description=open('README.md').read(),
    install_requires=[
        "gmpy2 >= 2.0.3",
        "PyCrypto >= 2.6.1"
    ],
)
