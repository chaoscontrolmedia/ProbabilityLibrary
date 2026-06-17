#include <vector>




long double intFastPow(double base, int exponent);
double find_sq_root(double x);
double find_nth_root(double x, int n);
long double combinations_stable(int n, int k);



/*===================Conversions========================*/
bool probability_check(double e);
double probability(int e, int s);
double convert_to_percentage(int e, int s);
double complement_probability(int e, int s);
double complement_percentage(int e, int s);



/*Conditional Probability*/

std::vector<double> add_probabilities(std::vector<double> values);





/*Bayes*/
std::vector<double> add_supports(int n);
std::vector<double> partitioned_sets();


std::vector<double> uniform_probability_distribution(std::vector<double> values);
std::vector<double> distinct_probabilities(std::vector<double>support_vector);
double expected_value(std::vector<double> probabilities);
double sum_values(std::vector<double> values);
void print_vectors(std::vector<double> values);



/*===Distributions=====*/


/*Bernoulli Distribution*/
double bern_pmf(int x, double p);
double bern_cdf(int x, double p);
double bern_expected_value(double p);
double bern_variance(double p);
double bern_st_dev(double p);
void bern_info(double p, int x);
void bern_run();


/*Binomial Distribution*/
double binom_pmf(int n, int k, double p);
double binom_cdf(int n, int k, double p);
double binom_expected_value(int n, double p);
double binom_variance(int n, double p);
double binom_st_dev(int n, double p);
void bin_info(int n, int x, double p);
void bin_run();



/*Geometric Distribution*/ 
double geo_expected_value(double p);
double geo_variance(double p);
double geo_st_dev(double p);
double geo_pmf(int x, double p);
double geo_cdf(int x, double p);
void geo_run();


/*Negative Binomial Distribution*/
double neg_bin_pmf(double p, int n, int k);
double neg_bin_cdf(double p, int n, int k);
double neg_bin_expected_value(int r, double p);
double neg_bin_variance(int r, double p);
double neg_bin_st_dev(int r, double p);
void neg_bin_info(double p, int n, int k);
void neg_bin_simulation();
void neg_bin_cdf_failures(double p, int n, int k);
void neg_bin_run();














