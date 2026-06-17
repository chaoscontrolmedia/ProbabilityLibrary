#include <iostream>
#include "utils.h"

using namespace std;




/* Geometric Distribution*/

double geo_expected_value(double p) { return 1.0 / p; }
double geo_variance(double p) { return (1.0 - p) / (p * p); }
double geo_st_dev(double p) { return find_sq_root(geo_variance(p)); }


double geo_pmf(int x, double p) {
    if (x < 1) return 0.0; // Geometric distribution is defined for x >= 1
    return intFastPow(1.0 - p, x - 1) * p;
}






double geo_cdf_recursive(int k, double p) {
    if (k < 1) return 0.0; // Geometric distribution is defined for k >= 1
    return 1.0 - intFastPow(1.0 - p, k);
}

//Number of Bernoulli trials for the first success
double geometricPMF(double p, int k) {
    //There should be at least try and p has to be in between 0 and 1.
    if (p <= 0 || p > 1 || k < 1) return 0;
    double failure_rate = 1 - p;

    double total_prob = 1;
    for (int i = 1; i < k; i++) {
        total_prob *= failure_rate;
    }
    double result = total_prob * p;
    return result;
}





void geo_info(double p, int x) {
    double expected_value = geo_expected_value(p);
    double variance = geo_variance(p);
    double st_dev = geo_st_dev(p);
    double pmf = geo_pmf(x, p);
    double cdf = geo_cdf(x, p);

    cout << "Trials until first success: " << x << "\n";
    cout << "Probability of success on each trial: " << p << "\n\n";
    cout << "P(X=" << x << ") = " << pmf << "\n";
    cout << "P(X <= " << x << ") = " << cdf << "\n";
    cout << "Expected Value (1/p): " << expected_value << "\n";
    cout << "Variance ((1-p)/p^2): " << variance << "\n";
    cout << "Standard Deviation (sqrt((1-p)/p^2)): " << st_dev << "\n";
}


void geo_run() {
    double p;
    int k;
    cout << "Geometric Distribution - Measures probability of first success on the k-th trial\n";
    cout << "Probability of success: ";
    cin >> p;
    cout << "Number of trials until first success (k): ";
    cin >> k;
    cout << "\n\n";
    geo_info(p, k);
}

