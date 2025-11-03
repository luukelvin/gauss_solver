#pragma once

#include "utils.h"
#include "LinearSystem.h"

class Solver {
    private:
        LinearSystem system;

    public:
        Solver(LinearSystem);
        int find_pivot_index(int);
        Vector backsubstitute();
        Vector solve();
};
