#include "utils.h"
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;


/*==============Conversions============*/
bool probability_check(double e) {
    return e > 0 && e <= 1;
}
// probability of success
double probability(int e, int s) {
    return static_cast<double>(e) / s;
}

double convert_to_percentage(int e, int s) {
    return probability(e, s) * 100;
}

//P(Ac) = 1 = P(A)
double complement_probability(int e, int s) {
    return 1 - probability(e, s);
}
double complement_percentage(int e, int s) {
    return 100 - convert_to_percentage(e, s);
}





/*====Sample Space=======*/

vector<double> add_supports(int n) {
    vector<double> support_vector;
    for (int i = 1; i <= n; i++) {
        double val;
        cout << "Support " << i << ": ";
        cin >> val;
        support_vector.push_back(val);
    }
    return support_vector;
}


double sum_values(vector<double> values) {
    double sum = 0;
    for (auto i : values) {
        sum += i;
    }
    return sum;
}







 /*=================Conditional Probability================*/

 double probability_a_given_b(double a, double b) {
	if(a <= 0 || a > 1 || b <= 0 || b > 1) {
		throw std::invalid_argument("Probabilities must be between 0 and 1");
	}
	return (a * b) / b;
}

 double proability_a_or_b(double a, double b) {
	if(a <= 0 || a > 1 || b <= 0 || b > 1) {
		throw std::invalid_argument("Probabilities must be between 0 and 1");
	}
	return a + b - (a * b);
}


double probability_a_and_b(double a, double b) {
	if(a <= 0 || a > 1 || b <= 0 || b > 1) {
		throw std::invalid_argument("Probabilities must be between 0 and 1");
	}
	return a * b;
}

vector<double> add_probabilities() {
    vector<double> probability_vector;

    double p;
    int choice;

    while (true) {
        cout << "p-Probability of success:\n";
        cout << "Enter Decimal(1), Enter Fraction(2), Exit(-1): ";
        cin >> choice;

        if (choice == -1) {
            break;
        }

        if (choice == 1) {
            cout << "Enter Decimal: ";
            cin >> p;
        }
        else if (choice == 2) {
            int e, s;
            cout << "e (success outcomes): ";
            cin >> e;
            cout << "s (total outcomes): ";
            cin >> s;

            p = convert_to_percentage(e, s);

            cout << "Fraction: " << e << "/" << s << "\n";
            cout << "Decimal: " << p << "\n";
            cout << "Complement: " << (s - e) << "/" << s << "\n";
            cout << "Complement decimal: "
                << convert_to_percentage(s - e, s) << "\n";
        }
        else {
            cout << "Invalid choice.\n";
            continue;
        }

        if (probability_check(p)) {
            probability_vector.push_back(p);
            cout << "Probability added: " << p << "\n";
        }
        else {
            cout << "Invalid probability (must be 0 to 1).\n";
        }
    }

    return probability_vector;
}




/*========================*Bayes Theorem==============================*/

vector<double> partitioned_sets() {
    const double EPS = 1e-9;
    vector<double> priors;
    int partitioned_sets = 0;
    double partitioned_probability = 0;
    double total_probability = 0;



    while (total_probability <= 1 + EPS) {

        //This is checked first because the user shouldn't be asked to input if p = 1.
        //is the total close to 1? (different bases)
        if (abs(total_probability - 1.0) < EPS)
        {
            cout << "\nCapacity reached.\n";
            break;
        }

        //The user inputs the values as long as the condition hasn't been met of p = 1.
        cout << "\nEnter partitioned_set P(A_j) " << partitioned_sets + 1 << ": ";
        cin >> partitioned_probability;

        total_probability += partitioned_probability;
        cout << "\nTotal Probability: " << total_probability;


        if (total_probability > 1.0 + EPS) {
            double difference = total_probability - (1 + EPS);
            cout << "Value too high. Exceeded by" << difference << ".\nSubtracting last amount= " << partitioned_probability << "\n";
            total_probability -= partitioned_probability;
            cout << "Enter a smaller partition. \nTotal:" << total_probability;

        }
        else {
            //Store the partitioned probabilities to a vector if the values are valid.
            priors.push_back(partitioned_probability);
            partitioned_sets++;
        }
    }
    cout << "\nNumber of Sets: " << partitioned_sets;
    cout << "\nAmounts: ";
    for (double val : priors) {
        cout << val << " ";
    }

    return priors;


}
vector<double> likelihoods(vector<double>priors) {
    double given = 0;
    vector<double> joint_probabilities;
    cout << "\nEnter P given values:\n";
    for (double val : priors) {
        cout << "\nP given: " << val << "\n";
        cin >> given;
        joint_probabilities.push_back(val * given);
    }

    for (double val : joint_probabilities) {
        cout << val << " ";
    }
    return joint_probabilities;
}
double probability_summation(vector<double> joint_probabilities) {
    /*?P(Ai?)P(B?Ai?)*/
    double given_total = 0.0;
    //cout << "P Given: " << val*given;
    for (double val : joint_probabilities) {
        given_total += val;
    }
    cout << "\nTotal probability = " << given_total;
    return given_total;
}
double bayes_numerator(vector<double> partitioned_sets,
vector<double> joint_probabilities, double given_total) {
    int choice;
    //double num = a * given_b;
    cout << "\n\nP(A_i|B) = Choose partition index: \n";
    for (int i = 0; i < partitioned_sets.size(); i++) {
        cout << "[" << i << "]-> " << partitioned_sets[i] << " ";
    }
    cin >> choice;
    if (choice >= 0 && choice < partitioned_sets.size()) {
        double given_b = joint_probabilities[choice];
        double result = given_b / given_total;
        cout << given_b << "/" << given_total << "= ";
        return result;
    }
    return given_total;
}
void bayes_theorem() {
    vector<double> a = partitioned_sets();
    vector<double> b = likelihoods(a);
    double Psum = probability_summation(b);
    double c = bayes_numerator(a, b, Psum);
    cout << c;
}





























 /*========================Logs and exponents=================================================*/
