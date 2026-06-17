#include <iostream>
#include <vector>
#include "utils.h"

/*VS code has to be closed tp upload to Github*/



using namespace std;








void test() {
	bool uniform = false;
	bool n_known = false;
	int n;
	vector<double> supports;
	print_vectors(supports);

	cout << "Is N known? 1-yes, 2-no: ";
	cin >> n_known;


	if (n_known){

		while (true) {
			cout << "Enter support size: ";
			cin >> n;
			if (n > 0) {
				supports = add_supports(n);
				print_vectors(supports);
				break;
			}
			else {
				cout << "Support size must be greater than 0. Please try again.\n";
			}
		}
	}
	
	else {
		int alpha = 0, value = 0, count = 0;
		vector<double> supports;


		while (true)
		{
			cout << "Enter value: ";
			cin >> value;
			if (value >= 0) {
				supports.push_back(value);
				count++;
			}
			else {
				cout << "Negative value entered. Stopping input.\n";
				break;
			}
		}
	}


	while (true) {
		cout << "\n\n";
		cout << "Is p Uniform? (1 for yes, 0 for no): ";
		cin >> uniform;

		//load balancers
		if (uniform) {
			cout << "Uniform Probability Distribution:\n";
			vector<double> uniform_dist = uniform_probability_distribution(supports);
			print_vectors(uniform_dist);
			cout << "Alpha(Sum) " << sum_values(uniform_dist) << "\n";
			cout << "Expected Value: " << expected_value(uniform_dist);
			cout << "\n\n";

		}

		else {
			cout << "Distinct Probabilities:\n";
			vector<double> distinct_dist = distinct_probabilities(supports);
			print_vectors(distinct_dist);
			cout << "\n\n";
			cout << "Alpha(Sum) " << sum_values(distinct_dist) << "\n";
			cout << "Expected Value: " << expected_value(distinct_dist) << endl;



		}
	}

}


///*Binomial Distribution*/

 
 







int main() {

	test();

	//cout << "Choose a distribution:\n1. Bernoulli\n2. Binomial\n3. Geometric\n4. Negative Binomial\n";





	//geo_expected_value(0.5);
	//geo_variance(0.5);
	//geo_st_dev(0.5);
	//geo_pmf(3, 0.5);
	//geo_cdf(3, 0.5);
	//neg_bin_expected_value(3, 0.5);
	//neg_bin_variance(3, 0.5);
	//neg_bin_st_dev(3, 0.5);
	//neg_bin_pmf(0.5, 3, 2);
	//neg_bin_cdf(0.5, 3, 2);


		//neg_bin_simulation();
	//neg_bin_info(.6, 4, 4);
	//neg_bin_info(.6, 5, 4);
	//neg_bin_info(.6, 6, 4);
	//neg_bin_info(.6, 7, 4);

	//geo_info(.6, 4);


	//geo_run();
	//bin_run();
	return 0;
}