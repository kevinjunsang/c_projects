#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1e-14
#define PI      3.141592653589793

static inline double Abs(double x) {
    return x < 0.0 ? -x : x;
}

double Exp(double x) {
    double term = 1.0;
    double sum = term;
    int k = 1;
    while (Abs(term) > EPSILON) {
        term *= Abs(x) / k;
        sum += term;
        k += 1;
    }
    if (x > 0) {
        return sum;
    } else {
        return 1 / sum;
    }
}

double Sin(double x) {
    while (Abs(x) > 2 * PI) {
        if (x > 0) {
            x -= 2 * PI;
        } else {
            x += 2 * PI;
        }
    }
    int sign = 1;
    double value = x;
    double term = x;
    int k = 3;
    while (Abs(term) > EPSILON) {
        term = term * (x * x) / ((k - 1) * k);
        sign = -sign;
        value += sign * term;
        k += 2;
    }
    return value;
}

double Cos(double x) {
    while (Abs(x) > 2 * PI) {
        if (x > 0) {
            x -= 2 * PI;
        } else {
            x += 2 * PI;
        }
    }
    int sign = 1;
    double value = 1.0;
    double term = 1.0;
    int k = 2;
    while (Abs(term) > EPSILON) {
        term = term * (x * x) / ((k - 1) * k);
        sign = -sign;
        value += sign * term;
        k += 2;
    }
    return value;
}

double Sqrt(double x) {
    double f = 1.0;
    while (x > 1) {
        x /= 4;
        f *= 2;
    }
    double z = 0.0;
    double y = 1.0;
    while (Abs(y - z) > EPSILON) {
        z = y;
        y = 0.5 * (z + x / z);
    }
    return y * f;
}

double Log(double x) {
    double y = 1.0;
    double f = 0.0;
    double p = Exp(y);
    while (x > p) {
        x /= p;
        f += 1;
    }
    while (Abs(p - x) > EPSILON) {
        y += x / p - 1;
        p = Exp(y);
    }
    return y + f;
}
