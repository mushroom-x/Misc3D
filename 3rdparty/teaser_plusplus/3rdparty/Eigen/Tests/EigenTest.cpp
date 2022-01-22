/** @file EigenTest.cpp
 * Created at 2020-03-07
 * Copyright (c) RVBUST, Inc - All rights reserved.
 */

#include <Eigen/Dense>
#include <iostream>
using namespace Eigen;

int main() {
    MatrixXd m(2, 5);
    m.resize(4, 3);
    std::cout << "The matrix m is of size " << m.rows() << "x" << m.cols() << std::endl;
    std::cout << "It has " << m.size() << " coefficients" << std::endl;
    VectorXd v(2);
    v.resize(5);
    std::cout << "The vector v is of size " << v.size() << std::endl;
    std::cout << "As a matrix, v is of size " << v.rows() << "x" << v.cols() << std::endl;
}
