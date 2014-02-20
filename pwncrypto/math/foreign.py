'''Foreign imports of fast mathematical functions'''
import gmpy2

__all__ = 'gcd lcm gcdext invert is_prime root log2'.split()

def gcd(*args):
    return reduce(gmpy2.gcd, args)

def lcm(*args):
    return reduce(gmpy2.lcm, args)

gcdext = gmpy2.gcdext
invert = gmpy2.invert
is_prime = gmpy2.is_prime
root = gmpy2.root
log2 = gmpy2.log2
