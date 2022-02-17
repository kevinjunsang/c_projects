#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>

#include "numtheory.h"
#include "randstate.h"

void gcd(mpz_t d, mpz_t a, mpz_t b) {
	mpz_t t, b_1;
	mpz_init(t);
	mpz_init_set(b_1, b);
	while (mpz_cmp_ui(b_1, 0) > 0) {
		mpz_set(t, b_1);
		mpz_fdiv_r(b_1, a, b_1);
		mpz_set(a, t);
	}
	mpz_set(d, a);
	mpz_clears(t, b_1, NULL);
}
//r = r, r_1 = r'
//t = t, t_1 = t'
//temp = temp for r and t
void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {
	mpz_t r, r_1, t, t_1, q, temp, mul;
	mpz_inits(r, r_1, t, t_1, q, temp, mul, NULL);
	mpz_set(r, n);
	mpz_set(r_1, a);
	mpz_set_ui(t, 0);
	mpz_set_ui(t_1, 1);
	while (mpz_cmp_ui(r_1, 0) != 0) {
		mpz_fdiv_q(q, r, r_1);
		mpz_set(temp, r_1);
		mpz_mul(mul, q, temp);
		mpz_sub(r_1, r, mul);
		mpz_set(r, temp);
		mpz_set(temp, t_1);
		mpz_mul(mul, q, temp);
		mpz_sub(t_1, t, mul);
		mpz_set(t, temp);
	}
	if (mpz_cmp_ui(r, 1) > 0) {
		mpz_set(i, 0);
	}
	if (mpz_cmp_ui(t, 0) < 0) {
		mpz_add(i, t, n);
	}
	mpz_clears(r, r_1, t, t_1, q, temp, mul, NULL);
}

void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {
	mpz_t v, p, ex;
	mpz_inits(v, p, ex, NULL);
	mpz_set_ui(v, 1);
	mpz_set(p, base);
	mpz_set(ex, exponent);
	while (mpz_cmp_ui(ex, 0) > 0) {
		if (mpz_odd_p(ex)){
			mpz_mul(v, v, p);
			mpz_mod(v, v, modulus);
		}
		mpz_mul(p, p, p);
		mpz_mod(p, p, modulus);
		mpz_fdiv_q_ui(ex, ex, 2);
	}
	mpz_set(out, v);
	mpz_clears(v, p, ex, NULL);
}

bool is_prime(mpz_t n, uint64_t iters) {
	if (mpz_cmp_ui(n, 0) == 0) {
		return false;
	}
	if (mpz_cmp_ui(n, 1) == 0) {
		return false;
	}
	if (mpz_cmp_ui(n, 2) == 0) {
		return true;
	}
	if (mpz_cmp_ui(n, 3) == 0) {
		return true;
	}
	if (mpz_even_p(n) != 0) {
		return false;
	}
	mpz_t d, s, y, a, f, n_1, n_2, s_1, s_2, j, t;
	mpz_inits(d, s, y, f, a, n_1, n_2, s_1, s_2, j, t, NULL);
	mpz_sub_ui(d, n, 1);
	mpz_set_ui(s, 0);
	while(mpz_even_p(d) == 0) {
		mpz_fdiv_q_ui(d, d, 2);
		mpz_add_ui(s, s, 1);
		mpz_set(s_1, s);
	}
	mpz_sub_ui(n_1, n, 3);
	mpz_sub_ui(n_2, n, 1);
	mpz_sub_ui(s_2, s_1, 1);
	mpz_set_ui(t, 2);
	for (uint64_t i = 1; i < iters; i += 1) {
		mpz_urandomm(a, state, n_1);
		mpz_add_ui(a, a, 2);
		pow_mod(y, a, d, n);
		if ((mpz_cmp_ui(y, 1) != 0) && (mpz_cmp(y, n_2) != 0)) {
			mpz_set_ui(j, 1);
			while ((mpz_cmp(j, s_2) <= 0) && (mpz_cmp(y, n_2) != 0)) {
				pow_mod(y, y, t, n);
				if (mpz_cmp_ui(y, 1) == 0) {
					mpz_clears(d, s, y, a, n_1, n_2, s_1, s_2, j, t, NULL);
					return false;
				}
				mpz_add_ui(j, j, 1);
			}
			if (mpz_cmp(y, n_2) != 0) {
				mpz_clears(d, s, y, a, n_1, n_2, s_1, s_2, j, t, NULL);
				return false;
			}
		}
	}
	mpz_clears(d, s, y, a, n_1, n_2, s_1, s_2, j, t, NULL);
	return true;				
}


void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
	do {
		mpz_urandomb(p, state, bits);
		if (mpz_even_p(p)) {
			mpz_sub_ui(p, p, 1);
		}
	}while(is_prime(p, iters) == false);
}


