#pragma once
#include "dominoGame.h"
#include "statisticsUtils.h"
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

struct ExperimentResult {
    int n;
    int total_tiles;
    std::map<int, int> size_counts;
    double average_size;
    double median_size;
    int most_frequent_size;
    double avg_to_total_ratio;
    double median_to_total_ratio;
    std::map<int, double> size_percentages;
};

class ExperimentRunner {
private:
    int num_experiments;
    std::vector<ExperimentResult> results;

public:
    explicit ExperimentRunner(int experiments_count = 1000);

    void run_experiments(int n_min, int n_max);
    void run_experiments(const std::vector<int>& n_values);
    ExperimentResult run_single_experiment(int n, int experiments_count = -1);

    void print_results() const;
    void save_to_file(const std::string& filename) const;
    void analyze_dependencies() const;

    void set_num_experiments(int count) { num_experiments = count; }
    int get_num_experiments() const { return num_experiments; }
    const std::vector<ExperimentResult>& get_results() const;
};