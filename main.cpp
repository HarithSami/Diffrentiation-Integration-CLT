#include <math.h>
#include <sstream>
#include <iostream>
#include "stdlib.h"
#include <fstream>
#include <string>
#include <vector>
#include "symbolic_diff.hpp"


using namespace std;

int main() {



    int option = 0;
    int int_choice = 0;



    //implement enums
    enum Menus {
        sym_dif = 1,
        num_dif,
        num_integ,
    };


    cout << "Select one of the following functions\n"
        << "1.Symbolic Diffrentiation\n"
        << "2.Numeric Diffrentiation\n"
        << "3.Numeric Integration" << endl;
    int choice;
    cin >> choice;

    if (choice == sym_dif) {
        double symbolic_diffrentiation= symbolic_diff();

    }
    else if (choice == num_dif || choice == num_integ) {
        std::string csv_file{};
        std::cout << "Type the name of wanted data set file (with the extension) \n"
            "You can also include your own CSV files (must contain 2 columns representing x & y values.\n"
            "Existing CSV document [ file.csv | TBA | TBA | TBA ] \n";
        std::cin >> csv_file;
        enum num_diff_Menus {
            original_data_set = 1,
            diffrentiated_data_set,
            integrated_data_set,
            go_back,
        };
        std::cout << "Select one of the following:"
            "[1] show original data set"
            "[2] show diffrential data set"
            "[3] show integrated data set"
            "[4] go back";
        int numerical_choice;
        std::cin >> numerical_choice;
        if (numerical_choice == original_data_set) {

        }
        else if (numerical_choice == diffrentiated_data_set) {

        }
        else if (numerical_choice == integrated_data_set) {

        }
        else if (numerical_choice == go_back) {

        }
        else {
            std::cout << "you have neterd a false value";
        }







    }

    else {
        cout << "false value\n";

    }

    return 0;


    }

