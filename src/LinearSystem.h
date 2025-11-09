#pragma once

#include <valarray>
#include <vector>

class Matrix {
    private:
        std::valarray<double> data;
        size_t num_rows;
        size_t num_cols;

    public:
        // constructors
        Matrix(size_t m, size_t n) : data(0., m*n), num_rows{m}, num_cols{n} {};
        Matrix(std::valarray<double> arr, size_t m, size_t n);
        Matrix(const std::vector<std::vector<double>>& arr);

        // entry-wise read
        double operator()(size_t i, size_t j) const;

        // elementary (row) operations
        Matrix& permute_rows(size_t i, size_t j);

        // misc.
        void print() const;
};

struct LinearSystem {
    Matrix A;
    std::vector<double> b;
};
