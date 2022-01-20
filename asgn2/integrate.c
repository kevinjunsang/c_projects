#include "functions.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PI 3.14159265

//integrate function
double integrate(double (*f)(double x), double a, double b, uint32_t n) {
    double h = (b - a) / n;
    double sum = (*f)(a) + (*f)(b);
    for (uint32_t i = 2; i < n; i += 2) {
        sum += 2 * (*f)(a + i * h);
    }
    for (uint32_t i = 1; i < n; i += 2) {
        sum += 4 * (*f)(a + i * h);
    }
    sum *= h / 3.0;
    return sum;
}
//getopt loop
//takes inputs for function, low, high, and partition count
int main(int argc, char **argv) {
    int opt = 0;
    bool A = false;
    bool B = false;
    bool C = false;
    bool D = false;
    bool E = false;
    bool F = false;
    bool G = false;
    bool H = false;
    bool I = false;
    bool J = false;
    bool Z = false;
    uint32_t count = 100;
    float low, high;
    while ((opt = getopt(argc, argv, "abcdefghijn:p:q:H")) != -1) {
        switch (opt) {
        case 'a': A = true; break;
        case 'b': B = true; break;
        case 'c': C = true; break;
        case 'd': D = true; break;
        case 'e': E = true; break;
        case 'f': F = true; break;
        case 'g': G = true; break;
        case 'h': H = true; break;
        case 'i': I = true; break;
        case 'j': J = true; break;
        case 'n': count = atoi(optarg); break;
        case 'p': low = atof(optarg); break;
        case 'q': high = atof(optarg); break;
        case 'H': Z = true; break;
        default: fprintf(stderr, "error\n"); return 1;
        }
    }
    //sqrt(1 - x^4) function
    if (A) {
        printf("sqrt(1 - x^4) ,%.6lf,%.6lf,%i\n", low, high, count);
        float A[count / 2];
        for (uint32_t i = 0; i < count / 2; i += 1) {
            A[i] = 2 + 2 * i;
            A[i] = integrate(a, low, high, A[i]);
        }
        for (uint32_t i = 0; i < count / 2; i += 1) {
            printf("%i,%.15lf\n", 2 + 2 * i, A[i]);
        }
    }
    //1/log(x) function
    if (B) {
        printf("1/log(x) ,%.6lf,%.6lf,%i\n", low, high, count);
        float A[count / 2];
        for (uint32_t i = 0; i < count / 2; i += 1) {
            A[i] = 2 + 2 * i;
            A[i] = integrate(b, low, high, A[i]);
        }
        for (uint32_t i = 0; i < count / 2; i += 1) {
            printf("%i,%.15lf\n", 2 + 2 * i, A[i]);
        }
    }
    //exp(-x^2) function
    if (C) {
        printf("exp(-x^2) ,%.6lf,%.6lf,%i\n", low, high, count);
        float A[count / 2];
        for (uint32_t i = 0; i < count / 2; i += 1) {
            A[i] = 2 + 2 * i;
            A[i] = integrate(c, low, high, A[i]);
        }
        for (uint32_t i = 0; i < count / 2; i += 1) {
            printf("%i,%.15lf\n", 2 + 2 * i, A[i]);
        }
    }
    //sin(x^2) function
    if (D) {
        printf("sin(x^2) ,%.6lf,%.6lf,%i\n", low, high, count);
        float A[count / 2];
        for (uint32_t i = 0; i < count / 2; i += 1) {
            A[i] = 2 + 2 * i;
            A[i] = integrate(d, low, high, A[i]);
        }
        for (uint32_t i = 0; i < count / 2; i += 1) {
            printf("%i,%.15lf\n", 2 + 2 * i, A[i]);
        }
    }
    //cos(x^2) function
    if (E) {
        printf("cos(x^2) ,%.6lf,%.6lf,%i\n", low, high, count);
        float A[count / 2];
        for (uint32_t i = 0; i < count / 2; i += 1) {
            A[i] = 2 + 2 * i;
            A[i] = integrate(e, low, high, A[i]);
        }
        for (uint32_t i = 0; i < count / 2; i += 1) {
            printf("%i,%.15lf\n", 2 + 2 * i, A[i]);
        }
    }
    //log(log(x)) function
    if (F) {
        printf("log(log(x)) ,%.6lf, %.6lf, %i\n", low, high, count);
        float A[count / 2];
        for (uint32_t i = 0; i < count / 2; i += 1) {
            A[i] = 2 + 2 * i;
            A[i] = integrate(f, low, high, A[i]);
        }
        for (uint32_t i = 0; i < count / 2; i += 1) {
            printf("%i,%.15lf\n", 2 + 2 * i, A[i]);
        }
    }
    //sin(x)/x function
    //need to avoid 0, since sin(0)/0 can not be computed
    if (G) {
        printf("sin(x)/x ,%.6lf, %.6lf, %i\n", low, high, count);
        float A[count / 2];
        for (uint32_t i = 0; i < count / 2; i += 1) {
            A[i] = 2 + 2 * i;
            A[i] = 2 * integrate(g, 1e-60, high, A[i]);
        }
        for (uint32_t i = 0; i < count / 2; i += 1) {
            printf("%i,%.15lf\n", 2 + 2 * i, A[i]);
        }
    }
    //exp(-x)/x function
    if (H) {
        printf("exp(-x)/x ,%.6lf, %.6lf, %i\n", low, high, count);
        float A[count / 2];
        for (uint32_t i = 0; i < count / 2; i += 1) {
            A[i] = 2 + 2 * i;
            A[i] = integrate(h, low, high, A[i]);
        }
        for (uint32_t i = 0; i < count / 2; i += 1) {
            printf("%i,%.15lf\n", 2 + 2 * i, A[i]);
        }
    }
    //exp(exp(x)) function
    if (I) {
        printf("exp(exp(x)) ,%.6lf, %.6lf, %i\n", low, high, count);
        float A[count / 2];
        for (uint32_t k = 0; k < count / 2; k += 1) {
            A[k] = 2 + 2 * k;
            A[k] = integrate(i, low, high, A[k]);
        }
        for (uint32_t i = 0; i < count / 2; i += 1) {
            printf("%i,%.15lf\n", 2 + 2 * i, A[i]);
        }
    }
    //sqrt(sin^2(x) + cos^2(x)) function
    if (J) {
        printf("sqrt(sin^2(x) + cos^2(x)) ,%.6lf, %.6lf, %i\n", low, high, count);
        float A[count / 2];
        for (uint32_t i = 0; i < count / 2; i += 1) {
            A[i] = 2 + 2 * i;
            A[i] = integrate(j, low, high, A[i]);
        }
        for (uint32_t i = 0; i < count / 2; i += 1) {
            printf("%i,%.15lf\n", 2 + 2 * i, A[i]);
        }
    }
    //synopsis and usage
    if (Z) {
        fprintf(stderr, "SYNOPSIS\n"
                        "    Approximates Numerical Integration Using Simpson's 1/3 Rule\n"
                        "\n"
                        "USAGE\n"
                        "    ./integrate [-abcdefghijp:q:n:] [-p low] [-q high] [-n count]\n"
                        "\n"
                        "OPTIONS\n"
                        "    -a                    sqrt(1 - x^4)\n"
                        "    -b                    1/log(x)\n"
                        "    -c                    exp(-x^2)\n"
                        "    -d                    sin(x^2)\n"
                        "    -e                    cos(x^2)\n"
                        "    -f                    log(log(x))\n"
                        "    -g                    sin(x)/x\n"
                        "    -h                    exp(-x)/x\n"
                        "    -i                    exp(exp(x))\n"
                        "    -j                    sqrt(sin^2(x) + cos^2(x))\n"
                        "    -n partitians         Sets Maximum number of partitions.\n"
                        "    -p low                Sets lower bound of integral interval.\n"
                        "    -q high               Sets higher bound of integral interval.\n"
                        "    -H                    Display program synopsis and usage.\n");
    }
}
