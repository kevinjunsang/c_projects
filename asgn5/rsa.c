#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>

#include "randstate.h"
#include "numtheory.h"
#include "rsa.h"

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
    //making p and q as primes
    uint64_t bits = nbits / 2;
    //bits = nbits / 2
    make_prime(p, bits, iters);
    make_prime(q, bits, iters);
    if (mpz_cmp(p, q) < 0) {
        mpz_swap(p, q);
    }
    //setting n as p * q
    mpz_mul(n, p, q);
    //initialzing variables
    mpz_t g, p_1, q_1, n_1, e_1;
    mpz_inits(g, p_1, q_1, n_1, e_1, NULL);
    //g = gcd
    //p_1 = p - 1
    //q_1 = q - 1
    //n_1 = lambda(n)
    mpz_sub_ui(p_1, p, 1);
    mpz_sub_ui(q_1, q, 1);
    gcd(g, p_1, q_1);
    mpz_mul(n_1, p_1, q_1);
    mpz_fdiv_q(n_1, n_1, g);
    do {
        make_prime(e, nbits, iters);
        mpz_set(e_1, e);
        gcd(g, e_1, n_1);
    } while (mpz_cmp_ui(g, 1) != 0);
    mpz_clears(g, p_1, q_1, n_1, e_1, NULL);
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zx\n", n);
    gmp_fprintf(pbfile, "%Zx\n", e);
    gmp_fprintf(pbfile, "%Zx\n", s);
    fprintf(pbfile, "%s\n", username);
}

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%Zx\n", n);
    gmp_fscanf(pbfile, "%Zx\n", e);
    gmp_fscanf(pbfile, "%Zx\n", s);
    fscanf(pbfile, "%s\n", username);
}

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    //p_1 is p - 1
    //q_1 is q - 1
    //n_1 is lamba(n)
    mpz_t n_1, p_1, q_1;
    mpz_inits(n_1, p_1, q_1, NULL);
    mpz_sub_ui(p_1, p, 1);
    mpz_sub_ui(q_1, q, 1);
    mpz_mul(n_1, p_1, q_1);
    mod_inverse(d, e, n_1);
    mpz_clears(n_1, p_1, q_1, NULL);
}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n", n);
    gmp_fprintf(pvfile, "%Zx\n", d);
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx\n", n);
    gmp_fscanf(pvfile, "%Zx\n", d);
}

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    pow_mod(c, m, e, n);
}

void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    mpz_t out, base;
    mpz_inits(out, base, NULL);
    uint64_t k;
    size_t j = 0;
    k = mpz_sizeinbase(n, 2);
    k -= 1;
    k = k / 8;
    uint8_t *array;
    array = (uint8_t *) malloc((k) * sizeof(uint8_t));
    array[0] = 0xFF;
    while ((j = fread(array + 1, sizeof(uint8_t), k - 1, infile)) > 0) {
        mpz_import(base, j + 1, 1, sizeof(uint8_t), 1, 0, array);
        rsa_encrypt(out, base, e, n);
        gmp_fprintf(outfile, "%Zx\n", out);
    }
    free(array);
    mpz_clears(out, base, NULL);
}

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    pow_mod(m, c, d, n);
}

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
    mpz_t c, m;
    mpz_inits(c, m, NULL);
    uint64_t k;
    k = mpz_sizeinbase(n, 2);
    k -= 1;
    k = k / 8;
    uint8_t *array;
    array = (uint8_t *) malloc((k) * sizeof(uint8_t));
    array[0] = 0xFF;
    size_t j = 0;
    while (gmp_fscanf(infile, "%Zx\n", c) != EOF) {
        rsa_decrypt(m, c, d, n);
        mpz_export(array, &j, 1, sizeof(uint8_t), 1, 0, m);
        fwrite(array + 1, sizeof(char), j - 1, outfile);
    }
    free(array);
    mpz_clears(c, m, NULL);
}

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    pow_mod(s, m, d, n);
}

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    mpz_t t;
    mpz_init(t);
    pow_mod(t, s, e, n);
    if (mpz_cmp(t, m) == 0) {
        mpz_clear(t);
        return true;
    }
    mpz_clear(t);
    return false;
}
