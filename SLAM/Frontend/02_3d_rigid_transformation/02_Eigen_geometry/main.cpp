// main.cpp
#include <iostream>
#include <Eigen/Geometry>  // Eigen Geometry module for transformations and rotations

int main() {
    // Define a 3D vector (point)
    Eigen::Vector3d point(1.0, 2.0, 3.0);
    std::cout << "Original point:\n" << point << std::endl;

    // Define a 3D translation (translate by (1, -2, 3))
    Eigen::Translation3d translation(1.0, -2.0, 3.0);
    Eigen::Vector3d translated_point = translation * point;  // Apply translation
    std::cout << "\nTranslated point:\n" << translated_point << std::endl;

    // Define a 3D rotation using Angle-Axis (rotate 45 degrees around the Z-axis)
    Eigen::AngleAxisd rotation(M_PI / 4, Eigen::Vector3d::UnitZ());
    Eigen::Vector3d rotated_point = rotation * point;  // Apply rotation
    std::cout << "\nRotated point (45 degrees around Z-axis):\n" << rotated_point << std::endl;

    // Combine translation and rotation into an affine transformation
    Eigen::Affine3d affine_transform = translation * rotation;
    Eigen::Vector3d transformed_point = affine_transform * point;
    std::cout << "\nPoint after combined translation and rotation:\n" << transformed_point << std::endl;

    // Quaternion representation of the rotation (can be constructed from Angle-Axis)
    Eigen::Quaterniond quaternion(rotation);
    Eigen::Vector3d rotated_point_with_quaternion = quaternion * point;  // Apply quaternion rotation
    std::cout << "\nRotated point using Quaternion:\n" << rotated_point_with_quaternion << std::endl;

    // Verify the rotation using quaternion inverse ( q * p * q^-1 )
    Eigen::Quaterniond q_inv = quaternion.inverse();
    Eigen::Quaterniond p(0, point.x(), point.y(), point.z());  // Treat point as a pure quaternion
    Eigen::Quaterniond rotated_quaternion = quaternion * p * q_inv;
    Eigen::Vector3d rotated_point_via_quaternion = rotated_quaternion.vec();
    std::cout << "\nPoint rotated via q * p * q^-1:\n" << rotated_point_via_quaternion << std::endl;

    return 0;
}
