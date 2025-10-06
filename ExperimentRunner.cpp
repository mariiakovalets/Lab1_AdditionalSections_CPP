#include "ExperimentRunner.h"

ExperimentRunner::ExperimentRunner(int experiments_count)
    : num_experiments(experiments_count) {}

void ExperimentRunner::run_experiments(int n_min, int n_max) {
    results.clear();
    for (int n = n_min; n <= n_max; ++n) {
        std::cout << "Running " << num_experiments << " experiments for n = " << n << "..." << std::endl;
        results.push_back(run_single_experiment(n, num_experiments));
    }
}

void ExperimentRunner::run_experiments(const std::vector<int>& n_values) {
    results.clear();
    for (int n : n_values) {
        std::cout << "Running " << num_experiments << " experiments for n = " << n << "..." << std::endl;
        results.push_back(run_single_experiment(n, num_experiments));
    }
}

ExperimentResult ExperimentRunner::run_single_experiment(int n, int experiments_count) {
    if (experiments_count == -1) {
        experiments_count = num_experiments;
    }

    ExperimentResult result;
    result.n = n;
    result.total_tiles = (n + 1) * (n + 2) / 2;

    std::vector<int> game_sizes;
    DominoGame game(n);

    for (int i = 0; i < experiments_count; ++i) {
        int size = game.play_game();
        game_sizes.push_back(size);
        result.size_counts[size]++;
    }

    result.average_size = StatisticsUtils::calculate_mean(game_sizes);
    result.median_size = StatisticsUtils::calculate_median(game_sizes);
    result.most_frequent_size = StatisticsUtils::find_mode(result.size_counts);
    result.size_percentages = StatisticsUtils::calculate_percentages(result.size_counts, experiments_count);
    result.avg_to_total_ratio = result.average_size / result.total_tiles;
    result.median_to_total_ratio = result.median_size / result.total_tiles;

    return result;
}

void ExperimentRunner::print_results() const {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "EXPERIMENT RESULTS (" << num_experiments << " experiments each)\n";
    std::cout << std::string(50, '=') << "\n";

    for (const auto& result : results) {
        std::cout << "\n--- n = " << result.n << " ---\n";
        std::cout << "Total tiles: " << result.total_tiles << "\n";
        std::cout << "Average size: " << result.average_size << "\n";
        std::cout << "Median size: " << result.median_size << "\n";
        std::cout << "Most frequent size: " << result.most_frequent_size << "\n";
        std::cout << "Average/Total ratio: " << result.avg_to_total_ratio << "\n";
        std::cout << "Median/Total ratio: " << result.median_to_total_ratio << "\n";

        std::cout << "Size distribution (top-5):\n";
        int count = 0;
        for (const auto& pair : result.size_percentages) {
            if (count++ >= 5) break;
            std::cout << "  " << pair.first << ": " << pair.second << "%\n";
        }
    }

    analyze_dependencies();
}

void ExperimentRunner::save_to_file(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: cannot open file " << filename << std::endl;
        return;
    }

    file << "n,TotalTiles,AverageSize,MedianSize,MostFrequentSize,AvgToTotalRatio,MedianToTotalRatio,ExperimentsCount\n";

    for (const auto& result : results) {
        file << result.n << ","
            << result.total_tiles << ","
            << result.average_size << ","
            << result.median_size << ","
            << result.most_frequent_size << ","
            << result.avg_to_total_ratio << ","
            << result.median_to_total_ratio << ","
            << num_experiments << "\n";
    }

    file.close();
    std::cout << "Results saved to: " << filename << std::endl;
}

void ExperimentRunner::analyze_dependencies() const {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "DEPENDENCY ANALYSIS (" << num_experiments << " experiments)\n";
    std::cout << std::string(50, '=') << "\n";
    std::cout << "n\tAvg/Total\tMedian/Total\n";

    for (const auto& result : results) {
        std::cout << result.n << "\t"
            << std::fixed << std::setprecision(3)
            << result.avg_to_total_ratio << "\t\t"
            << result.median_to_total_ratio << "\n";
    }
}

const std::vector<ExperimentResult>& ExperimentRunner::get_results() const {
    return results;
}