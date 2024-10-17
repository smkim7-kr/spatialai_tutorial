// main.cpp
#include <iostream>
#include <Eigen/Dense>

int main() {
    // Define a 3x3 matrix and initialize with random values
    Eigen::Matrix3d mat = Eigen::Matrix3d::Random();
    std::cout << "Random 3x3 matrix:\n" << mat << std::endl;

    // Compute the transpose of the matrix
    Eigen::Matrix3d mat_transpose = mat.transpose();
    std::cout << "\nTranspose of the matrix:\n" << mat_transpose << std::endl;

    // Compute the matrix inverse
    Eigen::Matrix3d mat_inverse = mat.inverse();
    std::cout << "\nInverse of the matrix:\n" << mat_inverse << std::endl;

    // Verify the inverse by checking if mat * mat_inverse = Identity
    Eigen::Matrix3d identity = mat * mat_inverse;
    std::cout << "\nMatrix * Inverse:\n" << identity << std::endl;

    // Define a 3D vector
    Eigen::Vector3d vec(1, 2, 3);
    std::cout << "\n3D Vector:\n" << vec << std::endl;

    // Perform matrix-vector multiplication
    Eigen::Vector3d result = mat * vec;
    std::cout << "\nMatrix-vector multiplication result:\n" << result << std::endl;

    // Solving linear system (Ax = b), where A = mat and b = vec
    Eigen::Vector3d x = mat.colPivHouseholderQr().solve(vec);
    std::cout << "\nSolution to the linear system (Ax = b):\n" << x << std::endl;

    return 0;
}
