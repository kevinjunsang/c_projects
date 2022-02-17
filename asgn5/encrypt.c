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
    ;
    FILE *in = stdin;
    FILE *out = stdout;
    FILE *pub = stdin;
    bool pubfile = true;
    bool V = false;
    bool H = false;
    int opt = 0;
    while ((opt = getopt(argc, argv, "i:o:n:vh")) != -1) {
        switch (opt) {
        case 'i': in = fopen(optarg, "r+"); break;
        case 'o': out = fopen(optarg, "w+"); break;
        case 'n':
            pub = fopen(optarg, "r+");
            pubfile = false;
            break;
        case 'v': V = true; break;
        case 'h': H = true; break;
        default: fprintf(stderr, "error\n"); return 1;
        }
    }
    if (pubfile == true) {
        pub = fopen("rsa.pub", "r+");
    }
    mpz_t n, e, s, name;
    mpz_inits(n, e, s, name, NULL);
    char username[50];
    rsa_read_pub(n, e, s, username, pub);
    mpz_set_str(name, username, 62);
    if (rsa_verify(name, s, e, n) != true) {
        fprintf(stderr, "Verification failed\n");
    }

    rsa_encrypt_file(in, out, n, e);
    if (V == true) {
        printf("User = %s\n", username);
        gmp_printf("s (%d bits) = %Zd\n", mpz_sizeinbase(s, 2), s);
        gmp_printf("n (%d bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%d bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
    }
    fclose(in);
    fclose(out);
    fclose(pub);
    mpz_clears(n, e, s, name, NULL);
    if (H == true) {
        fprintf(stderr, "SYNOPSIS\n"
                        "     Program encrypts RSA key\n"
                        "\n"
                        "USAGE\n"
                        "     ./keygen [i:o:n:vh] [-i infile] [-o outfile] [-n pubfile]\n"
                        "\n"
                        "OPTIONS\n"
                        "     -h                 Displays program usage and synopsis\n"
                        "     -i                 Sets input file (default = stdin)\n"
                        "     -o                 Sets output file (default = stdout)\n"
                        "     -n                 Sets file for public key (default = rsa.pub)\n"
                        "     -v                 Prints out all values\n");
    }
    return 0;
}
