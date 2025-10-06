#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "experimentRunner.h"

int main() {
    try {
        int n, num_experiments;
        std::cout << "Enter n (max pip value): ";
        std::cin >> n;

        std::cout << "Enter number of experiments: ";
        std::cin >> num_experiments;
         if (num_experiments <= 0) throw std::invalid_argument("Number of experiments must be positive!");

        ExperimentRunner runner(num_experiments); 
        ExperimentResult result = runner.run_single_experiment(n); 

        std::cout << "\n RESULTS for n = " << n << "\n";
        std::cout << "Total tiles: " << result.total_tiles << "\n";
        std::cout << "Average size: " << result.average_size << "\n";
        std::cout << "Median size: " << result.median_size << "\n";
        std::cout << "Most frequent size: " << result.most_frequent_size << "\n";
        

        std::cout << "\nSize distribution (%):\n";
        for (const auto& [size, percent] : result.size_percentages) {
            std::cout << "  " << size << ": " << std::fixed << std::setprecision(2)
                      << percent << "%\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Input/Run error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}

