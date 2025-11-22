#include "utils.h"
#include "Matrix.h"
#include "SparseMatrix.h"

#include <algorithm>
#include <iterator>
#include <iostream>
#include <stdexcept>
#include <valarray>

SparseMatrix::SparseMatrix(const Matrix& A) {
    num_rows = A.shape().first;
    num_cols = A.shape().second;

    row_index = {};
    col_index = {};
    data = {};

    // Scan through the entries of A.
    size_t cur_idx = 0; 
    for (size_t i = 0; i < num_rows; i++) {
        row_index.push_back(cur_idx);
        for (size_t j = 0; j < num_cols; j++) {
            if (A(i,j) != 0) {
                // Store the nonzero entry at the cur_idx position.
                col_index.push_back(j);
                data.push_back(A(i,j));
                cur_idx += 1;
            }
        }
    }
    // For convenience, store the total number of non_zeros
    // (i.e. length of col_index and data).
    row_index.push_back(cur_idx);
}

SparseMatrix& SparseMatrix::permute_rows(size_t i, size_t j) {
    // Permutes row i and row j

    if (i >= num_rows || j >= num_rows) {
        throw std::out_of_range("Permuting index out of bounds.");
    }

    if (i == j) {
        // No permutation required
        return *this;
    }
    else {
        // Order i < j.
        std::pair<size_t, size_t> m = std::minmax(i, j);
        i = m.first;
        j = m.second;
    }

    // Indices that bound row i, row j and the rows in between.
    size_t row_i_start = row_index[i];
    size_t row_i_end = row_index[i+1]; // Also start of row i+1
    size_t row_j_start = row_index[j]; // Also end of row j-1
    size_t row_j_end = row_index[j+1]; // Also start of row j+1

    // Iterators to the start and end of the region to permute.
    auto row_i_start_it_col = col_index.begin();
    std::advance(row_i_start_it_col, row_i_start);
    auto row_j_end_it_col = col_index.begin();
    std::advance(row_j_end_it_col, row_j_end);

    auto row_i_start_it_data = data.begin();
    std::advance(row_i_start_it_data, row_i_start);
    auto row_j_end_it_data = data.begin();
    std::advance(row_j_end_it_data, row_j_end);

    // Copies of the region to permute
    std::vector<double> col_copy (row_i_start_it_col, row_j_end_it_col);
    std::vector<double> data_copy (row_i_start_it_data, row_j_end_it_data);

    // Row index offset from swapping i and j.
    size_t row_i_length = row_i_end - row_i_start;
    size_t row_j_length = row_j_end - row_j_start;
    int delta = row_j_length - row_i_length;

    // Update col_index and data
    for (size_t k = row_i_start; k < row_j_end; k++) {
        if (k < row_i_end + delta) {
            // Copy row j
            col_index[k] = col_copy[(row_j_start-row_i_start) + (k-row_i_start)];
            data[k] = data_copy[(row_j_start-row_i_start) + (k-row_i_start)];
        }
        else if (k < row_j_start + delta) {
            // Copy rows between i+1 and j-1
            col_index[k] = col_copy[k - row_i_start - delta];
            data[k] = data_copy[k - row_i_start - delta];
        }
        else {
            // k >= row_j_start + delta
            // Copy row i
            col_index[k] = col_copy[k - row_j_start - delta];
            data[k] = data_copy[k - row_j_start - delta];
        }
    }

    // Update row_index only for rows in between i and j+1.
    for (size_t l = i+1; l < j+1; l++) {
        row_index[l] += delta;
    }

    return *this;
}

void SparseMatrix::print() const {
    std::cout << "row_index ";
    print_vector(row_index);
    std::cout << '\n';
    std::cout << "col_index ";
    print_vector(col_index);
    std::cout << '\n';
    std::cout << "data      ";
    print_vector(data);
    std::cout << '\n';
}
