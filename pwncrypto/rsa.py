def sqrt_1(N, e, d):
    import random
    from pwncrypto.math import gcd

    r = (e*d - 1) / 2
    s = 1
    while r % 2 == 0:
        r /= 2
        s += 1

    while True:
        w = random.randint(2, N)

        if gcd(w, N) != 1:
            p = gcd(w, N)
            return (p, N // p)

        v = pow(w, r, N)

        if v == 1:
            continue

        while v % N != 1:
            v0 = v
            v = pow(v, 2, N)

        if v0 % N == N-1:
            continue

        p = gcd(v0 + 1, N)
        return (p, N // p)
