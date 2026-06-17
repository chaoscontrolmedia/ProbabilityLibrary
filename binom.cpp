#include <iostream>
#include "utils.h"






double binom_pmf(int n, int x, double p) {
	if (x < 0 || x > n) return 0.0; // Binomial distribution is defined for 0 <= x <= n
	long double nCr = combinations_stable(n, x);
	return nCr * intFastPow(p, x) * intFastPow(1.0 - p, n - x);
}

double binom_cdf(int n, int x, double p) {
	double cdf = 0.0;
	for (int i = 0; i <= x; ++i) {
		cdf += binom_pmf(n, i, p);
	}
	return cdf;
}

double binom_expected_value(int n, double p) { return n * p; }
double binom_variance(int n, double p) { return n * p * (1 - p); }
double binom_st_dev(int n, double p) { return find_sq_root(binom_variance(n, p)); }


void bin_info(int n, int x, double p) {
	double expected_value = binom_expected_value(n, p);
	double variance = binom_variance(n, p);
	double st_dev = binom_st_dev(n, p);
	double pmf = binom_pmf(n, x, p);
	double cdf = binom_cdf(n, x, p);
	std::cout << "Number of trials: " << n << "\n";
	std::cout << "Number of successes: " << x << "\n";

	std::cout << "Probability of success on each trial: " << p << "\n\n";
	std::cout << "P(X=" << x << ") = " << pmf << "\n";
	std::cout << "P(X <= " << x << ") = " << cdf << "\n";
	std::cout << "Expected Value (np): " << expected_value << "\n";
	std::cout << "Variance (np(1-p)): " << variance << "\n";
	std::cout << "Standard Deviation (sqrt(np(1-p))): " << st_dev << "\n";
}



void bin_run() {
	int n, x;
	double p;
	std::cout << "Binomial Distribution - Measures probability of x successes in n trials\n";
	std::cout << "Number of trials (n): ";
	std::cin >> n;
	std::cout << "Number of successes (x): ";
	std::cin >> x;
	std::cout << "Probability of success on each trial: ";
	std::cin >> p;
	std::cout << "\n\n";
	bin_info(n, x, p);
}







