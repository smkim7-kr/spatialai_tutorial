#include <iostream>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <sophus/so3.hpp>
#include <sophus/se3.hpp>

// Example using Sophus for SO(3) and SE(3) with perturbation models
int main() {
    // Create a Sophus SO(3) object (Rotation around z-axis by 45 degrees)
    Eigen::Vector3d axis_angle(0, 0, M_PI / 4); // 45 degrees around Z-axis
    Sophus::SO3d SO3 = Sophus::SO3d::exp(axis_angle); // Exponential map

    std::cout << "Original SO(3) Rotation Matrix:\n" << SO3.matrix() << std::endl;

    // Create a small perturbation in so(3) (small rotation around x-axis)
    Eigen::Vector3d delta_so3(0.01, 0, 0); // Small rotation perturbation around x-axis

    // Apply the perturbation to the original SO(3)
    Sophus::SO3d perturbed_SO3 = SO3 * Sophus::SO3d::exp(delta_so3); // SO3 * exp(delta_so3)

    std::cout << "\nPerturbed SO(3) Rotation Matrix:\n" << perturbed_SO3.matrix() << std::endl;

    // -------- SE(3) Example --------
    // Create a Sophus SE(3) object (Rotation around z-axis + translation)
    Eigen::Vector3d translation(1, 0, 0); // Translation along x-axis
    Sophus::SE3d SE3 = Sophus::SE3d(SO3, translation); // SE3 = [SO3 | translation]

    std::cout << "\nOriginal SE(3) Transformation Matrix:\n" << SE3.matrix() << std::endl;

    // Create a small perturbation in se(3) (small rotation + translation)
    Eigen::Matrix<double, 6, 1> delta_se3;
    delta_se3 << 0.01, 0, 0, 0.01, 0, 0; // Small rotation and translation perturbations

    // Apply the perturbation to the original SE(3)
    Sophus::SE3d perturbed_SE3 = SE3 * Sophus::SE3d::exp(delta_se3); // SE3 * exp(delta_se3)

    std::cout << "\nPerturbed SE(3) Transformation Matrix:\n" << perturbed_SE3.matrix() << std::endl;

    return 0;
}
