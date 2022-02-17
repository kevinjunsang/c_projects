#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "rsa.h"
#include "randstate.h"
#include "numtheory.h"

#include <gmp.h>

int main(int argc, char **argv) {
    //initialize bits and iters as 256 and 50 respectively
    uint64_t mbits = 256;
    uint64_t miters = 50;
    FILE *pbfile = stdin;
    FILE *pvfile = stdout;
    bool file_1 = true;
    bool file_2 = true;
    uint64_t seed = time(NULL);
    bool V = false;
    bool H = false;
    int opt = 0;
    //getopt loop
    while ((opt = getopt(argc, argv, "b:i:n:d:s:vh")) != -1) {
        switch (opt) {
        case 'b': mbits = atoi(optarg); break;
        case 'i': miters = atoi(optarg); break;
        case 'n':
            pbfile = fopen(optarg, "w");
            file_1 = false;
            break;
        case 'd':
            pvfile = fopen(optarg, "w");
            file_2 = false;
            break;
        case 's': seed = atoi(optarg); break;
        case 'v': V = true; break;
        case 'h': H = true; break;
        default: fprintf(stderr, "error\n"); return 1;
        }
    }
    //default pbfile and pvfile
    if (file_1 == true) {
        pbfile = fopen("rsa.pub", "w");
    }
    if (file_2 == true) {
        pvfile = fopen("rsa.priv", "w");
    }
    //fileno and fchmod as asgn doc
    int pubfile, privfile;
    pubfile = fileno(pbfile);
    privfile = fileno(pvfile);
    if (fchmod(pubfile, 0600) == -1 || fchmod(privfile, 0600) == -1) {
        printf("wrong permissions\n");
        return -1;
    }

    mpz_t p, q, n, e, d, mpz_name, sign;
    mpz_inits(p, q, n, e, d, mpz_name, sign, NULL);
    //initialize seed
    randstate_init(seed);
    //make public key and private key
    rsa_make_pub(p, q, n, e, mbits, miters);
    rsa_make_priv(d, e, p, q);
    //initialize temporary d values
    mpz_t d_1, d_2;
    mpz_inits(d_1, d_2, NULL);
    mpz_set(d_1, d);
    mpz_set(d_2, d);
    //get name and convert to mpz
    char *name = getenv("USER");
    mpz_set_str(mpz_name, name, 62);
    //sign with temp d value d_1 and write priv with temp d value d_2
    rsa_sign(sign, mpz_name, d_1, n);
    rsa_write_pub(n, e, sign, name, pbfile);
    rsa_write_priv(n, d_2, pvfile);
    mpz_clears(d_1, d_2);
    if (V == true) {
        printf("User = %s\n", name);
        gmp_printf("s (%d bits) = %Zd\n", mpz_sizeinbase(sign, 2), sign);
        gmp_printf("p (%d bits) = %Zd\n", mpz_sizeinbase(p, 2), p);
        gmp_printf("q (%d bits) = %Zd\n", mpz_sizeinbase(q, 2), q);
        gmp_printf("n (%d bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%d bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
        gmp_printf("d (%d bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }
    //clear randstate and mpz_t values
    //close both files
    randstate_clear();
    mpz_clears(p, q, n, e, d, mpz_name, sign, NULL);
    fclose(pbfile);
    fclose(pvfile);
    if (H == true) {
        fprintf(stderr,
            "SYNOPSIS\n"
            "     Program generates a public and private RSA key\n"
            "\n"
            "USAGE\n"
            "     ./keygen [b:i:n:d:s:vh] [-b bits] [-i iters] [-n pubfile] [-d privfile] [-s "
            "seed]\n"
            "\n"
            "OPTIONS\n"
            "     -h                 Displays program usage and synopsis\n"
            "     -b                 Sets number of bits for public key (default = 256)\n"
            "     -i                 Sets number of iterations for Miller-Rabin (default = 50)\n"
            "     -n                 Sets file for public key (default = rsa.pub)\n"
            "     -d                 Sets file for private key (default = rsa.priv)\n"
            "     -s                 Sets seed for all random calls (default = time(NULL)\n"
            "     -v                 Prints out all values\n");
    }
    return 0;
}
