#include "functions.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define pi 3.14159265

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
    uint32_t count = 100;
    float low, high;
    while ((opt = getopt(argc, argv, "abcdefghijn:p:q:H:")) != -1) {
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
        case 'H': printf("hi"); break;
        default: fprintf(stderr, "error\n"); return 1;
        }
    }
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
}
