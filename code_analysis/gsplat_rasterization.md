# Following gsplat rasterization code 

##### NOTE: if the link shows wrong code, it may be because main commit is different from when I've written this
##### Use ff2da2e2a5dac795094edf8d5f867ba1d3c6931a instead of main in the link

# Important files
| File | Description |
|-------------------------------------------------|-------------------------|
| `nerfstudio/blob/main/nerfstudio/models/splatfacto.py` | Whole pipeline for 3d gaussian splatting |
| `gsplat/blob/main/gsplat/rendering.py` | gsplat rasterization rendering |
| `gsplat/blob/main/gsplat/cuda/csrc/fully_fused_projection_fwd.cu` | CUDA kenrel for 3d gaussian projection to 2d image space |
| `gsplat/blob/main/gsplat/cuda/csrc/isect_tiles.cu` | CUDA kernel for encoding keys for gaussians and their itersecting tiles |
| `gsplat/blob/main/gsplat/cuda/csrc/rasterize_to_pixels_fwd.cu` | CUDA kernel for tile-based rendering |
| `gsplat/blob/main/gsplat/cuda/_wrapper.py` | Wrapper file that calls CUDA kernel |
| `gsplat/blob/main/gsplat/cuda/csrc/ext.cpp` | Pybind11 that bridge between python api and CUDA kernels  |


| Image | Description |
|-------------------------------------------------|-------------------------|
| <img src="images/rasterize_arg.png" alt="drawing" width="3000"/> | Rasterization inputs @ https://github.com/nerfstudio-project/gsplat/blob/main/gsplat/rendering.py#L28<br>1. means, quats, scales, opacities, colors, veiwmats, Ks: gaussians, cameras parameters<br>NOTE: colors.shape = [N, K, 3] where K is SH coefficients or [N, D] if not SH<br>2. near_plane, far_plane: clipping planes respect to camera frustum<br>3. radius_clip: Gaussians below radius_clip size will be ignored for efficiency<br>4. tile_size: tile_size of image for rasterization<br>5. render_mode: determines whether to output rgb/depth/opacity<br>6. sparse_grad, packed, channel_chunk: for efficiency and memory management<br>7. absgrad: from "AbsGS: Recovering Fine Details for 3D Gaussian Splatting" paper<br>8. rasterize_mode: from "Mip-Splatting: Alias-free 3D Gaussian Splatting" paper|
| <img src="images/project_3dto2d.png" alt="drawing" width="3000"/> | fully_fused_projection() which projects 3D gaussians to 2D pixel space @ https://github.com/nerfstudio-project/gsplat/blob/main/gsplat/rendering.py#L297 <br> More detail at row below|
| <img src="images/_FullyFusedProjection.png" alt="drawing" width="3000"/> | fully_fused_projection() @ https://github.com/nerfstudio-project/gsplat/blob/main/gsplat/cuda/_wrapper.py#L203 <br> calls _FullyFusedProjection() <br><br> _FullyFusedProjection() @ https://github.com/nerfstudio-project/gsplat/blob/main/gsplat/cuda/_wrapper.py#L775 <br> calls CUDA kernel through _make_lazy_cuda_func() <br> forward calls "fully_fused_projection_fwd" and backward calls "fully_fused_projection_bwd"| 
| <img src="images/sh.png" alt="drawing" width="3000"/> | Compute spherical harmonics through colors using direction vectors and spherical_harmonics() funcion<br>Clamp colors to prevent negative SH colors| 
| <img src="images/multigpu.png" alt="drawing" width="3000"/> | When Multi-GPU is used, distribution Gaussians with respective GPUs|
| <img src="images/isect_tiles.png" alt="drawing" width="3000"/> | isect_tiles() which identifies intesercting image tiles of gaussians @ https://github.com/nerfstudio-project/gsplat/blob/main/gsplat/rendering.py#L494 <br> Gaussians are mapped to screen-spaced tiles based on their position and radius <br> More detail at row below|
| <img src="images/isect_tiles2.png" alt="drawing" width="3000"/> | isect_tiles() @ https://github.com/nerfstudio-project/gsplat/blob/main/gsplat/cuda/_wrapper.py#L342 <br> calls CUDA kernel through _make_lazy_cuda_func() <br> cuda isect_tiles() are defined @ https://github.com/nerfstudio-project/gsplat/blob/main/gsplat/cuda/csrc/isect_tiles.cu#L15 |
| <img src="images/rasterize_pixel.png" alt="drawing" width="3000"/> | split colors in n_chunks chunks, then perform actual rasterization (since color, 2d gaussians, tile appings are all ready!)|


# fully_fused_projection_fwd 
##### @ https://github.com/nerfstudio-project/gsplat/blob/main/gsplat/cuda/csrc/fully_fused_projection_fwd.cu

