#pragma once

#include "Matrix.h"

#include <vector>

struct SparseMatrix {
    // CSR sparse matrix

    // Data members
    // All of these are public so that the elimination/solving interface is
    // consistent with the interface for solving dense Matrices. All of the
    // solving procedures need to operate directly on the data.
    std::vector<double> row_index;
    std::vector<double> col_index;
    std::vector<double> data;
    size_t num_rows;
    size_t num_cols;

    // constructor
    SparseMatrix(const Matrix& A);

    // in-place elementary (row) operations
    SparseMatrix& permute_rows(size_t i, size_t j);

    // misc.
    void print() const;
};
