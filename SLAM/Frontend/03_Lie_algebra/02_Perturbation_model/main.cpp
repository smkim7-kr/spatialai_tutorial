#include <iostream>
#include <cmath>
#include <array>

using Matrix3x3 = std::array<std::array<double, 3>, 3>;
using Vector3 = std::array<double, 3>;
using Matrix4x4 = std::array<std::array<double, 4>, 4>;

// Function to create a skew-symmetric matrix from a vector (so(3))
Matrix3x3 skew_symmetric(const Vector3& v) {
    return {{{ 0, -v[2], v[1] }, 
             { v[2], 0, -v[0] }, 
             { -v[1], v[0], 0 }}};
}

// Matrix multiplication for 3x3 matrices
Matrix3x3 mat_mult(const Matrix3x3& A, const Matrix3x3& B) {
    Matrix3x3 result = {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

// Identity matrix (3x3)
Matrix3x3 identity_3x3() {
    return {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
}

// Matrix addition for 3x3 matrices
Matrix3x3 mat_add(const Matrix3x3& A, const Matrix3x3& B) {
    Matrix3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

// Scalar multiplication for matrix
Matrix3x3 scalar_mult(double s, const Matrix3x3& A) {
    Matrix3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = s * A[i][j];
        }
    }
    return result;
}

// Exponential map for so(3) to SO(3)
Matrix3x3 exp_so3(const Vector3& omega) {
    double theta = std::sqrt(omega[0]*omega[0] + omega[1]*omega[1] + omega[2]*omega[2]);
    if (theta == 0) {
        return identity_3x3();
    }
    
    Matrix3x3 omega_hat = skew_symmetric(omega);
    Matrix3x3 omega_hat_sq = mat_mult(omega_hat, omega_hat);
    
    Matrix3x3 I = identity_3x3();
    Matrix3x3 term1 = scalar_mult(std::sin(theta) / theta, omega_hat);
    Matrix3x3 term2 = scalar_mult((1 - std::cos(theta)) / (theta * theta), omega_hat_sq);
    
    return mat_add(mat_add(I, term1), term2);
}

// Perturbation model for SO(3)
// Original rotation matrix R is perturbed by a small rotation represented by delta_omega
Matrix3x3 perturb_so3(const Matrix3x3& R, const Vector3& delta_omega) {
    // Compute the exponential map of delta_omega (perturbation in so(3))
    Matrix3x3 delta_R = exp_so3(delta_omega);
    
    // Perturbed rotation: R * exp([delta_omega]x)
    return mat_mult(R, delta_R);
}

// Identity matrix (4x4)
Matrix4x4 identity_4x4() {
    return {{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
}

// Matrix multiplication for 4x4 matrices
Matrix4x4 mat_mult_4x4(const Matrix4x4& A, const Matrix4x4& B) {
    Matrix4x4 result = {{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

// Exponential map for se(3) to SE(3)
Matrix4x4 exp_se3(const Vector3& omega, const Vector3& v) {
    // Compute the rotational part using exp(so(3) -> SO(3))
    Matrix3x3 R = exp_so3(omega);
    double theta = std::sqrt(omega[0]*omega[0] + omega[1]*omega[1] + omega[2]*omega[2]);
    
    // Compute V for translation part
    Matrix3x3 V;
    if (theta == 0) {
        V = identity_3x3();
    } else {
        Matrix3x3 omega_hat = skew_symmetric(omega);
        Matrix3x3 omega_hat_sq = mat_mult(omega_hat, omega_hat);
        
        Matrix3x3 I = identity_3x3();
        Matrix3x3 term1 = scalar_mult((1 - std::cos(theta)) / (theta * theta), omega_hat);
        Matrix3x3 term2 = scalar_mult((theta - std::sin(theta)) / (theta * theta * theta), omega_hat_sq);
        
        V = mat_add(mat_add(I, term1), term2);
    }
    
    // Build SE(3) matrix
    Matrix4x4 T = identity_4x4();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            T[i][j] = R[i][j];
        }
        T[i][3] = V[i][0] * v[0] + V[i][1] * v[1] + V[i][2] * v[2];
    }
    
    return T;
}

// Perturbation model for SE(3)
// Original transformation matrix T is perturbed by a small twist (delta_omega, delta_v)
Matrix4x4 perturb_se3(const Matrix4x4& T, const Vector3& delta_omega, const Vector3& delta_v) {
    // Compute the exponential map of the perturbation (se(3) -> SE(3))
    Matrix4x4 delta_T = exp_se3(delta_omega, delta_v);
    
    // Perturbed transformation: T * exp([delta_omega, delta_v])
    return mat_mult_4x4(T, delta_T);
}

int main() {
    // Example: Perturbation in SO(3)
    std::cout << "SO(3) Perturbation Example:\n";
    
    // Original rotation matrix (45-degree rotation around z-axis)
    Vector3 omega = {0, 0, M_PI / 4};
    Matrix3x3 R = exp_so3(omega);

    // Original matrix
    std::cout << "Original Matrix (SO(3)):\n";
    for (const auto& row : R) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    
    // Small perturbation in so(3) (small rotation around x-axis)
    Vector3 delta_omega = {0.01, 0, 0};  // Perturbation of 0.01 radians around x-axis
    
    // Perturbed rotation
    Matrix3x3 R_perturbed = perturb_so3(R, delta_omega);
    
    std::cout << "Perturbed Rotation Matrix (SO(3)):\n";
    for (const auto& row : R_perturbed) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
    }
    
    std::cout << "\n";

    // Example: Perturbation in SE(3)
    std::cout << "SE(3) Perturbation Example:\n";
    
    // Original transformation matrix (rotation + translation)
    Vector3 v = {1, 0, 0};  // Translation along x-axis
    Matrix4x4 T = exp_se3(omega, v);

    std::cout << "Original Matrix (SE(3)):\n";
    for (const auto& row : T) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
    }
    
    std::cout << "\n";
    
    // Small perturbation in se(3) (small rotation around x-axis and small translation)
    Vector3 delta_v = {0.01, 0, 0};  // Small translation perturbation
    Matrix4x4 T_perturbed = perturb_se3(T, delta_omega, delta_v);
    
    std::cout << "Perturbed Transformation Matrix (SE(3)):\n";
    for (const auto& row : T_perturbed) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
    }
    
    return 0;
}
