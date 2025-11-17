#pragma once

#include <valarray>
#include <vector>

class Matrix {
    // 0-indexed matrices
    private:
        std::valarray<double> data;
        size_t num_rows;
        size_t num_cols;

    public:
        // constructors
        Matrix(size_t m, size_t n) : data(0., m*n), num_rows{m}, num_cols{n} {};
        Matrix(std::valarray<double> arr, size_t m, size_t n);
        Matrix(const std::vector<std::vector<double>>& arr);

        // get dimensions
        std::pair<size_t, size_t> shape() const;

        // entry-wise read and write
        double& operator()(size_t i, size_t j);
        double operator()(size_t i, size_t j) const;

        // in-place elementary (row) operations
        Matrix& permute_rows(size_t i, size_t j);

        // misc.
        void print() const;
};
