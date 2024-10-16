# Docker (from Spatial AI Persepctive)

## Benefits of Using Docker for Robotics:
- **Consistency**: Docker allows developers to run the same code across different environments without worrying about version conflicts or dependencies.
- **Isolation**: Robotics projects often involve multiple software stacks (e.g., ROS, machine learning libraries, and hardware drivers). Docker ensures that each of these environments can be isolated, avoiding potential conflicts.
- **Reproducibility**: Docker images allow others to reproduce your robotics setup with minimal effort.
- **Multi-Architecture Support**: Useful for deploying robotics applications to different hardware platforms (e.g., x86, ARM for Raspberry Pi).

## Basic usage

### 1. **Pulling Docker Images**

Before starting a container, pull the image from Docker Hub or another registry. Common images include ROS, Gazebo, and various robotic libraries.

```bash
docker pull osrf/ros:noetic-desktop-full  # ROS Noetic (Desktop version)
docker pull osrf/ros:foxy-desktop         # ROS2 Foxy (Desktop version)
docker pull osrf/gazebo                   # Gazebo Simulation
```

### 2. **Running Containers**

Command to start a container based on an image

```bash
docker run -it osrf/ros:noetic-desktop-full

# Access graphical applications lik Rviz or Gazebo
xhost +local:docker  # Allow Docker to access your display
docker run -it --rm \
    --env="DISPLAY" \
    --env="QT_X11_NO_MITSHM=1" \
    --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
    osrf/ros:noetic-desktop-full
```

### 3. **Accessing Devices (e.g., USB, Camera, LIDAR)**

Access to hardware devices. Use --device flag to pass device

```bash
# pass the /dev/ttyUSB0 device
docker run -it --device=/dev/ttyUSB0 osrf/ros:noetic-desktop-full
```

### 4. **GPU Acceleration**

Used in vision processing or simulations. Use --gpus flag to pass GPU resources

```bash
docker run --gpus all -it osrf/ros:noetic-desktop-full

# use docker directly provided from nvidia
docker run --gpus all -it nvidia/cuda:11.0-base nvidia-smi
```

### 5. **Volume binding**

Share directories between host machine and coontainer. Use -v flag

```bash
docker run -it -v /home/user/data:/data osrf/ros:noetic-desktop-full
```

### 6. **DockerFile**

Use to build custom docker images, can build from existing images, then add required libraries e.g. Eigen, Sophus, Pangolin

```Dockerfile
FROM osrf/ros:noetic-desktop-full

# Install additional ROS packages
RUN apt-get update && apt-get install -y ros-noetic-navigation

# Set up environment
SHELL ["/bin/bash", "-c"]
RUN source /opt/ros/noetic/setup.bash

# Default command
CMD ["roscore"]
```

### 7. **Docker Compose**

Use Docker Compose to manage multi-container applications, use yaml file format

```yaml
# One container use ROS master node, other use vision systems
version: '3'
services:
  ros-master:
    image: osrf/ros:noetic-ros-core
    command: roscore

  ros-vision:
    image: custom/vision-system
    networks:
      - ros-network

networks:
  ros-network:
```