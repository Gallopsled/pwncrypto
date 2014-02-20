pwncrypto
=========

__This library is super ALPHA.__

__It will probably wipe your disk and kick your dog!__

Python library for working with cryptography, cryptographic primitives,
and number theory.

This document describes the proposed structure of the project
and future features.

The goal is to create a fast an easy to use library. Ease of use
comes from python, and speed from C. Getting started should be as easy as

    $ pip install pwncrypto

 - Modern cryptography
 - Mathematics

Required libraries are
 - PyCrypto
 - gmpy2

Modern cryptography
-------------------

Provide both complete implementations and building blocks
for modern cryptographic constructions. The goal is to enable
analysis of novel implementations as seen in CTFs.

Mathematics
-----------

Provide an interface to the fundamental building blocks that
everything is based on, for maximum flexibility in development.
