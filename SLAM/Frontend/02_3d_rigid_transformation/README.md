
# 3D Rigid Transformation

## Introduction
A rigid transformation in 3D space consists of two components: **rotation** and **translation**. Rigid transformations are critical in fields like robotics, computer vision, and computer graphics. This guide covers these transformations in-depth, including practical examples using the **Eigen** library, which is widely used in C++ for linear algebra operations.

### 1. Translation
Translation is the process of moving a point or object in 3D space along the x, y, and z axes without changing its orientation. Mathematically, it can be represented as:

$$ T(p) = p + t $$

Where:
- $p$ is the original position vector.
- $t = \begin{bmatrix} t_x \\ t_y \\ t_z \end{bmatrix}$ is the translation vector.


Example in Eigen (C++):
```cpp
#include <Eigen/Dense>

Eigen::Vector3d point(1, 2, 3);
Eigen::Vector3d translation(2, 0, 1);
Eigen::Vector3d new_point = point + translation;
```

### 2. Rotation
Rotation transforms an object around an axis or point in 3D space. In 3D, there are several ways to represent rotations, including **rotation matrices**, **quaternions**, and **Euler angles**.

#### 2.1 Rotation Matrix
A rotation matrix is a 3x3 orthogonal matrix that rotates points in 3D space. If a vector \(p\) is rotated by a matrix \(R\), the result is:

$$
R(p) = R \cdot p
$$

Example in Eigen:
```cpp
Eigen::Matrix3d rotation_matrix;
rotation_matrix = Eigen::AngleAxisd(M_PI/4, Eigen::Vector3d::UnitZ());
Eigen::Vector3d rotated_point = rotation_matrix * point;
```

#### 2.2 Quaternions
Quaternions are a compact and efficient way to represent rotations in 3D. They avoid some issues with Euler angles, such as **gimbal lock**.

A quaternion is typically written as:

$$
q = w + xi + yj + zk
$$

Where \(w\) is the scalar part, and \(x, y, z\) form the vector part. The Eigen library provides a straightforward interface for working with quaternions.

Example in Eigen:
```cpp
Eigen::Quaterniond quaternion(Eigen::AngleAxisd(M_PI/4, Eigen::Vector3d::UnitZ()));
Eigen::Vector3d rotated_point = quaternion * point;
```

#### 2.3 Euler Angles
Euler angles are a way of representing 3D rotations using three angles (yaw, pitch, roll). These angles are applied in a specific order to rotate the object around the coordinate axes.

For example, a typical sequence is **ZYX**, where:
- **Yaw** (rotation around z-axis)
- **Pitch** (rotation around y-axis)
- **Roll** (rotation around x-axis)

The Eigen library supports the conversion between rotation matrices, quaternions, and Euler angles.

Example in Eigen:
```cpp
Eigen::Vector3d euler_angles = rotation_matrix.eulerAngles(2, 1, 0); // ZYX order
```

### 3. Combining Rotation and Translation: Homogeneous Transformation
In many practical cases, you need to apply both a rotation and a translation to an object. This can be done using **homogeneous transformation matrices**, which are 4x4 matrices that combine rotation and translation.

A homogeneous transformation matrix looks like this:

$$
T = \begin{bmatrix} R & t \\ 0 & 1 \end{bmatrix}
$$

Where:
- \(R\) is the 3x3 rotation matrix.
- \(t\) is the 3x1 translation vector.

Example in Eigen:
```cpp
Eigen::Matrix4d transform = Eigen::Matrix4d::Identity();
transform.block<3,3>(0,0) = rotation_matrix;
transform.block<3,1>(0,3) = translation;
Eigen::Vector4d point_homogeneous(point(0), point(1), point(2), 1.0);
Eigen::Vector4d transformed_point = transform * point_homogeneous;
```

### 4. Summary
- **Translation** moves objects without changing their orientation.
- **Rotation** can be represented using matrices, quaternions, or Euler angles.
- **Homogeneous transformations** combine rotation and translation into a single matrix.
- The **Eigen** library provides tools to handle these operations efficiently in C++.

### 5. Resources
- [Eigen Documentation](https://eigen.tuxfamily.org/dox/GettingStarted.html)
- [3D Rotations in Robotics](https://en.wikipedia.org/wiki/Rotation_matrix)

