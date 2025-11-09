# include "LinearSystem.h"

#include <iostream>

int main() {
    Matrix m0 (2, 3);

    Matrix m1 {{1, 2, 3, 4}, 2, 2};

    Matrix m2 ({{1,2}, {3,4}});

    m0.print();
    std::cout << '\n';
    m1.print();
    std::cout << '\n';
    m2.print();
    std::cout << '\n';

    m2.permute_rows(0, 1);
    m2.print();
    
    // Matrix m3 {{1, 2, 3}, 2, 2};

    // Matrix m4 ({{1, 2}, {3}});

    return 0;
}
