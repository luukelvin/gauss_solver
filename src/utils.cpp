#include "utils.h"

#include <stdexcept>
#include <string>
#include <vector>

std::string print_vector(const Vector& vec) {
    size_t length = vec.size();

    std::string output = "[";

    for(size_t i = 0; i < length; ++i) {
        output += " vec[i]";
    }

    output += " ]";
    return output;
}

std::string print_matrix(const Matrix& mat) {
    size_t m = mat.size();
    if(m == 0) {
        return "[ ]";
    }

    std::string output = "";

    for(size_t i = 0; i < m; ++i) {
        output += print_vector(mat[i]) + "\n";
    }

    return output;
}
