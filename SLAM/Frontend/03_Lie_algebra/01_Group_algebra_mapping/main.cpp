#include <iostream>
#include <vector>
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

// Matrix multiplication
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

// Identity matrix
Matrix3x3 identity_3x3() {
    return {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
}

// Matrix addition
Matrix3x3 mat_add(const Matrix3x3& A, const Matrix3x3& B) {
    Matrix3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = A[i][j] + B[i][j];
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

// Logarithmic map for SO(3) to so(3)
Vector3 log_so3(const Matrix3x3& R) {
    double trace = R[0][0] + R[1][1] + R[2][2];
    double theta = std::acos((trace - 1) / 2.0);
    
    if (theta == 0) {
        return {0, 0, 0};
    }

    double factor = theta / (2 * std::sin(theta));
    
    Vector3 omega = {
        (R[2][1] - R[1][2]) * factor,
        (R[0][2] - R[2][0]) * factor,
        (R[1][0] - R[0][1]) * factor
    };
    
    return omega;
}

// Exponential map for se(3) to SE(3)
Matrix4x4 exp_se3(const Vector3& omega, const Vector3& v) {
    Matrix3x3 R = exp_so3(omega);
    double theta = std::sqrt(omega[0]*omega[0] + omega[1]*omega[1] + omega[2]*omega[2]);
    
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
    
    Matrix4x4 T = {{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 1}}};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            T[i][j] = R[i][j];
        }
        T[i][3] = V[i][0] * v[0] + V[i][1] * v[1] + V[i][2] * v[2];
    }
    
    return T;
}

// Logarithmic map for SE(3) to se(3)
std::pair<Vector3, Vector3> log_se3(const Matrix4x4& T) {
    Matrix3x3 R = {{{T[0][0], T[0][1], T[0][2]}, {T[1][0], T[1][1], T[1][2]}, {T[2][0], T[2][1], T[2][2]}}};
    Vector3 omega = log_so3(R);
    
    double theta = std::sqrt(omega[0]*omega[0] + omega[1]*omega[1] + omega[2]*omega[2]);
    
    Matrix3x3 V_inv;
    if (theta == 0) {
        V_inv = identity_3x3();
    } else {
        Matrix3x3 omega_hat = skew_symmetric(omega);
        Matrix3x3 omega_hat_sq = mat_mult(omega_hat, omega_hat);
        
        Matrix3x3 I = identity_3x3();
        Matrix3x3 term1 = scalar_mult(theta / (2 * std::sin(theta)), omega_hat);
        Matrix3x3 term2 = scalar_mult((1 - std::cos(theta)) / (theta * theta), omega_hat_sq);
        
        V_inv = mat_add(mat_add(I, term1), term2);
    }
    
    Vector3 v = {
        V_inv[0][0] * T[0][3] + V_inv[0][1] * T[1][3] + V_inv[0][2] * T[2][3],
        V_inv[1][0] * T[0][3] + V_inv[1][1] * T[1][3] + V_inv[1][2] * T[2][3],
        V_inv[2][0] * T[0][3] + V_inv[2][1] * T[1][3] + V_inv[2][2] * T[2][3]
    };
    
    return {omega, v};
}

int main() {
    // Example for so(3) <-> SO(3)
    std::cout << "so(3) -> SO(3) -> so(3) example:" << std::endl;
    Vector3 omega_so3 = {0, 0, M_PI / 4};  // 45 degrees around Z-axis
    
    // Exponential map (so(3) -> SO(3))
    Matrix3x3 R_so3 = exp_so3(omega_so3);
    std::cout << "Rotation matrix (SO(3)):" << std::endl;
    for (const auto& row : R_so3) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    
    // Logarithmic map (SO(3) -> so(3))
    Vector3 omega_log_so3 = log_so3(R_so3);
    std::cout << "Recovered omega (so(3)): (" << omega_log_so3[0] << ", " << omega_log_so3[1] << ", " << omega_log_so3[2] << ")" << std::endl;
    
    std::cout << "\n";

    // Example for se(3) <-> SE(3)
    Vector3 omega = {0, 0, M_PI / 4};
    Vector3 v = {1, 0, 0};
    
    Matrix4x4 T = exp_se3(omega, v);
    
    std::cout << "Transformation Matrix SE(3):" << std::endl;
    for (const auto& row : T) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    
    auto [omega_log, v_log] = log_se3(T);
    std::cout << "Logarithm of SE(3): Omega = (" << omega_log[0] << ", " << omega_log[1] << ", " << omega_log[2] << "), v = (" << v_log[0] << ", " << v_log[1] << ", " << v_log[2] << ")" << std::endl;
    
    return 0;
}
