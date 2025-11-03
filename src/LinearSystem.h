#pragma once

#include "utils.h"

class LinearSystem {
    private:
        Matrix A;
        Vector b;
        int dim;

    public:
        LinearSystem(Matrix mat, Vector vec);
        LinearSystem& permute_rows(int row1, int row2);
        LinearSystem& eliminate(int col);
};
