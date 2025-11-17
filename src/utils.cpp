#include "utils.h"

#include <iostream>
#include <vector>

void print_vector(const std::vector<double>& vec) {
    size_t length = vec.size();

    std::cout << "[";

    for(size_t i = 0; i < length; ++i) {
        std::cout << " " << vec[i];
    }

    std::cout << " ]";
}

std::vector<double>& swap(std::vector<double>& vec, size_t i, size_t j) {
    double temp = vec[i];
    vec[i] = vec[j];
    vec[j] = temp;

    return vec;
}
