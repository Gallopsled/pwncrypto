#ifndef __FACTOR_H__
#define __FACTOR_H__

void factor_fermat(mpz_t p, mpz_t q, const mpz_t N);
void factor_pollard_rho(mpz_t p, mpz_t q, const mpz_t N);
void factor_sqrt_1(mpz_t p, mpz_t q, const mpz_t N, const mpz_t e, const mpz_t d);

#endif
