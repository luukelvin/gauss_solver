#include "utils.h"
#include "Matrix.h"
#include "Solver.h"

#include <cmath>
#include <stdexcept>
#include <iostream>

LinearSystem GEPP(Matrix& A, std::vector<double>& b, bool in_place) {
    /**
     * Gaussian elimination with scaled row pivoting.
     *
     * Elimination may be done in-place or on copies by setting the in_place flag.
     *
     */

    if (in_place) {
        _GEPP(A, b);
        return {A, b};
    }
    else {
        Matrix A_copy = A;
        std::vector<double> b_copy = b;
        _GEPP(A_copy, b_copy);
        return {A_copy, b_copy};
    }
}

void _GEPP(Matrix& A, std::vector<double>& b) {
    /**
     * Gaussian elimination with scaled row pivoting.
     *
     * WARNING: Performs elimination in-place!
     */

    validate_system(A, b);
    size_t n = A.shape().second;
    for (size_t i = 0; i < n; i++) {
        // Get pivot row and permute
        size_t pivot_idx = find_pivot_index(A, i);
        A.permute_rows(i, pivot_idx);
        swap(b, i, pivot_idx);

        // Subtract multiples of row i from the rows below to zero  out the
        // entry in column i.
        double a_ii_inv = 1/A(i,i);
        for (size_t j = i+1; j < n; j++) {
            double elim_factor = A(j,i) * a_ii_inv;
            A(j,i) = 0.0;
            for (size_t k = i+1; k < n; k++) {
                A(j,k) = A(j,k) - elim_factor * A(i,k);
            }
            b[j] = b[j] - elim_factor * b[i];
        }
    }
}

std::vector<double> backsubstitute(const Matrix& A, const std::vector<double>& b) {
    size_t n = A.shape().second;
    std::vector<double> solution (n, 0.0);
    for (size_t i = n; i-- > 0; ) {
        // Decrement i immediately after checking condition to avoid overflow
        // since we need to get to i==0.
        double sum = 0.0;
        for (size_t j = n-1; j > i; j--) {
            sum += A(i,j) * solution[j];
        }
        solution[i] = (b[i] - sum) / A(i,i);
    }
    return solution;
}

std::vector<double> solve(Matrix& A, std::vector<double>& b, bool eliminate_in_place) {
    /**
     * Solves Ax = b using Gaussian elimination with partial pivoting.
     *
     * Set the eliminate_in_place flag to perform the elimination in-place on
     * A and b.
     */

    LinearSystem sys = GEPP(A, b, eliminate_in_place);
    return backsubstitute(sys.A, sys.b);
}

size_t find_pivot_index(const Matrix& A, size_t col) {
    /**
     * Gets the index of the pivot row for scaled row pivoting in the specified
     * column. (I.e. for the col-th elimination step).
     */

    const size_t n = A.shape().second; 

    if (col < 0 || col >= n) {
        throw std::out_of_range("Failed to find pivot. Given index out of bounds.");
    }

    // Scan through entries A(col, col) to A(n-1, col) for the maximum.
    double max = std::abs(A(col, col));
    size_t max_idx = col;
    for (size_t i = col+1; i < n; i++) {
        double entry = std::abs(A(i, col));
        if (entry > max) {
            max = entry;
            max_idx = i;
        }
    }

    if (max < 1e-10) {
        throw std::runtime_error("Singular matrix.");
    }

    return max_idx;
}

void validate_system(const Matrix& A, const std::vector<double>& b) {
    /**
     * Validates system dimensions.
     */
    
    size_t m_A = A.shape().first;
    size_t n_A = A.shape().second;
    size_t n_b = b.size();

    if (m_A != n_A) {
        throw std::invalid_argument("Matrix is not square.");
    }
    else if (n_A != n_b) {
        throw std::invalid_argument("Matrix and vector for the system do not have the same dimension.");
    }
}
