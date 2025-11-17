#pragma once

#include "Matrix.h"

#include <vector>

struct LinearSystem {
    Matrix A;
    std::vector<double> b;
};

LinearSystem GEPP(Matrix& A, std::vector<double>& b, bool in_place=true);
std::vector<double> backsubstitute(const Matrix& A, const std::vector<double>& b);

// Convenience function for solving a system with GEPP and backsubstitute.
std::vector<double> solve(Matrix& A, std::vector<double>& b, bool eliminate_in_place=false);

// ----- internal -----
size_t find_pivot_index(const Matrix& A, size_t col);
void validate_system(const Matrix& A, const std::vector<double>& b);

// standard in-place Gaussian elimination with partial pivoting
void _GEPP(Matrix& A, std::vector<double>& b);
