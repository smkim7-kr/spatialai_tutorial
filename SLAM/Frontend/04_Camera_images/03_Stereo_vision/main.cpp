#include <opencv2/opencv.hpp>
#include <open3d/Open3D.h>
#include <iostream>

// Camera parameters (example values, replace with actual calibration data)
double fx = 718.856;    // Focal length in pixels (x-axis)
double fy = 718.856;    // Focal length in pixels (y-axis)
double cx = 607.1928;   // Principal point x-coordinate
double cy = 185.2157;   // Principal point y-coordinate
double baseline = 0.573; // Baseline between the two cameras (in meters)

// Function to generate a point cloud from the disparity map
std::shared_ptr<open3d::geometry::PointCloud> generatePointCloud(const cv::Mat& disparity, const cv::Mat& leftImage) {
    auto pointCloud = std::make_shared<open3d::geometry::PointCloud>();

    // Iterate over the disparity map to create 3D points
    for (int v = 0; v < disparity.rows; v++) {
        for (int u = 0; u < disparity.cols; u++) {
            // Get the disparity value
            float d = disparity.at<float>(v, u);
            if (d <= 0.0) continue;  // Ignore points with no disparity

            // Compute depth (Z)
            double Z = fx * baseline / d;

            // Compute 3D coordinates (X, Y, Z)
            double X = (u - cx) * Z / fx;
            double Y = (v - cy) * Z / fy;

            // Get the color from the left image
            cv::Vec3b color = leftImage.at<cv::Vec3b>(v, u);

            // Add the point to the point cloud
            pointCloud->points_.emplace_back(X, Y, Z);
            pointCloud->colors_.emplace_back(color[2] / 255.0, color[1] / 255.0, color[0] / 255.0); // BGR to RGB
        }
    }

    return pointCloud;
}

int main(int argc, char **argv) {
    // Load stereo images
    cv::Mat leftImage = cv::imread(argv[1], cv::IMREAD_COLOR);
    cv::Mat rightImage = cv::imread(argv[2], cv::IMREAD_COLOR);

    if (leftImage.empty() || rightImage.empty()) {
        std::cerr << "Error loading images" << std::endl;
        return -1;
    }

    // Convert images to grayscale
    cv::Mat leftGray, rightGray;
    cv::cvtColor(leftImage, leftGray, cv::COLOR_BGR2GRAY);
    cv::cvtColor(rightImage, rightGray, cv::COLOR_BGR2GRAY);

    // Use StereoSGBM to compute disparity
    cv::Ptr<cv::StereoSGBM> stereoSGBM = cv::StereoSGBM::create(
        0,          // Min disparity
        192,        // Number of disparities (must be divisible by 16)
        5,          // Block size (5x5)
        600,        // P1 (regularization parameter)
        2400,       // P2 (larger regularization parameter)
        10,         // Disparity uniqueness ratio
        12,         // Speckle window size
        30,         // Speckle range
        32,         // Disparity smoothness penalty (min)
        1           // Full DP
    );
    
    // Compute disparity
    cv::Mat disparity;
    stereoSGBM->compute(leftGray, rightGray, disparity);

    // Convert disparity to float for further processing
    disparity.convertTo(disparity, CV_32F, 1.0 / 16.0);  // SGBM produces fixed-point disparity

    // Normalize the disparity map for visualization
    cv::Mat disparityNormalized;
    cv::normalize(disparity, disparityNormalized, 0, 255, cv::NORM_MINMAX, CV_8U);

    // Save and display the disparity map
    cv::imshow("Disparity Map", disparityNormalized);
    cv::imwrite("disparity_map.png", disparityNormalized);
    cv::waitKey(0);  // Wait for a keypress to continue

    // Generate point cloud
    std::shared_ptr<open3d::geometry::PointCloud> pointCloud = generatePointCloud(disparity, leftImage);

    // Visualize the point cloud using Open3D
    open3d::visualization::DrawGeometries({pointCloud}, "3D Point Cloud");

    return 0;
}
