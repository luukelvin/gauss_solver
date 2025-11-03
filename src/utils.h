#pragma once

#include <string>
#include <vector>

typedef std::vector<double> Vector;
typedef std::vector<Vector> Matrix;

std::string print_vector(const Vector& vec);
std::string print_matrix(const Matrix& mat);
