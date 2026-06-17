#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath> // for log

using namespace std;


/*-----------------------------------------
  Natural log via series:
  ln(1 - y) = - sum_{k=1}^∞ y^k / k
  Valid for |y| < 1
-----------------------------------------*/
long double ln1_minus(long double y, int terms = 40) {
    long double sum = 0.0L;
    long double power = y;

    for (int k = 1; k <= terms; ++k) {
        sum += power / k;
        power *= y;
    }
    return -sum;
}

/*-----------------------------------------
  log10 using ln series
-----------------------------------------*/
long double log10_custom(long double x) {
    const long double LN10 = 2.302585092994045684L;

    if (x <= 0.0L)
        return -1e18L; // log(0)

    // Reduce to (0,1) using inversion
    bool inverted = false;
    if (x > 1.0L) {
        x = 1.0L / x;
        inverted = true;
    }

    long double ln_x = ln1_minus(1.0L - x);
    long double log10_x = ln_x / LN10;

    return inverted ? -log10_x : log10_x;
}

/*-----------------------------------------
  log10(n choose k) using discrete sum
-----------------------------------------*/
long double log10_combinations(int n, int k) {
    if (k < 0 || k > n) return -1e18L;
    if (k == 0 || k == n) return 0.0L;

    if (k > n - k) k = n - k;

    long double result = 0.0L;
    for (int i = 1; i <= k; ++i) {
        result += log10_custom(n - k + i);
        result -= log10_custom(i);
    }
    return result;
}



// Compute log10 of factorials up to n and store in a table
vector<long double> compute_log_factorial_table(int n) {
    vector<long double> log_table(n + 1, 0.0L);
    for (int i = 1; i <= n; ++i) {
        log_table[i] = log_table[i - 1] + log10(i);
    }
    return log_table;
}



// Compute log10(C(n,x)) using sum of logs
long double log_combinations_discrete(int n, int x) {
    if (x < 0 || x > n) return -1e18L; // log(0)
    if (x == 0 || x == n) return 0.0L;  // log(1)
    if (x > n - x) x = n - x;          // symmetry

    long double result = 0.0L;
    for (int i = 1; i <= x; i++) {
        result += log10(n - x + i) - log10(i);
    }
    return result;
}

// Compute log10 P(X=x) for Binomial(n,p)
long double log_binomial_probability(int n, int x, double p) {
    long double logC = log_combinations_discrete(n, x);
    long double logP = logC + x * log10(p) + (n - x) * log10(1.0 - p);
    return logP;
}


void factorials_using_logs() {
    int n = 5;
    int x = 2;
    compute_log_factorial_table(n);
    cout << log_combinations_discrete(n, x);
    cout << log_binomial_probability(n, x, .8);

}

// constexpr double E = 2.718281828459045;
//
//long double log_binomial_probability(
//    int n,
//    int x,
//    double p
//) {
//
//
//    if (x < 0 || x > n) return -1e18L; // log(0)
//
//    // log(n choose x)
//    long double log_comb = 0.0L;
//    for (int k = 1; k <= x; ++k) {
//        log_comb += customLog(n - x + k, E);
//        log_comb -= customLog(k, E);
//    }
//
//    // x * log(p) + (n-x) * log(1-p)
//    long double log_prob =
//        log_comb
//        + x * customLog(p, E)
//        + (n - x) * customLog(1.0 - p, E);
//
//    return log_prob;
//}
//







int main() {

    factorials_using_logs();


    // vector<long double> table = compute_log_table(10);

    // for (int i = 0; i < table.size(); ++i) {
    //     cout << "log10(" << i << "!) = " << table[i] << endl;
    // }


    // int n = 2025;
    // int x = 1000;
    // double p = 1.0 / 6.0;

    // long double logP = log_binomial_probability(n, x, p);

    // cout << setprecision(6) << scientific;
    // cout << "log10 P(X=" << x << ") = " << logP << "\n";
    // cout << "P(X) ≈ 10^" << logP << "\n";

    //     const int n = 2025;
    // const int x = 1000;
    // const double p = probability(1, 6);

    // long double log10_p     = log10_custom(p);
    // long double log10_1mp   = log10_custom(1.0 - p);
    // long double log10_comb  = log10_combinations(n, x);

    // long double log10_P =
    //       log10_comb
    //     + x * log10_p
    //     + (n - x) * log10_1mp;

    // cout << scientific << setprecision(6);
    // cout << "log10 P(X = " << x << ") = " << log10_P << '\n';
    // cout << "P(X = " << x << ") ≈ 10^" << log10_P << '\n';



    return 0;
}



// #include <iostream>
// #include <iomanip>
// #include <vector>
// using namespace std;


// // Series-based natural log of y (0 < y < 2) using ln(1-z) expansion
// long double ln_series(double y, int terms = 30) {
//     if (y <= 0) throw invalid_argument("ln undefined for y <= 0");
//     double z = 1.0 - y; // ln(y) = -sum(z^k/k)
//     long double sum = 0.0L;
//     long double power = z;
//     for (int k = 1; k <= terms; ++k) {
//         sum += power / k;
//         power *= z;
//     }
//     return -sum;
// }

// // Convert ln -> log10
// long double log10_series(double y, int terms = 30) {
//     const long double LN10 = 2.302585092994045684L; // ln(10)
//     return ln_series(y, terms) / LN10;
// }

// // Precompute log table of factorials
// vector<long double> compute_log_factorials(int n, int terms = 30) {
//     vector<long double> log_table(n + 1, 0.0L);
//     for (int i = 1; i <= n; ++i) {
//         log_table[i] = log_table[i-1] + ln_series(i, terms);
//     }
//     return log_table;
// }

// // log10 of combinations using precomputed log factorials
// long double log_combinations(int n, int x, const vector<long double>& log_table) {
//     if (x < 0 || x > n) return -1e18L;
//     if (x == 0 || x == n) return 0.0L;

//     // log(C(n,x)) = log(n!) - log(x!) - log((n-x)!)
//     long double lnC = log_table[n] - log_table[x] - log_table[n-x];
//     const long double LN10 = 2.302585092994045684L;
//     return lnC / LN10;
// }

// // log10 of Binomial Probability P(X = x)
// long double log10_binomial_probability(int n, int x, double p, const vector<long double>& log_table) {
//     long double logC = log_combinations(n, x, log_table);
//     long double log_p = log10_series(p);
//     long double log_1mp = log10_series(1.0 - p);

//     return logC + x*log_p + (n-x)*log_1mp;
// }

// int main() {
//     int n = 2025;
//     int x = 1000;
//     double p = probability(1,6); // success probability

//     // Precompute log factorials
//     vector<long double> log_table = compute_log_factorials(n);

//     // Compute log10(P(X=x))
//     long double logP = log10_binomial_probability(n, x, p, log_table);

//     cout << setprecision(6) << scientific;
//     cout << "log10 P(X = " << x << ") = " << logP << "\n";
//     cout << "P(X)  = apprpx. 10^" << logP << "\n";

//     return 0;
// }
