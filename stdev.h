#ifndef STD_DEV_H
#define STD_DEV_H
#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>
const size_t MAX_ELEMENTS_TO_PRINT = 5;

double vec_mean(std::vector<double> const & vec) {
    return std::accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
}

double vec_stddev(std::vector<double> const & vec)
{
    double mean = vec_mean(vec);
    double sq_sum = std::inner_product(vec.begin(), vec.end(), vec.begin(), 0.0,
        [](double const & x, double const & y) { return x + y; },
        [mean](double const & x, double const & y) { return (x - mean)*(y - mean); });
    return std::sqrt(sq_sum / vec.size());
}

void vec_print(std::vector<double> const & vec) {
    std::cout << "values = ["
    for (int i = 0; i < std::min(MAX_ELEMENTS_TO_PRINT, vec.size()); i++) {
        std::cout << vec[i] <<", ";
    }
    std::cout << "...]\n";
    std::cout << "mean: " << vec_mean(vec) << " +- " << vec_stddev(vec) << "\n";
}

#endif