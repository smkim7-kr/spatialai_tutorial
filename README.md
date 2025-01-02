# Spatial_tutorial

### Overview
This repository contains a series of tutorials and examples covering various topics in **spatial AI**, **3D computer vision**, **robotics**, and the underlying mathematical concepts. Each directory focuses on a distinct subject—ranging from C++ programming to CUDA, OpenMP, ROS2, and SLAM.

---

## Table of Contents

| Topic                    | Description                                                                                                                                                                                                                                                                         |
|--------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| [3DCV](3DCV/)            | Lecture notes on [NUS 3D Computer Vision](https://www.youtube.com/playlist?list=PLxg0CGqViygP47ERvqHw_v7FVnUovJeaz), covering traditional 3D computer vision theories and multiple view geometry.                                                                                   |
| [Cpp](Cpp/)             | C++ and Modern C++ codes (from beginner to advanced). Inspired by [The Cherno C++ playlist](https://www.youtube.com/playlist?list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb) and supplemented by [ALIDA’s modern C++ note](https://drive.google.com/viewerng/viewer?url=https://github.com/gyubeomim/gb-supp-mat/blob/main/blog/Notes_on_Modern_C%2B%2B.pdf?raw%3DT). |
| [CUDA](CUDA/)            | Basics of CUDA programming (using VS 2022). Code is derived from the Korean book [CUDA 기반 GPU 병렬 처리 프로그래밍](https://product.kyobobook.co.kr/detail/S000202185653), covering parallel GPU computing fundamentals.                                                                 |
| [Docker](Docker/)        | Basic Docker commands and templates. Some templates are inspired by [@changh95’s GitHub repo](https://github.com/changh95/fastcampus_slam_codes).                                                                                                                                  |
| [Maths](Maths/)          | Notes on linear algebra, multivariate calculus, and matrix calculus for spatial AI. Based on [Angelo’s Math Notes](https://angeloyeo.github.io/2019/09/08/LHopital_rule_en.html).                                                                                                                                  |
| [OpenMP](OpenMP/)        | An introduction to OpenMP for parallel programming. Code is inspired by [@bluekds’s GitHub repo](https://github.com/bluekds/OpenMP-Programming).                                                                                                                                    |
| [ROS2](ROS2/)            | Guides on ROS2 for mobile robotics, covering TF2, URDF, Gazebo, sensors, slam_toolbox, and nav2. Based on [Articulated Robots playlist](https://www.youtube.com/playlist?list=PLunhqkrRNRhYAffV8JDiFOatQXuU-NnxT).                                                                    |
| [SLAM](SLAM/)            | SLAM in Python, covering ICP, PnP, Lie Algebra, transformations, triangulation, point cloud processing, RANSAC, non-linear optimization, etc. C++ examples can be found in [@changh95’s repo](https://github.com/changh95/fastcampus_slam_codes).                                     |
| [VLM101](VLM101/)            | Diverse modules in Large Visual Language Models implementation, covering RoPE, grouped multi query attention, flash attention, tokenization. Some codes are based on [Umar Jami videos](https://github.com/hkproj)                                   |
| [#TODO Jax & Rust](/)            | |


---

## Code Analysis & Related Projects

Below are code analyses and projects that relate closely to the tutorials above. Each entry highlights the relevant topics and includes a short description.

| Code Analysis / Project                                                            | Related Topics            | Description                                                                                                                                                                                                                             |
|------------------------------------------------------------------------------------|---------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| [mmdetection3d-visualizer](https://github.com/smkim7-kr/mmdet3d-visualizer)        | 3DCV                      | Added a bird’s-eye-view visualization module with a full inference pipeline. Offers detailed code analysis of how 3D detection pipelines work in `mmdetection3d`.                                                                       |
| [gsplat rasterization code analysis](code_analysis/gsplat_rasterization.md)        | 3DCV, CUDA, Cpp           | Analyzes **Gsplat Gaussian rasterization** including projection, encoding, and rendering steps. Explains how data flows through the pipeline and how it’s optimized.                                                                      |
| [Nerfstudio vanilla nerf code analysis](code_analysis/nerfstudio.md)               | 3DCV                      | Explores the **vanilla NeRF** implementation in Nerfstudio. Focuses on the volumetric rendering pipeline and the structure of the code base.                                                                                            |
| [Nerfstudio splatfacto pipeline code analysis](code_analysis/splatfacto.md)        | 3DCV                      | Examines the **Splatfacto** pipeline in Nerfstudio, illustrating how splatting or point-based rendering is integrated and how it differs from vanilla NeRF.                                                                              |
| [VQ-VAE code analysis](https://github.com/smkim7-kr/VLM101/tree/master/vqvae)      | VLM101                    | A **VQ-VAE** (Vector Quantized Variational Autoencoder) PyTorch implementation with annotated code and a breakdown of the architecture and training loop.                                                                                |
| [Flash Attention](https://github.com/smkim7-kr/VLM101/tree/master/FlashAttention)  | VLM101                    | Implementation of **Flash Attention** in Triton, highlighting optimization strategies for attention mechanisms.                                                                                                                           |
| [Simple-PaliGemma](https://github.com/smkim7-kr/VLM101/tree/master/Diffusion_Model)| VLM101                    | Implements a **PaliGemma diffusion model** with in-depth comments on the pipeline and the code structure.                                                                                                                                |
| [#TODO glim](https://github.com/koide3/glim)                                       | SLAM, OpenMP, CUDA, ROS2  | Planned code analysis of **Glim**—a SLAM solution that integrates parallelization via OpenMP and CUDA within a ROS2 framework.                                                                                                            |

---

![svg image](main.svg "Example")
