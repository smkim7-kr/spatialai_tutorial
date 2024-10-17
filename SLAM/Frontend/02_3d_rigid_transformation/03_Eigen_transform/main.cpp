#include <iostream>
#include <Eigen/Dense>

int main() {
    // Define a 3D point in Camera 1's coordinate system
    Eigen::Vector3d point_in_cam1(1.0, 2.0, 3.0);
    std::cout << "Point in Camera 1's coordinate system:\n" << point_in_cam1 << std::endl;

    // --- Transformation from World to Camera 1 (T_C1^W = [R_C1^W, t_C1^W]) ---
    Eigen::Matrix3d R_C1_W;
    R_C1_W = Eigen::AngleAxisd(M_PI / 6, Eigen::Vector3d::UnitZ())  // Rotation around Z-axis by 30 degrees
             * Eigen::AngleAxisd(M_PI / 6, Eigen::Vector3d::UnitY()) // Rotation around Y-axis by 30 degrees
             * Eigen::AngleAxisd(M_PI / 6, Eigen::Vector3d::UnitX()); // Rotation around X-axis by 30 degrees

    Eigen::Vector3d t_C1_W(1.0, 2.0, 3.0);  // Translation from World to Camera 1

    // --- Transformation from World to Camera 2 (T_C2^W = [R_C2^W, t_C2^W]) ---
    Eigen::Matrix3d R_C2_W;
    R_C2_W = Eigen::AngleAxisd(M_PI / 4, Eigen::Vector3d::UnitZ())  // Rotation around Z-axis by 45 degrees
             * Eigen::AngleAxisd(M_PI / 4, Eigen::Vector3d::UnitY()) // Rotation around Y-axis by 45 degrees
             * Eigen::AngleAxisd(M_PI / 4, Eigen::Vector3d::UnitX()); // Rotation around X-axis by 45 degrees

    Eigen::Vector3d t_C2_W(-2.0, -1.0, 1.0);  // Translation from World to Camera 2

    // Convert the point from Camera 1 to the World coordinate system
    Eigen::Vector3d point_in_world = R_C1_W.transpose() * (point_in_cam1 - t_C1_W);
    std::cout << "\nPoint in World coordinate system:\n" << point_in_world << std::endl;

    // Convert the point from the World coordinate system to Camera 2's coordinate system
    Eigen::Vector3d point_in_cam2 = R_C2_W * point_in_world + t_C2_W;
    std::cout << "\nPoint in Camera 2's coordinate system:\n" << point_in_cam2 << std::endl;

    // --- Optional: Transformation between Camera 1 and Camera 2 (T_C2^C1 = T_C2^W * (T_C1^W)^(-1)) ---
    Eigen::Matrix3d R_C2_C1 = R_C2_W * R_C1_W.transpose();  // Rotation from Camera 1 to Camera 2
    Eigen::Vector3d t_C2_C1 = t_C2_W - R_C2_W * R_C1_W.transpose() * t_C1_W;  // Translation from Camera 1 to Camera 2

    std::cout << "\nRotation matrix from Camera 1 to Camera 2 (R_C2^C1):\n" << R_C2_C1 << std::endl;
    std::cout << "\nTranslation vector from Camera 1 to Camera 2 (t_C2^C1):\n" << t_C2_C1 << std::endl;

    return 0;
}
