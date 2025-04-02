# Lecture 11: Diffusion Synchronization (KAIST CS492D, Fall 2024)

## Recap: Score Distillation Sampling (SDS)
- Leverages pretrained 2D image diffusion models for 3D generation.
- Instead of enforcing view consistency, SDS runs backpropagation through the loss function used during diffusion model training.
- Updates are made via rendered 2D images rather than scarce 3D data.
- Applications:
  - 2D image generation (`g(\theta)` = identity)
  - 3D object generation
- Comparison with reverse diffusion:
  - Diffusion: reverse trajectory in pixel space
  - SDS: optimizes rendered images from 3D representation
- Limitation: Convergence struggles at low classifier-free guidance (CFG) weights; high CFG hampers output diversity.

---

## Two Spaces in Diffusion Synchronization
- **Canonical Space**: Target space where desired data lies (e.g., panorama image, texture map).
- **Instance Space**: Where the pretrained diffusion model operates (e.g., square image, low-resolution latent).
- **Projection**: Canonical → Instance
- **Unprojection**: Instance → Canonical

### Applications
- **Panoramas**: 
  - Canonical: panoramic image
  - Instance: square images from cropping
- **Mesh Textures**:
  - Canonical: texture image space
  - Instance: square image
- **Ambiguous Images**: Transformation or orientation leads to different interpretations (canonical and instance are the same)
- **Zooming Videos**: Mapping between zoomed-in/out views (canonical = instance = image space)
- **Long-Duration Motion**: Canonical = long time sequence, Instance = short segments

---

## Diffusion Synchronization (Joint Reverse Process)
- Instead of SDS, run multiple reverse processes jointly across instance spaces.
- Use latent diffusion for memory efficiency.

### MultiDiffusion [Bar-Tal et al., 2023]
- Canonical: panorama latent space
- Instance: square latent crops
- Key idea:
  1. Crop from canonical space → project to instance
  2. Reverse diffusion in instance space (DDIM)
  3. Unproject and **average overlapping regions** in canonical space
- Without averaging, artifacts/discontinuity appear at seams.

### DDIM Deterministic Reverse Process:
For time step \( t ightarrow t-1 \):
1. \( \epsilon_t = \epsilon_	heta(x_t, t) \)
2. \( \hat{x}_0 = rac{x_t - \sqrt{1 - lpha_t} \epsilon_t}{\sqrt{lpha_t}} \)
3. \( x_{t-1} = \sqrt{lpha_{t-1}} \hat{x}_0 + \sqrt{1 - lpha_{t-1}} \epsilon_t \)

### Limitation (360° Panoramas / Mesh Textures):
- Projection is no longer square due to distortion.
- Mapping is **non-injective**; unprojection requires **interpolation**.
- Averaging \( x_t \) in canonical space yields blurry, unrealistic results.

### Alternatives to Averaging \( x_t \):
- \( \epsilon_t \): noisy direction vector → averaging harms denoising trajectory
- \( x_0 | t \): predicted clean image → **preferred** due to minimal deviation

---

## Five Synchronization Strategies
| Case | Denoising Space | Averaged Quantity       |
|------|------------------|--------------------------|
| 1    | Instance         | \( \epsilon_t \)         |
| 2    | Instance         | \( x_0 | t \)           |
| 3    | Instance         | \( x_t \)               |
| 4    | Canonical        | \( \epsilon_t \)         |
| 5    | Canonical        | \( x_0 | t \)           |

- Case 2 and 5 preferred: averaging \( x_0 | t \) gives better results.
- Case 1/4 problematic: direction average can misguide trajectory.
- Case 3 leads to distribution mismatch.

---

## Comparison to Other Techniques
### Iterative Update
- Fill texture progressively per view.
- Limitation: lacks global consistency across views.

### SDS vs. Synchronization
| SDS                      | Synchronization            |
|-------------------------|----------------------------|
| Works without conditions| Needs strong conditions    |
| Less realistic output   | More realistic when guided |
| Better coverage         | May fail to converge       |

---

## Fine-Tuning for Joint Diffusion: MVDiffusion
- Based on **ControlNet** concept:
  - Small dataset
  - Few added parameters (zero convs)
  - Freeze pretrained weights

### Correspondence-Aware Attention (CAA)
- Requires predefined pixel correspondence across instance views.
- Architecture:
  - CAA → ZeroConv → FFN → ZeroConv (per layer)
- Pros:
  - Significantly improved output quality
- Cons:
  - Requires specific canonical-instance mapping
  - May fail for out-of-domain prompts

---

## Summary
- **SDS**: Flexible, but requires careful loss design.
- **Synchronization**: Leverages pretrained models via joint denoising across views.
- **Best results**: When averaging \( x_0 | t \), not \( x_t \) or \( \epsilon_t \).
- **Fine-tuning** (e.g., MVDiffusion): Great when mapping is known, but not generalizable.

---

## References
- Poole et al., *DreamFusion*, ICLR 2023
- Bar-Tal et al., *MultiDiffusion*, ICML 2023
- Kim et al., *SyncTweedies*, NeurIPS 2024
- Tang et al., *MVDiffusion*, NeurIPS 2023
- Lee et al., *SyncDiffusion*, NeurIPS 2023
- Geng et al., *Visual Anagrams*, CVPR 2024
- Haque et al., *IN2N*, 2023
- Richardson et al., *TEXTure*, 2023
- Chen et al., *Text2Tex*, ICCV 2023
