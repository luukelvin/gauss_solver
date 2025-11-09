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