long double intFastPow(double base, int exponent) {
    if (exponent == 0) return 1.0L;

    long double result = 1.0L;
    long double b = base;
    int exp = abs(exponent);

    while (exp > 0) {
        if (exp % 2 == 1)   // if exponent is odd
            result *= b;

        b *= b;             // square the base
        exp /= 2;           // halve the exponent
    }

    return (exponent > 0) ? result : 1.0L / result;
}


//Naive implementation of power function, can be optimized with fast exponentiation
long double intCustomPow(double base, int exponent) {
    //1*1, 2*2 3*3...
    if (exponent == 0) return 1;

    int abs_exp = (exponent > 0) ? exponent : -exponent;
    long double result = 1.0L;

    for (int i = 1; i <= abs_exp; i++) {
        result *= base;
    }
    if (exponent > 0) return result;
    else return 1 / result;
}


 void customLog(int base, long long result){
     //int exponent = 1;
     int operations = 0;
     int exponent = 1;
     //use while loop because result is unknown
     //multiply exponent by base by result until exponent is no longer less than the result.
     while (exponent < result) {
         exponent *= base;
         operations++;
     }
 }



double find_sq_root(double x) {
    double eps = 1e-9; // small value for precision
    double left = 0.0, right = max(1.0, x); // initialize search range

    // Binary search to find the logarithm
    while (right - left > eps) {
        double mid = (left + right) / 2.0; // calculate midpoint
        if (mid * mid <= x) {
            left = mid; // adjust search range
        }
        else {
            right = mid; // adjust search range
        }
    }

    return left; // return the result
}

//Can be optimized for large n with squaring instead of naive loop
double find_nth_root(double x, int n) {
    if (x == 0) return 0;
    if (n <= 0) throw invalid_argument("Root must be >0");

    double eps = 1e-9; // small value for precision
    double left, right;


    // Set the initial bounds
    if (x < 1.0) {
        left = 0.0;
        right = 1.0;
    }
    else {
        left = 1.0;
        right = x;
    }

    // Binary search to find the logarithm
    while ((right - left) > eps) {
        double mid = (left + right) / 2.0; // calculate midpoint

        double mid_power = 1.0;
        for (int i = 0; i < n;++i) {
            mid_power *= mid;
        }
        if (mid_power < x) {
            left = mid; // adjust search range
        }
        else {
            right = mid; // adjust search range
        }
    }
    return (left + right) / 2; // return the result
}

/*=============================Combinatorics==============================*/

//Time = O(n), Space = O(n)-Call Stack
 static long long factorial(int n) {
     //if(n == 1)cout << " ";
     if (n <= 1) {
         cout << " = ";
         return 1;
     }
     //cout << n;
     return n * factorial(n - 1);
 }



/*Permutations*/

/* Binomial Random  Variable*/
//Stable and efficient way to calculate nPk without overflow
long long permutations_product_form(int n, int k) {
    if (k<0 || k>n) return 0.0L;

    long long result = 1;
    for (int i = 1; i <= k; i++) {
        result *= (n - i + 1);
    }
    return result;
}


