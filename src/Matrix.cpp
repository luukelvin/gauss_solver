#include "utils.h"
#include "Matrix.h"

#include <iostream>
#include <stdexcept>
#include <valarray>
#include <vector>

Matrix::Matrix(std::valarray<double> arr, size_t m, size_t n) {
    if (arr.size() != m*n) {
        throw std::invalid_argument("Matrix could not be created. Length of given array does not match given number of rows and columns.");
    }

    data = arr;
    num_rows = m;
    num_cols = n;
}

Matrix::Matrix(const std::vector<std::vector<double>>& arr) {
    if (arr.empty()) {
        num_rows = 0;
        num_cols = 0;
        data = {};
        return;
    }

    num_rows = arr.size();
    num_cols = arr[0].size();

    std::vector<double> flattened = {};

    for (const auto& v : arr) {
        if (num_cols != v.size()) {
            throw std::invalid_argument("Matrix could not be created. Rows do not have the same length.");
        }

        flattened.insert(flattened.end(), v.begin(), v.end());
    }

    data = std::valarray<double> (flattened.data(), num_rows*num_cols);
}

std::pair<size_t, size_t> Matrix::shape() const {
    return {num_rows, num_cols};
}

double& Matrix::operator()(size_t i, size_t j) {
    return data[i*num_cols + j];
}

double Matrix::operator()(size_t i, size_t j) const {
    return data[i*num_cols + j];
}

Matrix& Matrix::permute_rows(size_t i, size_t j) {
    /**
     * Permutes rows i and j in-place.
     *
     * Returns a reference to this.
     */

    // references to the ith and jth row.
    std::slice_array<double> row_i = data[std::slice(i*num_cols, num_cols, 1)];
    std::slice_array<double> row_j = data[std::slice(j*num_cols, num_cols, 1)];

    std::valarray<double> temp = row_i;
    row_i = row_j;
    row_j = temp;

    return *this;
}

void Matrix::print() const {
    if(num_rows == 0) {
        std::cout << "[ ]";
        return;
    }

    for(size_t i = 0; i < num_rows; ++i) {
        const std::valarray<double> row_slice = data[std::slice(i*num_cols, num_cols, 1)];
        std::vector<double> row_vector (std::begin(row_slice), std::end(row_slice));
        print_vector(row_vector);
        std::cout << "\n";
    }
}
