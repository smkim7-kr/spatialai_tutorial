#include <iostream>
#include <Eigen/Dense>

// Define transformation from world coordinates to camera coordinates
Eigen::Vector3d world_to_camera(const Eigen::Vector3d& X_w, const Eigen::Matrix3d& R_cw, const Eigen::Vector3d& t_cw) {
    return R_cw * X_w + t_cw;
}

// Convert from camera coordinates to normalized coordinates
Eigen::Vector2d camera_to_normalized(const Eigen::Vector3d& X_c) {
    return { X_c(0) / X_c(2), X_c(1) / X_c(2) };
}

// Convert from normalized coordinates to pixel coordinates
Eigen::Vector2d normalized_to_pixel(const Eigen::Vector2d& X_n, double f_x, double f_y, double c_x, double c_y) {
    return { f_x * X_n(0) + c_x, f_y * X_n(1) + c_y };
}

int main() {
    // World coordinates (example point in world)
    Eigen::Vector3d X_w(3, 2, 10);  // Point in world coordinates

    // Rotation matrix from world to camera (identity, no rotation)
    Eigen::Matrix3d R_cw;
    R_cw = Eigen::Matrix3d::Identity();  // Assume camera aligned with world frame

    // Translation from world to camera (camera positioned at origin in world coordinates)
    Eigen::Vector3d t_cw(0, 0, 0);  // Camera at world origin

    // Intrinsic parameters (focal length and principal point)
    double f_x = 800.0, f_y = 800.0;  // Focal length in pixels
    double c_x = 400.0, c_y = 300.0;  // Principal point (center of the image)

    // Step 1: World to Camera coordinates
    Eigen::Vector3d X_c = world_to_camera(X_w, R_cw, t_cw);
    std::cout << "Camera Coordinates: [" << X_c.transpose() << "]" << std::endl;

    // Step 2: Camera to Normalized coordinates
    Eigen::Vector2d X_n = camera_to_normalized(X_c);
    std::cout << "Normalized Coordinates: [" << X_n.transpose() << "]" << std::endl;

    // Step 3: Normalized to Pixel coordinates
    Eigen::Vector2d X_p = normalized_to_pixel(X_n, f_x, f_y, c_x, c_y);
    std::cout << "Pixel (Image) Coordinates: [" << X_p.transpose() << "]" << std::endl;

    return 0;
}
