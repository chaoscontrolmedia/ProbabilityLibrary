#include <iostream>
#include "utils.h"


using namespace std;






double neg_bin_expected_value(double p, int k) {return k / p;}
double neg_bin_variance(double p, int k) { return k * (1 - p) / (p * p);}
double neg_bin_st_dev(double p, int k) { return find_sq_root(neg_bin_variance(p, k));}



double neg_bin_cdf(double p, int n, int k) {
    double cdf = 0.0;
    for (int i = k; i <= n; i++) {
        cdf += combinations_stable(i - 1, k - 1) * intFastPow(p, k) * intFastPow(1 - p, i - k);
    }
    return cdf;
}

double neg_bin_pmf(double p, int n, int k) {
    return combinations_stable(n - 1, k - 1) * intFastPow(p, k) * intFastPow(1 - p, n - k);
}


//Alt.form in terms of failures
double neg_bin_cdf_fails(double p,int n, int k) {
    double cdf = 0.0;
    for (int i = 0; i <= n - k; ++i) {
        cdf += combinations_stable(k + i - 1, k - 1) * intFastPow(p, k ) * intFastPow(1 - p, i);
    }
    return cdf;
}



void neg_bin_info(double p,int n, int k)  {
    double  combinations = combinations_stable(n-1,k-1);
	double expected_value = neg_bin_expected_value(p, k);
	double variance = neg_bin_variance(p, k);
	double st_dev = neg_bin_st_dev(p, k);
    double pmf = neg_bin_pmf(p, n, k);

	cout << "Trials: " << n << "\n";
	cout << "Successes: " << k << "\n\n";

	cout << "P(X=" << n << ") = " << pmf << "\n";
    cout << "CDF P(X <= " << n << ") = " << neg_bin_cdf(p, n, k) << "\n";
    cout << "Expected Value((1-p) / p): " << expected_value << "\n";
    cout << "Variance ((1-p)/p^2) : " << variance << "\n";
	cout << "Standard Deviation (sqrt((1-p)/p^2)): " << st_dev << "\n";
	
}


void neg_bin_run() {
    double p;
    int n, k;
    cout << "Negative Binomial -Measures probability of k successes out of n trials\n";
    cout << "Probability of success: ";
    cin >> p;
    cout << "Number of trials (n): ";
    cin >> n;
	cout << "Number of successes (k): ";
	cin >> k;
    cout << "\n\n";

    neg_bin_info(p, n, k);
}


