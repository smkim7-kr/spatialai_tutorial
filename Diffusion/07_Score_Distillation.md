# KAIST CS492D (Fall 2024) — Lecture 10: Score Distillation 2

## Score Distillation: From Images to 3D

### Motivation
- Extend diffusion models beyond images to other modalities like **3D** (e.g., point clouds, voxels).
- Major challenge: **lack of large-scale 3D datasets**.
- Goal: Generate **diverse, imaginative 3D shapes** (e.g., "ghost eating a hamburger") **without relying on large datasets**.

### Key Idea
- **Distill pretrained image diffusion models** to generate 3D content without training from scratch.

---

## 3D Generation Methods

### DietNeRF
- Few-shot 3D reconstruction using:
  1. **Image + viewpoint priors**
  2. **CLIP embedding distance** (image-text similarity)

### DreamFields
- Zero-shot 3D generation without image priors.
- Uses **CLIP distance** between generated 3D render and text.

### DreamFusion
- Uses **pretrained image diffusion model** instead of CLIP.
- Reformulates diffusion model as a **discriminator**:
  - Input: (text, rendered image)
  - Output: alignment score

---

## Score Distillation Sampling (SDS)

### Pipeline
1. Render 3D scene from parameters \( \theta \) at view \( c \) → \( x_0 = g(\theta; c) \)
2. Add noise → \( x_t = \sqrt{\alpha_t} x_0 + \sqrt{1 - \alpha_t} \epsilon_t \)
3. Predict noise \( \hat{\epsilon}_t(x_t, y, t) \)
4. Minimize loss: \( L = \| \hat{\epsilon}_t - \epsilon_t \|^2 \)
5. Update 3D parameters \( \theta \) using gradient descent.

### Optimization Trick
- Ignore **Jacobian of noise predictor** to save memory.
- Empirically shown to work well.

### Use Cases
- **3D generation**: DreamFusion (leveraging 5B image-trained diffusion model)
- **Vector images**, **4D generation**, **Mesh editing**

---

## SDS Limitations

- Uses **only 2D priors** → lacks **3D contextual consistency**.
- Tradeoff:
  - **Low CFG weight**: better alignment but unstable.
  - **High CFG weight**: stable but reduced diversity.

### Improvement: Variational Score Distillation (VSD)
- Fine-tune noise predictor using **LoRA** with \( \epsilon_t \) replacement.

---

## DDIM Reverse Process & SDS Equivalence

### DDIM Sampling (Max Variance Case)
- Set \( \sigma_t = \sqrt{1 - \alpha_{t-1}} \)
- Forward: \( x_t \rightarrow x_0 \rightarrow x_{t-1} \)
- If \( \sigma_t = 0 \): deterministic sampling

### SDS = DDIM with:
- Random timestep \( t \)
- Proxy variable \( \theta \) encodes \( x_{0|t} \)
- SDS update ≈ DDIM inversion + backprop through \( \theta \)

### Key Insight
> SDS is equivalent to DDIM reverse with maximum variance and parameter update in 3D latent space.

---

## Score Distillation via Inversion (SDI)

### Goal
Make SDS more similar to DDIM **denoising** process.

### Method
- Apply **DDIM Inversion**: recover \( x_t \) from \( x_{0|t} \)
- Then proceed with standard DDIM reverse steps
- Either:
  - Use **random timestep**
  - Or **decrease timestep** like DDIM

### Tradeoffs
- **+** Better convergence and 3D quality
- **–** Slower: extra DDIM inversion per step

---

## Extension to Editing

### Problem
SDS **loses identity** of original image during editing.

### Delta Denoising Score (DDS)
- Predict noise for **both** edited and reference images using **same noise**.
- Compare predicted noise directly.
- Often fails to preserve appearance or geometry.

### Instruct-NeRF2NeRF
- Iteratively updates 3D representation using multi-view edits.
- Limitation: **Cannot edit geometry** (e.g., pose changes).

---

## Posterior Distillation Sampling (PDS)

### Motivation
Enable **both** geometric and appearance changes.

### Core Idea
- Instead of \( \epsilon_t \), compare **noise trajectory** \( z_t \).
- Loss: 
  \[
  L_{\text{PDS}} = \mathbb{E}_{t,\epsilon} \left[ \| z(x_t, y, t) - z(x_t^{\text{ref}}, y^{\text{ref}}, t) \|^2 \right]
  \]
- Apply same noise \( \epsilon \) to both reference and edited images.

### Toy 2D Example
- Classify red vs. blue points.
- SDS: all red points → same blue point (low diversity)
- DDS: red → diverse blue, but strays too far
- **PDS**: minimally shifts red → diverse blue, preserving identity

### Benefits
- Combines **DDS term** + **reference preservation term**
- Can apply to:
  - **Image editing**
  - **3D scene editing**
  - **Vector image editing (SVG)**

---

## Summary

| Method | Key Feature | Limitation |
|--------|-------------|------------|
| SDS | Aligns with diffusion noise | Loses identity, lacks 3D consistency |
| SDI | Adds DDIM inversion | Time overhead |
| DDS | Adds reference noise prediction | Still loses identity |
| PDS | Compares noise trajectory \( z_t \) | Best tradeoff in editing |

---
