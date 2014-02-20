#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include <gmp.h>
#define printf gmp_printf

void factor_fermat(mpz_t p, mpz_t q, const mpz_t N)
{
    if (mpz_probab_prime_p(N, 25)) // Error prob 2^(-50)
    {
        mpz_set(p, N);
        mpz_set_ui(q, 1);
        return;
    }

    mpz_t a, b;
    mpz_inits(a, b, NULL);

    mpz_sqrt(a, N); // a = sqrt(N)
    mpz_mul(b, a, a);
    mpz_sub(b, b, N); // b = a*a - N

    while (!mpz_perfect_square_p(b))
    {
        mpz_addmul_ui(b, a, 2);
        mpz_add_ui(b, b, 1); // b += 2*a + 1
        mpz_add_ui(a, a, 1); // a += 1
    }

    mpz_sqrt(b, b);
    mpz_sub(p, a, b);
    mpz_add(q, a, b);

    mpz_clears(a, b, NULL);
}

void factor_pollard_rho(mpz_t p, mpz_t q, const mpz_t N)
{
    uint64_t i = 1, power = 1;

    mpz_t x, y, d;
    mpz_inits(x, y, d, NULL);

    mpz_set_ui(x, 2);
    mpz_set_ui(y, 2);
    mpz_set_ui(d, 1);

    // TODO: Refine accoring to literature

    while (mpz_cmp_ui(d, 1) == 0)
    {
        mpz_mul(x, x, x);
        mpz_add_ui(x, x, 2); // Choose another function?
        mpz_mod(x, x, N); // x = (x*x + 2) % N

        // This can be optimized further
        // as described on wikipedia
        mpz_sub(d, x, y);
        mpz_abs(d, d);
        mpz_gcd(d, d, N); // d = gcd(abs(x - y), N)

        if (i == power)
        {
            mpz_set(y, x); // y = x
            power *= 2; // power *= 2
        }

        i += 1;
    }

    if (mpz_cmp(d, N) != 0)
    {
        mpz_set(p, d);
        mpz_cdiv_q(q, N, d); // q = N // d
    }
    else
    {
        mpz_set_ui(p, 0);
        mpz_set_ui(q, 0);
    }

    mpz_clears(x, y, d, NULL);
}

void factor_sqrt_1(mpz_t p, mpz_t q, const mpz_t N, const mpz_t e, const mpz_t d)
{
    mpz_t r, w, v, v0;
    mpz_t max, one;
    mpz_inits(r, w, v, v0, max, one, NULL);

    mpz_mul(r, e, d);
    mpz_sub_ui(r, r, 1);
    mpz_cdiv_q_ui(r, r, 2); // r = (e*d - 1) / 2

    unsigned int s = 1; // Why do we keep s?

    while (mpz_divisible_ui_p(r, 2))
    {
        mpz_divexact_ui(r, r, 2);
        s += 1;
    }

    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));

    mpz_sub_ui(max, N, 1);
    mpz_set_ui(one, 1);

    while (true)
    {
        mpz_urandomm(w, state, max);
        mpz_add_ui(w, w, 2); // w = rand(2, n)

        mpz_powm(v, w, r, N); // v = pow(w, r, N)

        if (!mpz_cmp_ui(v, 1))
        {
            continue;
        }

        while (!mpz_congruent_p(v, one, N))
        {
            mpz_set(v0, v);
            mpz_powm_ui(v, v, 2, N); // v = pow(v, 2, N)
        }

        if (mpz_congruent_p(v0, N, max))
        {
            continue;
        }

        mpz_add_ui(v0, v0, 1);
        mpz_gcd(p, v0, N); // p = gcd(v0 + 1, N)
        mpz_cdiv_q(q, N, p); // q = N/p
    }

    gmp_randclear(state);
    mpz_clears(r, w, v, v0, max, one, NULL);
}
