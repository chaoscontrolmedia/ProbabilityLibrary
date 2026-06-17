void bayes_v1() {
    const double EPS = 1e-9;
    vector<double> set_amounts;
    vector<double> given_amounts;

    int partitioned_sets = 0;
    double partitioned_probability = 0;
    double total_probability = 0;
    double given_total = 0.0;
    double given = 0;
    while (total_probability <= 1 + EPS) {

        //This is checked first because the user shouldn't be asked to input if p = 1.
        //is the total close to 1? (different bases)
        if (abs(total_probability - 1.0) < EPS)
        {
            cout << "\nCapacity reached. ";
            break;
        }

        //The user inputs the values as long as the condition hasn't been met of p = 1.
        cout << "\nEnter partitioned_set P(A_j) " << partitioned_sets + 1 << ": ";
        cin >> partitioned_probability;

        total_probability += partitioned_probability;
        cout << "\nTotal Probability: " << total_probability;


        if (total_probability > 1.0 + EPS) {
            double difference = total_probability - (1 + EPS);
            cout << "Value too high. Exceeded by" << difference << ".\nSubtracting last amount= "
                << partitioned_probability << "\n";
            total_probability -= partitioned_probability;
            cout << "Enter a smaller partition. \nTotal:" << total_probability;

        }
        else {
            //Store the partitioned probabilities to a vector if the values are valid.
            set_amounts.push_back(partitioned_probability);
            partitioned_sets++;
        }
    }



    cout << "\nNumber of Sets: " << partitioned_sets;
    cout << "\nAmounts: ";
    for (double val : set_amounts) {
        cout << val << " ";
    }


    bool mult;
    cout << "\nMultiply by given likelihood ?\n";
    cin >> mult;


    if (mult) {
        cout << "Enter P given values:\n";
        for (double val : set_amounts) {
            cout << "\nP given: " << val << "\n";
            cin >> given;
            //val*given;
            given_amounts.push_back(val * given);
        }


        //cout << "P Given: " << val*given;
        for (double val : given_amounts) {
            given_total += val;
            cout << val << " ";
        }
        if (given_total > 0) {
            cout << "\nGiven total: " << given_total;
            cout << "\nComplement: " << 1 - given_total;
        }
    }
    else return;

    int choice;

    //double num = a * given_b;
    cout << "\nP(A_i|B) = Choose partition index: ";
    for (int i = 0; i < set_amounts.size(); i++) {
        cout << "[" << i << "]-> " << set_amounts[i];
    }

    cin >> choice;

    if (choice >= 0 && choice < set_amounts.size()) {
        double a = set_amounts[choice];
        double given_b = given_amounts[choice];
        cout << given_b << "/" << given_total << "=" << given_b / given_total;
    }
    return;

}







