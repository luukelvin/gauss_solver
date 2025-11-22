/**
 * Code validation on test cases provided in the project specification, as well
 * as an assortment of (rather ad hoc and nonexhaustive) tests for logic not
 * explicitly part of Gauss elimination.
 */

#include "utils.h"
#include "Matrix.h"
#include "SparseMatrix.h"
#include "Solver.h"

#include <iostream>

void matrix_constructors() {
    /**
     * Expected results:
     * [ 0 0 0 ]
     * [ 0 0 0 ]
     *
     * [ 1 2 ]
     * [ 3 4 ]
     *
     * [ 1 2 ]
     * [ 3 4 ]
     */
    Matrix m0 (2, 3);

    Matrix m1 {{1, 2, 3, 4}, 2, 2};

    Matrix m2 ({{1,2}, {3,4}});

    m0.print();
    std::cout << '\n';
    m1.print();
    std::cout << '\n';
    m2.print();
    std::cout << '\n';

    // Exceptional cases
    // Matrix m3 {{1, 2, 3}, 2, 2};

    // Matrix m4 ({{1, 2}, {3}});
}

void matrix_permutation() {
    /**
     * Expected result:
     * [ 3 4 ]
     * [ 1 2 ]
     */
    Matrix A ({{1,2}, {3,4}});
    A.permute_rows(0, 1);
    A.print();
    std::cout << '\n';
}

void pivot_index() {
    /**
     * Expected result:
     * 0
     * 1
     */
    Matrix A ({{3,4}, {1,2}});
    std::cout << find_pivot_index(A, 0);
    std::cout << '\n';
    std::cout << find_pivot_index(A, 1);
    std::cout << '\n';
    // Exceptional case
    // std::cout << find_pivot_index(A, 2);
    // std::cout << '\n';
}

void GEPP_not_in_place() {
    Matrix A ({{2, 4, 6}, {1, 5, -3}, {3, 1, 8}});
    std::vector<double> b = {12, 13, 12};

    LinearSystem sys = GEPP(A, b, false);
    A.print();
    std::cout << '\n';
    sys.A.print();
    std::cout << '\n';
    print_vector(b);
    std::cout << '\n';
    print_vector(sys.b);
    std::cout << '\n';
}

void test_1_solving_backsub() {
    /**
     * Expected result:
     *
     *   Solution:
     *   [1, 2, 3]
     */
    Matrix A ({{2, 1, 1}, {0, 3, 2}, {0, 0, 4}});
    std::vector<double> b = {7, 12, 12};
    std::vector<double> x = backsubstitute(A, b);

    std::cout << "----Test 1----\n";
    std::cout << "Solution:\n";
    print_vector(x);
    std::cout << '\n';
}

void test_2_elimination() {
    /**
     * Expected results:
     *
     *   U =
     *   [ 3 1 8 ]
     *   [ 0 4.66667 -5.66667 ]
     *   [ 0 0 4.71429 ]
     *
     *   d =
     *   [ 12 9 -2.42857 ]
     *
     *   Solution:
     *   [ 4.93939 1.30303 -0.515152 ]
     */

    Matrix A ({{2, 4, 6}, {1, 5, -3}, {3, 1, 8}});
    std::vector<double> b = {12, 13, 12};
    GEPP(A, b);
    std::vector<double> x = backsubstitute(A, b);

    std::cout << "----Test 2----\n";
    std::cout << "U = \n";
    A.print();
    std::cout << '\n';
    std::cout << "d = \n";
    print_vector(b);
    std::cout << '\n' << '\n';
    std::cout << "Solution:\n";
    print_vector(x);
    std::cout << '\n';
}

void test_3_pivot_permutation() {
    /**
     * Expected results:
     *
     *   U =
     *   [ 4 1 1 ]
     *   [ 0 2.5 0.5 ]
     *   [ 0 0 -0.4 ]
     *
     *   d =
     *   [ 2 0 0.5 ]
     *
     *   Solution:
     *   [ 0.75 0.25 -1.25 ]
     */

    Matrix A ({{1, 1, 0}, {2, 3, 1}, {4, 1, 1}});
    std::vector<double> b = {1, 1, 2};
    GEPP(A, b);
    std::vector<double> x = backsubstitute(A, b);

    std::cout << "----Test 3----\n";
    std::cout << "U = \n";
    A.print();
    std::cout << '\n';
    std::cout << "d = \n";
    print_vector(b);
    std::cout << '\n' << '\n';
    std::cout << "Solution:\n";
    print_vector(x);
    std::cout << '\n';
}

void test_4_singular_matrix() {
    /**
     * Expected results:
     *
     *   Error encountered in elimination:
     *   Singular matrix.
     *   U =
     *   [ 10 3 5 ]
     *   [ 0 -0.1 -6.5 ]
     *   [ 0 0 1.42109e-14 ]
     *
     *   d =
     *   [ 1 0.3 1 ]
     *
     */

    Matrix A ({{7, 2, -3}, {3, 1, 8}, {10, 3, 5}});
    std::vector<double> b = {1, 1, 1};

    std::cout << "----Test 4----\n";
    try {
        GEPP(A, b);
        A.print();
        std::cout << '\n';
        print_vector(b);
        std::cout << '\n';
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error encountered in elimination: \n";
        std::cout << e.what() << '\n';
        std::cout << "When error occurred, GEPP had obtained:\n";
        std::cout << "U = \n";
        A.print();
        std::cout << '\n';
        std::cout << "d = \n";
        print_vector(b);
        std::cout << '\n';
    }
}

void test_5_sparse() {
    Matrix A = { {{2,-1,0,0},{-1,2,-1,0},{0,-1,2,-1},{0,0,-1,2}} };

    SparseMatrix S = {A};
    S.print();
    S.permute_rows(0,2);
    S.print();
}

int main() {

    // matrix_constructors();
    // matrix_permutation();
    // pivot_index();
    // GEPP_not_in_place();

    test_1_solving_backsub();
    std::cout << '\n';
    test_2_elimination();
    std::cout << '\n';
    test_3_pivot_permutation();
    std::cout << '\n';
    test_4_singular_matrix();
    std::cout << '\n';
    test_5_sparse();
    std::cout << '\n';

    return 0;
}