/* Binomial Random  Variable*/
//Stable and efficient way to calculate n choose k without overflow
long double combinations_product_form(int n, int k) {
    if (k < 0 || k > n) return 0.0L;
    if (k == 0 || k == n) return 1.0L;


    if (k > n - k) k = n - k;

    long double result = 1.0L;

    for (int i = 1; i <= k; ++i) {
        result *= (n - k + i);
        result /= i;
    }
    return result;
}


//C(n,k), or n!/n!(n-k)!
//Naive implementation, can be optimized with the product form to avoid overflow and improve efficiency.
static long long combinations(int n, int k) {
    if ((k == 0) || (k == n)) {
        return 1;
    }
    else {
        return factorial(n) / (factorial(k) * factorial(n - k));
    }
}




long double count_sequences(int n, int k) {
    if (k < 0 || k > n) return 0.0L;
    if (k == 0 || k == n) return 1.0L;


    if (k > n - k) k = n - k;

    long double result = 1.0L;

    for (int i = 1; i <= k; ++i) {
        result *= (n - k + i);
        result /= i;
    }
    return result;
}


//Time = O(n), Space = O(1)
void print_factorial_iterative(int n) {
    int factorial = 1;
    for (int i = 1; i <= n; i++) {
        factorial *= i;
        cout << factorial << " ";
    }
}

//Time = O(n), Space = O(n)-Call Stack
static long long print_factorial_recursive(int n) {
    //if(n == 1)cout << " ";
    if (n <= 1) {
        cout << " = ";
        return 1;
    }
    cout << n;
    return n * print_factorial_recursive(n - 1);
}




/*================Expected Value====================*/

double expected_value(vector<double>probabilities) {
    double e = 0;
    for (auto i : probabilities) {
        e += i;
    }
    return e;
}


//E[x] = sigma all x (x*f(x))
double expected_value_for_pmf(const vector<int>& inputs, const vector<double>& pmf) {
    double expectation = 0;

    for (size_t i = 0; i < inputs.size(); i++) {
        expectation += inputs[i] * pmf[i];
    }

    return expectation;
}





/*================*Display Function====================*/

void print_vectors(vector<double> values) {
    for (auto i : values) {
        cout << i << " ";
    }
}



vector<double> uniform_probability_distribution(vector<double> values) {
    double p;
    vector<double> probability_list;
    cout << "Enter p: ";
    cin >> p;
    for (double i : values) {
        probability_list.push_back(i * p);
    }
    return probability_list;
}

vector<double> distinct_probabilities(vector<double>values) {
    //Add check for summing values to 1 later
    vector<double>probability_list;
    int frac_choice;
    int e;
    int s;
    //double converted_fraction();
    double p;
    //for every value in the element
    for (double i : values) {
        cout << "Add p for " << i << " as a fraction? 0-Yea, 1-No";
        cin >> frac_choice;
        if (frac_choice == 0) {
            cout << "Enter E and S";
            cin >> e >> s;
            probability_list.push_back(i * ((double)e / s));
        }
        else {
            cout << "Enter p: ";
            cin >> p;
            probability_list.push_back(i * p);
        }
    }
    return probability_list;
}

void probability_input_values() {
    int rel_choice;
    cout << "Enter the probability of event A: ";
    double a;
    cin >> a;
    cout << "Enter the probability of event B: ";
    double b;
    cin >> b;
    cout << "Relationship of events"

        "\n1.Either one or the other happens";
    "\n2.Both events happen. ";
    "\n3. one happens given the other";

    cin >> rel_choice;
    try {
        double result = probability_a_given_b(a, b);
        cout << "The probability of A given B is: " << result << endl;
    }
    catch (const std::invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }
}



double expected_value_uniform_distribution() {
    int x = 0;
    double total = 0;
    int count = 0;
    while (true) {
        cout << "Enter x: ";
        cin >> x;
        total += x;
        count++;
        if (x < 0) {
            cout << "Negative value entered. Stopping input.\n";
            break;
		}
    }
    if (count != 0) {
        double mu = total / count;
        return mu;
    }
}


void options_length() {
    int choices, length;
    cout << "How many choices? ";
    cin >> choices;
    cout << "How many times can a choice be made? ";
    cin >> length;

    cout << "Total Options: " << intPowDisplay(choices, length);

}


