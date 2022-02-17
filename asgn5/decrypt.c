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
    FILE *in = stdin;
    FILE *out = stdout;
    FILE *priv = stdin;
    bool privfile = true;
    bool V = false;
    bool H = false;
    int opt = 0;
    while ((opt = getopt(argc, argv, "i:o:n:vh")) != -1) {
        switch (opt) {
        case 'i': in = fopen(optarg, "r+"); break;
        case 'o': out = fopen(optarg, "w+"); break;
        case 'n':
            priv = fopen(optarg, "r+");
            privfile = false;
            break;
        case 'v': V = true; break;
        case 'h': H = true; break;
        default: fprintf(stderr, "error\n"); return 1;
        }
    }
    if (privfile == true) {
        priv = fopen("rsa.priv", "r+");
    }
    mpz_t n, d;
    mpz_inits(n, d, NULL);
    rsa_read_priv(n, d, priv);
    rsa_decrypt_file(in, out, n, d);
    if (V == true) {
        gmp_printf("n (%d bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("d (%d bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }
    fclose(in);
    fclose(out);
    fclose(priv);
    mpz_clears(n, d, NULL);
    if (H == true) {
        fprintf(stderr, "SYNOPSIS\n"
                        "     Program decrypts RSA key\n"
                        "\n"
                        "USAGE\n"
                        "     ./keygen [i:o:n:vh] [-i infile] [-o outfile] [-n privfile]\n"
                        "\n"
                        "OPTIONS\n"
                        "     -h                 Displays program usage and synopsis\n"
                        "     -i                 Sets input file (default = stdin)\n"
                        "     -o                 Sets output file (default = stdout)\n"
                        "     -n                 Sets file for private key (default = rsa.priv)\n"
                        "     -v                 Prints out all values\n");
    }
    return 0;
}
