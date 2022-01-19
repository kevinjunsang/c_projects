#include "functions.h"
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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
	printf("%i,%.15lf\n", n,  sum);
	return 0;
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
		case 'a':
			A = true;
			break;
		case 'b':
			B = true;
			break;
		case 'c':
			C = true;
			break;
		case 'd':
			D = true;
			break;
		case 'e':
			E = true;
			break;
		case 'f':
			F = true;
			break;
		case 'g':
			G = true;
			break;
		case 'h':
			H = true;
			break;
		case 'i':
			I = true;
			break;
		case 'j':
			J = true;
			break;
		case 'n':
			count = atoi(optarg);
			break;
		case 'p':
			low = atoi(optarg);
			break;
		case 'q':
			high = atoi(optarg);
			break;
		case 'H':
			printf("hi");
			break;
		default:
			fprintf(stderr, "error\n");
			return 1;
		}
	}
	if (A) {
		printf("sqrt(1 - x^4) ,%.6lf,%.6lf,%i\n", low, high, count);
		for (uint32_t i = 2; i < count + 1; i += 2) {
			integrate(a, low, high, i);
		}
	}
}