| Image | Description |
|-------------------------------------------------|-------------------------|
| <img src="images/ffpf1.png" alt="drawing" width="3000"/> | CUDA kernel fully_fused_projection_fwd_kernel(), where each thread processes one gaussian for one camera<br>Therefore, total C * N threads working in parallel<br>Fetch gaussian center and camera parameters through thread ids (gid, cid)|
| <img src="images/ffpf2.png" alt="drawing" width="3000"/> | Reorder rotation matrices since openGL(glm) library is column-major <br> pos_world_to_cam() transforms gaussian centre to camera space i.e. $mean_c = R * mean_w + t$<br> Finally, using near_plane/far_plane discard gaussians out of the range<br>NOTE: OpenGL(glm) library optimized for GPU computations (repsect to parallel computations) e.g. glm::vec3, glm::mat3, glm::mat4|
| <img src="images/ffpf3.png" alt="drawing" width="3000"/> | Compute 3D covariance using rotation(quats) and scales $\Sigma = RSS^TR^T$ <br> quat_scale_to_covar_preci() is defined under include/quat_scale_to_covar_preci.cuh <br> covar_world_to_cam() transforms 3D covariance to camera space|
| <img src="images/qscov.png" alt="drawing" width="3000"/> | quat_scale_to_covar_preci() definition @ https://github.com/nerfstudio-project/gsplat/blob/main/gsplat/cuda/include/quat_scale_to_covar_preci.cuh<br>$\Sigma = RSS^TR^T$|
| <img src="images/covw2c.png" alt="drawing" width="3000"/> | covar_world_to_cam() definition @ https://github.com/nerfstudio-project/gsplat/blob/main/gsplat/cuda/include/transform.cuh#L39<br>$\Sigma_{c} = R\Sigma_{w}R^T$|
| <img src="images/ffpf4.png" alt="drawing" width="3000"/> | Projects 3D Gaussians into 2D image (of particular camera view and 3d gaussian) <br> persp_proj() is defined under proj_fwd.cu|
| <img src="images/persp_proj.png" alt="drawing" width="3000"/> | presp_proj() projects 3D Gaussian into 2D Gaussian @ https://github.com/nerfstudio-project/gsplat/blob/main/gsplat/cuda/include/proj.cuh#L80<br>1. Extract (x,y,z) 3D Gaussian mean<br>2. Compute FOV limits based of camera resolution and focal length<br>3. Normalize depth<br>4. Check whether projected gaussians are within frustum boundaries, use (tx,ty) to prevent out-of-bound (x,y) values<br>5. Compute Jacobian matrix that maps 3D covariance to 2D covariance<br>6. Calculate 2D covariance: $\Sigma_{2d} = J\Sigma_{3d}J^T$<br>7. Calculate 2D mean: $u = f_x*(x/z) + c_x, v = f_y*(y/z) + c_y$|
| <img src="images/cull.png" alt="drawing" width="3000"/> | Cull small gaussian below certain radius and outside frustum<br>1. Compute b: average variance of Gaussian along principal axis<br>2. Compute v1: largest eigenvaalue, which repersents major axis of the ellipse (this is derived from quadratic form for variance)<br>3. Compute radius: approximated as 3 std along major axis<br>**NOTE: Projected gaussians should have two principle axis, which are two eigenvalues. However, in rasterization and culling, single radius (i.e. radii[idx]) are used for computational efficiency. Here, 3 std of larger eigenvalue (=major axis of projected gaussian) ensures sufficient approximation since it covers 99.7% of gaussians**|
| <img src="images/ffpf5.png" alt="drawing" width="3000"/> | Cull gaussian by making radius size 0 if small or outside of image pixel space<br>NOTE: This is different from 3D frustum culling in persp_proj() function: frustum culling only checks for gaussian center in 3d space, while here it checks while gaussian in 2d screen space|
| <img src="images/ffpf6.png" alt="drawing" width="3000"/> | Compute inverse of 2d covariance <br> Output radius/mean/depth/conic(inverse covariance) of particular gaussian at particular camera view image<br>NOTE: 2D covariance is inverted (as conic) because it is used for gaussian evaluation, it only stores upper traingle because 2d cov is symmetric|

# isect_tiles 
##### @ https://github.com/nerfstudio-project/gsplat/blob/main/gsplat/cuda/csrc/isect_tiles.cu

