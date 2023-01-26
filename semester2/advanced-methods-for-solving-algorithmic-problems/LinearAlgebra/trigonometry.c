#include "trigonometry.h"

double sinus(double x, double epsilon) {
	double term = x;
	double result = 0;
	int iter = 1;

	while (fabs(term) > epsilon) {
		result += term;
		term = (term * (-1.0) * x * x) / ((2.0 * iter) * (2.0 * iter + 1.0));
		++iter;
	}

	return result;
}

double cosinus(double x, double epsilon) {
	double term = 1;
	double result = 0;
	int iter = 1;

	while (fabs(term) > epsilon) {
		result += term;
		term = (term * (-1.0) * x * x) / ((2.0 * iter) * (2.0 * iter - 1.0));
		++iter;
	}

	return result;
}