#include <iostream>
#include "utils.h"
using namespace std;

double bern_pmf(double p, int x) {
	if (x != 0 && x != 1)
	{
		throw std::invalid_argument("x must be 0 or 1");
	}
	if (p < 0.0 || p > 1.0) {
		throw std::invalid_argument("P must be between 0 and 1");
	}
	return intFastPow(p, x) * intFastPow(1.0 - p, 1 - x);
}

double bern_cdf(double p, int x) {
	if (x < 0) return 0.0;
	if (x >= 1) return 1.0;
	return 1.0 - intFastPow(1.0 - p, x + 1);
}

double bern_expected_value(double p) {
	if (p < 0.0 || p > 1.0) {
		throw std::invalid_argument("P must be between 0 and 1");
	}
	return p;
}

double bern_variance(double p) {
	if (p < 0.0 || p > 1.0) {
		throw std::invalid_argument("P must be between 0 and 1");
	}
	return p * (1 - p);
}

double bern_st_dev(double p) {
	return find_sq_root(bern_variance(p));
}

void Bernoulli_general_info() {
	cout << "\n=== Bernoulli Distribution ===\n";
	cout << "Random Variable: X ~ Bernoulli(p)\n";
	cout << "Possible Values: {0, 1}\n";
	cout << "Parameter: p = P(X = 1)\n";
	cout << "Failure Probability: q = 1 - p\n";

	cout << "\nProbability Mass Function (PMF):\n";
	cout << "P(X = 1) = p\n";
	cout << "P(X = 0) = 1 - p\n";

	cout << "\nExpected Value (Mean):\n";
	cout << "E[X] = p\n";

	cout << "\nVariance:\n";
	cout << "Var(X) = p(1 - p)\n";

	cout << "\nStandard Deviation:\n";
	cout << "SD(X) = sqrt(p(1 - p))\n";

	cout << "\nMoment Generating Function (MGF):\n";
	cout << "M_X(t) = (1 - p) + pe^t\n";

	cout << "\nCharacteristics:\n";
	cout << "- Models a single trial.\n";
	cout << "- Only two outcomes: Success (1) or Failure (0).\n";
	cout << "- Foundation of the Binomial Distribution.\n";
	cout << "- Trials are independent when used in a Binomial experiment.\n";

	cout << "\nExamples:\n";
	cout << "- Coin flip (Heads = 1, Tails = 0)\n";
	cout << "- Pass/Fail exam\n";
	cout << "- Defective/Non-defective product\n";
	cout << "- Click/No Click on an advertisement\n";
}

//Prints the PMF, CDF, expected value, variance, and standard deviation for the Bernoulli distribution given p and x.
void bern_info(double p, int x) {
	double expected_value = bern_expected_value(p);
	double variance = bern_variance(p);
	double st_dev = bern_st_dev(p);
	double pmf = bern_pmf(p, x);
	double cdf = bern_cdf(p, x);
	std::cout << "Value of X: " << x << "\n";
	std::cout << "Probability of success on each trial: " << p << "\n\n";
	std::cout << "P(X=" << x << ") = " << pmf << "\n";
	std::cout << "P(X <= " << x << ") = " << cdf << "\n";
	std::cout << "Expected Value (p): " << expected_value << "\n";
	std::cout << "Variance (p(1-p)): " << variance << "\n";
	std::cout << "Standard Deviation (sqrt(p(1-p))): " << st_dev << "\n";
}


//Runs the Bernoulli distribution info function with user input for p and x.
void bern_run() {
	double p;
	int x;
	std::cout << "Bernoulli Distribution - Measures probability of success (1) or failure (0)\n";
	std::cout << "Probability of success: ";
	std::cin >> p;
	std::cout << "Value of X (0 or 1): ";
	std::cin >> x;
	std::cout << "\n\n";
	bern_info(p, x);
}