| Image | Description |
|-------------------------------------------------|-------------------------|
| <img src="images/isect1.png" alt="drawing" width="3000"/> | Boundary check : 1. if thread index exceeds total number of gaussians, return 2. if gaussian radius isn't positive, return|
| <img src="images/isect2.png" alt="drawing" width="3000"/> | Normalize gaussian center in tile coordinates e.g. tile_size=16, center=(32, 0) => tile_x = 32/16 = 2<br>Scales gaussian radius into tile space (as mentioned before, again here we use single radius per gaussian) e.g. radius 32 => scales to 32/16=2<br> Calculate tile_min and tile_max, which is top-left and bottom-right corner where gaussian intersects the tiles|
| <img src="images/isect3.png" alt="drawing" width="3000"/> | First (of the two) pass - quickly count number of tiles intersected by the gaussian into tiles_per_gauss<br> purpose: allocate memory|
| <img src="images/isect4.png" alt="drawing" width="3000"/> | Prepare for the second pass: assign key for each tiles gaussians up to 64 bits<br> Lower 32 bits encode **projected depth** (depth_id_enc), used for depth sort in alpha blending <br> Upper bits encode 10 bits index of **camera_id** (cid_enc) then 22 bits of **tile id** (tile_id) <br> Such encoding is required for quick GPU Radix Sort<br>cum_tiles_per_gauss, calculated after first pass, has cumulative tile counts of previous gaussians<br>cur_idx contains starting index of intersecting tiles of current idx gaussian<br>Iterate over itersected tile (i,j)<br>isect_ids containes encoded key, and flatten_ids contain gaussian-to-tile mapping indicies|
| <img src="images/isect5.png" alt="drawing" width="3000"/> | Radix Sort @ https://github.com/nerfstudio-project/gsplat/blob/main/gsplat/cuda/csrc/isect_tiles.cu#L251<br>Set keys as isect_ids and values as flatten_ids<br>Sort keys and rearrange corresponding values<br>Sort order are camera_id - tile_id - depth, which are optimized for per-camera, per-tile and per-depth rendering, which are highly parallelizable and improves memory locality<br>Use CUDA Radixsort API<br>NOTE: cub::DeviceRadixSort::SortPairs sort keys in ascending order i.e. close-to-far depth order|

# rasterize_to_pixels
##### @ https://github.com/nerfstudio-project/gsplat/blob/main/gsplat/cuda/csrc/rasterize_to_pixels_fwd.cu

| Image | Description |
|-------------------------------------------------|-------------------------|
| <img src="images/rast1.png" alt="drawing" width="3000"/> | Calling rasterization CUDA kernel @ https://github.com/nerfstudio-project/gsplat/blob/main/gsplat/cuda/csrc/rasterize_to_pixels_fwd.cu#L262<br> Highly parallelizable tile-based rendering code as each CUDA block processes single tile and each CUDA thread processes single pixel within the tile(block) i.e. Total block = # of camera * tile_height * tile_width|
| <img src="images/rast2.png" alt="drawing" width="3000"/> | Retrieve ids from grid/block/thread of CUDA kernel<br>gridDim.x are parallel rendered cameras, Each block in x dimension corresponds to specific camera i.e. blockIdx.x = 10 is 11th camera<br>gridDim.y and z corresponds to row and column tiles in the image i.e. tile_id = blockIdx.x * tile_width + blockIdx.z<br> x and y dimensions within the block (block.thread_index().x/y) repersents column/row of pixel within a tile i.e i = blockIdx.y * tile_size + threadIdx.y<br>**Summary: 3D grid: (camera, tile_rows, tile_colums) & 2D block: (pixel rows, pixel columns), Each grid contributes of single camera(=image) & each block contributes to single tile within the single camera**|
| <img src="images/rast3.png" alt="drawing" width="3000"/> | Gaussian relevant to a tile loaded to shared memory, and processed in batches, therefore HBM memory reads reduced|
| <img src="images/rast4.png" alt="drawing" width="3000"/> | Each thread within the batch fetch single guassian from low depth to high depth (which was already sorted before)|
| <img src="images/rast5.png" alt="drawing" width="3000"/> | For each gaussian in the batch, calculate relevant factors for alpha blending to color pixel<br>1. conic: inverse of 2d gaussian covariance. Inverse covariance is easier to calculate sigma(density)<br>2. delta:distance between gaussian center and pixel. Used as inputs of conic equation, which dervies sigma<br>3. sigma: Evaluate gaussian contribution to a pixel, by calculating distance from gaussian center using conic matrix<br>4. alpha: Caculate opacity $\alpha = (1-e^{-\sigma})$<br>5. T: transmittance calculated by alpha $T = T * (1 - \alpha)$|
| <img src="images/rast6.png" alt="drawing" width="3000"/> | Final rendering of color and weights<br>1. vis: weights for color $\Sigma T*\alpha$<br>2. c_ptr: pointer or current color of each pixel<br>3. pix_out: accumulated final rendered color $C_{pixel} = C_{pixel} + C_{guassian} * (\alpha * T)$<br>4. rendered_alphas, rendered_colors: final pixel, rendered_colors are blended with background $\alpha_{pixel} = 1 - T$ and $C_{pixel} = C_{pixel} + T * C_{background}$|