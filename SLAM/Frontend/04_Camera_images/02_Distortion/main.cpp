#include <opencv2/opencv.hpp>
#include <iostream>

// Distortion coefficients (example values, you need to replace with actual ones)
double k1 = -0.3, k2 = 0.1, k3 = 0.0;  // Radial distortion coefficients
double p1 = 0.0, p2 = 0.0;              // Tangential distortion coefficients

// Camera intrinsic parameters (example values, replace with actual ones)
double fx = 800, fy = 800;  // Focal lengths
double cx = 400, cy = 300;  // Principal point (center of the image)

// Function to undistort the pixel coordinates
cv::Point2f undistortPixel(const cv::Point2f& distortedPoint, const cv::Size& imageSize) {
    // Convert pixel coordinates to normalized coordinates
    double x = (distortedPoint.x - cx) / fx;
    double y = (distortedPoint.y - cy) / fy;
    
    // Compute the radius (r^2)
    double r2 = x * x + y * y;
    
    // Compute radial distortion
    double radialDistortion = 1 + k1 * r2 + k2 * r2 * r2 + k3 * r2 * r2 * r2;
    
    // Compute tangential distortion
    double x_tangential = 2 * p1 * x * y + p2 * (r2 + 2 * x * x);
    double y_tangential = p1 * (r2 + 2 * y * y) + 2 * p2 * x * y;
    
    // Apply the distortions
    double x_undistorted = x * radialDistortion + x_tangential;
    double y_undistorted = y * radialDistortion + y_tangential;
    
    // Convert back to pixel coordinates
    cv::Point2f undistortedPixel;
    undistortedPixel.x = x_undistorted * fx + cx;
    undistortedPixel.y = y_undistorted * fy + cy;
    
    return undistortedPixel;
}

int main() {
    // Load the distorted image
    cv::Mat distortedImage = cv::imread("./distorted.png", cv::IMREAD_GRAYSCALE);
    if (distortedImage.empty()) {
        std::cerr << "Failed to load image." << std::endl;
        return -1;
    }

    // Prepare the undistorted image (same size as distorted image)
    cv::Mat undistortedImage = cv::Mat::zeros(distortedImage.size(), distortedImage.type());

    // Iterate through every pixel of the undistorted image
    for (int v = 0; v < undistortedImage.rows; ++v) {
        for (int u = 0; u < undistortedImage.cols; ++u) {
            // Find the corresponding distorted pixel
            cv::Point2f undistortedPixel(u, v);
            cv::Point2f distortedPixel = undistortPixel(undistortedPixel, undistortedImage.size());
            
            // Check if the distorted pixel is within bounds
            if (distortedPixel.x >= 0 && distortedPixel.x < distortedImage.cols &&
                distortedPixel.y >= 0 && distortedPixel.y < distortedImage.rows) {
                // Assign the pixel value from the distorted image to the undistorted image
                undistortedImage.at<uchar>(v, u) = distortedImage.at<uchar>(static_cast<int>(distortedPixel.y), static_cast<int>(distortedPixel.x));
            }
        }
    }

    // Show the results
    cv::imshow("Distorted Image", distortedImage);
    cv::imshow("Undistorted Image", undistortedImage);
    cv::waitKey(0);

    return 0;
}
