#pragma once
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>

class StatisticsUtils {
public:
    static double calculate_mean(const std::vector<int>& data);
    static double calculate_median(std::vector<int> data);
    static int find_mode(const std::map<int, int>& frequency_map);
    static std::map<int, double> calculate_percentages(const std::map<int, int>& counts, int total);
};