long double intPowDisplay(double base, int exponent) {
    if (exponent == 0) return 0;
    cout << base << "^" << exponent << " = ";
    if (exponent > 0)
    {
        return intCustomPow(base, exponent);
    }

    else {

        return 1.0 / intCustomPow(base, -exponent);
    }
}


void multinomial(int n) {
    vector<int> options_array;
    int orig_n = n;
    int k = 0;


    cout << "Total arrangements: " << n << "!\n";
    while (n > 0) {

        if (n == 1) {
            cout << "Only 1 left.";
            options_array.push_back(1);
            n = 0;
            break;
        }

        cout << "How many options chosen from " << n << "!? ";
        cin >> k;

        if (k <= 0) {
            cout << "Invalid";
            continue;
        }

        if (k > n) {
            cout << "K is bigger than n\n";
            options_array.push_back(n);
            break;
        }
        else {
            options_array.push_back(k);
            n -= k;
        }
    }

    cout << "Total selections/Combinations for selections:";
    cout << orig_n << "!/";
    for (int val : options_array) {
        cout << val << "! ";
    }

}



void permutations_display(int n, int k) {
    long long npk = permutations_product_form(n, k);
    cout << "P(" << n << "," << k << ")";
    cout << "\n= " << n << "!/" << (n - k) << "!\n= ";
    factorial_iterative_display_range(n, k);
    cout << "= " << npk;
}









void factorial_iterative_display(int n) {
    if (n < 0) {
        cout << "Undefined for negative integers.\n";
        return;
    }
    int current = n;
    //cout << n << "! = ";
    while (current >= 1) {
        cout << current;
        if (current > 1) cout << "*";
        current--;
    }
    cout << "\n";
}



void factorial_iterative_display_range(int n, int k) {

    if (n < 0 || k<0 || k>n) {
        cout << "Undefined for negative integers.\n";
        return;
    }
    int current = n;
    int stop = n - k + 1;


    //cout <<n << "!/" <<  (n-k) << "! = ";
    while (current >= stop) {
        cout << current;
        if (current > stop) cout << "*";
        current--;
    }
    cout << "\n";

}


void combinations_display(int n, int k) {
    long long nck = combinations_product_form(n, k);
    cout << "C(" << n << "," << k << ")";
    cout << "\n= " << n << "!/" << k << "!" << (n - k) << "!\n= ";
    factorial_iterative_display_range(n, k);
    cout << " /";
    factorial_iterative_display(k);
    cout << "= " << nck;
}






 void counting_trial(){
     bool cont = true;
     int experiments = 0;
     int total= 0;
     int r;
     int options = 1;//Pick something
     while (cont = true){
         cout << "Experiment " << experiments;
         cout << "Enter ";
         cin >> r;
         total*=r;
         cout << "Total" << total;
         if(r == 1){
             cont = false;
         }
     }
 }




//pi notation
int fundamental_counting_principle_display() {
    int outcomes = 1;
    int choice = 0;
    int r = 1;
    int trials_cont = true;
    int experiments = 1;

    cout << "n1 * n2...nk pos.outcomes";

    while (trials_cont) {
        cout << "\nExperiment " << experiments;

        cin >> r;
        outcomes *= r;
        cout << "\nTotal: " << outcomes;
        experiments++;
        if (r == 0) {
            trials_cont = false;
            break;
        }
    }
}




//Menu option, so no parameters;
void combinatorial_program() {
    int n, k;
    cout << "Counting Problem\n";
    bool order_matters, reps_allowed;
    cout << "Does order matter?";
    cin >> order_matters;
    cout << "Are repetitions allowed?";
    cin >> reps_allowed;


    int mode = 2 * order_matters + reps_allowed;

    switch (mode) {
    case 0:
        // no order, no repetition
        break;

    case 1:
        // no order, repetition-Combinations(Binomial)
        cout << "Combinations-Order doesn't matter, no reps\n";
        cout << "How many options? ";
        cin >> n;
        cout << "How many are chosen? ";
        cin >> k;
        combinations_display(n, k);
        break;

    case 2:
        // order, no repetition(permutations)
        bool choice;
        cout << "Permutations-Order matters, no reps\n";
        cout << "How many options? ";
        cin >> n;
        cout << "How many are chosen? ";
        cin >> k;

        cout << "Are there multiple categories of selections";
        cin >> choice;

        if (choice == 1) {
            multinomial(n);
        }
        else {
            permutations_display(n, k);
        }
        break;

    case 3:
        // order, repetition
        //Ex. PIN codes, license plates, passwords
        fundamental_counting_principle_display;
        break;
    }

}

































