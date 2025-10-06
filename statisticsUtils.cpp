#include "statisticsUtils.h"

double StatisticsUtils::calculate_mean(const std::vector<int>& data) {
    if (data.empty()) return 0.0;
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

double StatisticsUtils::calculate_median(std::vector<int> data) {
    if (data.empty()) return 0.0;
    std::sort(data.begin(), data.end());
    size_t size = data.size();
    if (size % 2 == 0) {
        return (data[size / 2 - 1] + data[size / 2]) / 2.0;
    }
    else {
        return data[size / 2];
    }
}

int StatisticsUtils::find_mode(const std::map<int, int>& frequency_map) {
    if (frequency_map.empty()) return 0;
    auto max_it = std::max_element(frequency_map.begin(), frequency_map.end(),
        [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second < b.second;
        });
    return max_it->first;
}

std::map<int, double> StatisticsUtils::calculate_percentages(const std::map<int, int>& counts, int total) {
    std::map<int, double> percentages;
    if (total == 0) return percentages;
    for (const auto& pair : counts) {
        percentages[pair.first] = (static_cast<double>(pair.second) / total) * 100.0;
    }
    return percentages;
}