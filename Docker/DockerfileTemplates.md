# Commonly used commands (in Dockerfile format) in SpatiaiAI 
### (Adapted from https://github.com/changh95/fastcampus_slam_codes/tree/main)

## Contents
* [Essential libraries](#essential-libraries)
* [OpenCV](#opencv-48)
* [Eigen](#eigen-33)
* [Sophus](#sophus)
* [Pangolin](#pangolin-06)
* [PCL](#pcl)
* [ceres-solver](#ceres-solver )
* [DBoW2](#dbow2)
* [Github repository](#github-repository)
* [Pip](#install-libraries-via-pip)
* [ROS1](#ros21-included-slam)
* [Miniconda](#Miniconda-(using-libmamba))

## Essential libraries
```Dockerfile
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y && apt-get upgrade -y

RUN apt-get install build-essential -y && \
    apt-get install cmake -y && \
    apt-get install git -y && \
    apt-get install sudo -y && \
    apt-get install wget -y && \
    apt-get install ninja-build -y && \
    apt-get install software-properties-common -y && \
    apt-get install python3 -y && \
    apt-get install python3-pip -y && \
    apt-get install -y ssh && \
    apt-get install -y gcc && \
    apt-get install -y g++ && \
    apt-get install -y gdb && \
    apt-get install -y cmake && \
    apt-get install -y rsync && \
    apt-get install -y tar && \
    apt-get install -y vim && \
    apt-get install -y x11-utils && \
    apt-get install -y x11-apps && \
    apt-get install -y zip &&\
    apt-get clean
```

## OpenCV 4.8
```Dockerfile
RUN apt-get install -y cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
RUN wget https://github.com/opencv/opencv/archive/4.8.1.zip &&\
    unzip 4.8.1.zip &&\
    cd opencv-4.8.1 &&\
    mkdir build && cd build &&\
    cmake .. &&\
    make -j4 &&\
    make install &&\
    cd ../../
```
### for different OpenCV versions
```Dockerfile
...
RUN wget https://github.com/opencv/opencv/archive/{version}.zip &&\
    unzip {version}.zip &&\
    cd opencv-{version} &&\
...
```

### Note: OpenCV build error
Sometimes there is a case where OpenCV build fails. Add -DBUILD_TESTS=OFF -DBUILD_PERF_TESTS=OFF options while building
```Dockerfile
cmake -DBUILD_TESTS=OFF -DBUILD_PERF_TESTS=OFF -GNinja ..
```


## Eigen 3.3
```Dockerfile
RUN wget https://gitlab.com/libeigen/eigen/-/archive/3.3.8/eigen-3.3.8.zip &&\
    unzip eigen-3.3.8.zip &&\
    cd eigen-3.3.8 &&\
    mkdir build && cd build &&\
    cmake .. &&\
    make -j4 &&\
    make install &&\
    cd ../../
```

### for different Eigen versions
```Dockerfile
...
RUN wget https://gitlab.com/libeigen/eigen/-/archive/{version}/eigen-{version}.zip &&\
    unzip eigen-{version}.zip &&\
    cd eigen-{version} &&\
...
```

## Sophus
```Dockerfile
RUN wget https://github.com/strasdat/Sophus/archive/refs/tags/1.22.10.zip &&\
    unzip 1.22.10.zip &&\
    cd Sophus-1.22.10 &&\
    mkdir build && cd build &&\
    cmake .. &&\
    make -j4 &&\
    make install && \
    cd ../../
```

## Pangolin 0.6
```Dockerfile
RUN apt-get install -y mesa-utils && \
    apt-get install -y libgl1-mesa-glx && \
    apt-get install -y libglu1-mesa-dev && \
    apt-get install -y libglew-dev &&\
    apt-get install -y libglvnd-dev &&\
    apt-get install -y libgl1-mesa-dev &&\
    apt-get install -y libegl1-mesa-dev &&\
    apt-get install -y mesa-common-dev

RUN wget https://github.com/stevenlovegrove/Pangolin/archive/refs/tags/v0.6.zip &&\
    unzip v0.6.zip &&\
    cd Pangolin-0.6 &&\
    mkdir build && cd build &&\
    cmake .. &&\
    make -j4 &&\
    make install &&\
    cd ../../
```

## PCL
```Dockerfile
RUN apt-get install -y libpcl-dev
```

## ceres-solver 
```Dockerfile
RUN apt-get install -y libgoogle-glog-dev libgflags-dev libatlas-base-dev libsuitesparse-dev &&\
    wget https://github.com/ceres-solver/ceres-solver/archive/refs/tags/2.1.0.zip &&\
    unzip 2.1.0.zip &&\
    cd ceres-solver-2.1.0 && \
    mkdir build && cd build &&\
    cmake .. &&\
    make -j4 &&\
    make install &&\
    cd ../../
```

## DBoW2
```Dockerfile
RUN git clone https://github.com/dorian3d/DBoW2.git &&\
    cd DBoW2 &&\
    mkdir build && cd build &&\
    cmake -GNinja .. &&\
    ninja &&\
    ninja install &&\
    cd ../../
```

## Github repository
```Dockerfile
# Git repository has different dependencies and libraries, install them if required
RUN git clone {repo name (.git)} &&\
    cd {repo name} && mkdir build && cd build &&\
    cmake -GNinja .. &&\
    ninja &&\
    ninja install
# required if git repository has submodules/3rd party libraries
RUN git submodule init && git submodule update
# Same effect from above code
RUN git submodule update --init 
```

## Install libraries via pip
```Dockerfile
RUN pip3 install {library}
# example: open3d
RUN pip3 install open3d
# can also specify versions
RUN pip3 install open3d==0.17.0
```

## ROS1-included SLAM
```Dockerfile
FROM ros::{distro}

# OR

RUN apt-get update -y && \
    apt-get install -y sudo unzip git libeigen3-dev wget build-essential gdb curl cmake \
    libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev libglew-dev 
RUN apt-get install -y lsb-release &&\
    sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list' &&\
    curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add - &&\
    apt-get update -y &&\
    apt install -y ros-{distro}-desktop-full
RUN rosdep init && rosdep update

RUN mkdir -p /root/catkin_ws/src
WORKDIR /root/catkin_ws/src
RUN /bin/bash -c '. /opt/ros/{distro}/setup.bash; catkin_init_workspace'

RUN git clone {github repo (.git)}
... Building process...

WORKDIR /root/catkin_ws
RUN /bin/bash -c '. /opt/ros/{distro}/setup.bash; catkin_make -DBUILD_test=ON'
RUN sed -i "6i source \"/root/catkin_ws/devel/setup.bash\"" /ros_entrypoint.sh
```

## Miniconda (using libmamba)
```Dockerfile
ENV CONDA_DIR /opt/conda
ENV CONDA_OVERRIDE_CUDA "11.3.1"
ENV CONDA_OVERRIDE_GLIBC="2.17"

RUN wget --quiet https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh -O ~/miniconda.sh && \
    /bin/bash ~/miniconda.sh -b -p /opt/conda

ENV PATH=$CONDA_DIR/bin:$PATH 

RUN conda update -n base conda &&\
    conda install -n base conda-libmamba-solver &&\
    conda config --set solver libmamba
```