
# Inverse Problems in Diffusion Models

## Problem Setup

We aim to find a data point \( \mathbf{x} \) corresponding to a given measurement \( \mathbf{y} \), under the corruption model:

\[
\mathbf{y} = \mathcal{A}(\mathbf{x}) + \sigma \mathbf{z}, \quad \mathbf{z} \sim \mathcal{N}(0, I)
\]

We are given \( \mathbf{y} \) and \( \mathcal{A} \), and our goal is to recover \( \mathbf{x} \), even when \( \mathcal{A} \) is non-invertible.

### Examples

- **Gaussian Deblurring**:  
  - \( \mathbf{y} \): Blurry image  
  - \( \mathcal{A} \): Gaussian convolution  
  - \( \mathbf{x} \): Clean image

- **Super-resolution**:  
  - \( \mathbf{y} \): Low-resolution image  
  - \( \mathcal{A} \): Downsampling function  
  - \( \mathbf{x} \): High-resolution image

- **Inpainting/Outpainting**:  
  - \( \mathbf{y} \): Image with background  
  - \( \mathcal{A} \): Masking operation

- **Tomography**:  
  - \( \mathbf{y} \): Projected image  
  - \( \mathcal{A} \): Projection (e.g., volume rendering)  
  - \( \mathbf{x} \): 3D object

> The inverse problem may not be unique → conditional generative models are needed.

---

## Conditional Score Estimation

Given a pretrained diffusion model with a learned unconditional score:
\[
\nabla_{\mathbf{x}_t} \log p(\mathbf{x}_t)
\]

We aim to compute the conditional score:
\[
\nabla_{\mathbf{x}_t} \log p(\mathbf{x}_t | \mathbf{y})
\]

Using Bayes’ rule:
\[
\nabla_{\mathbf{x}_t} \log p(\mathbf{x}_t | \mathbf{y}) = \nabla_{\mathbf{x}_t} \log p(\mathbf{x}_t) + \nabla_{\mathbf{x}_t} \log p(\mathbf{y} | \mathbf{x}_t)
\]

---

## Estimating \( \nabla_{\mathbf{x}_t} \log p(\mathbf{y} | \mathbf{x}_t) \)

### Option 1: Classifier Guidance
Train classifier \( p(\mathbf{y}|\mathbf{x}_t) \), then compute gradient.

### Option 2: Classifier-Free Guidance
Train noise prediction network \( \epsilon_\theta(\mathbf{x}_t, \mathbf{y}, t) \).

---

## Pseudoinverse-Guided Diffusion Models

Assume linear \( \mathcal{A}(\mathbf{x}) = A\mathbf{x} \), then:
\[
\mathbf{y} = A\mathbf{x}_0 + \sigma \mathbf{z}
\]

- Known:
  - \( p(\mathbf{y}|\mathbf{x}_0) = \mathcal{N}(A\mathbf{x}_0, \sigma^2 I) \)
  - \( p(\mathbf{x}_0|\mathbf{x}_t) = \mathcal{N}(\hat{\mathbf{x}}_0^{(t)}, r^2 I) \)

- Then:
\[
p(\mathbf{y}|\mathbf{x}_t) \approx \mathcal{N}(A\hat{\mathbf{x}}_0^{(t)}, \sigma^2 I + r^2 AA^\top)
\]

- Chain rule:
\[
\nabla_{\mathbf{x}_t} \log p(\mathbf{y}|\mathbf{x}_t) = A^\top (\sigma^2 I + r^2 AA^\top)^{-1} (\mathbf{y} - A\hat{\mathbf{x}}_0^{(t)}) \cdot \frac{\partial \hat{\mathbf{x}}_0^{(t)}}{\partial \mathbf{x}_t}
\]

---

## Diffusion Posterior Sampling (DPS)

Assume \( r = 0 \):  
\[
p(\mathbf{y}|\mathbf{x}_t) = \mathcal{N}(\mathcal{A}(\hat{\mathbf{x}}_0^{(t)}), \sigma^2 I)
\]

Then:
\[
\nabla_{\mathbf{x}_t} \log p(\mathbf{y}|\mathbf{x}_t) = -\frac{1}{2\sigma^2} \nabla_{\mathbf{x}_t} \| \mathbf{y} - \mathcal{A}(\hat{\mathbf{x}}_0^{(t)}) \|^2
\]

This gradient can be added to DDPM as:

```python
x_{t-1} = x_{t-1}^{(uncond)} - \xi_t \nabla_{x_t} \mathcal{L}(x_0^{(t)})
```

One line of code: backpropagate \( \mathcal{L}(\cdot) \) to guide sampling.

---

## Generalizing DPS: Custom Guidance

You can define any differentiable guidance loss \( \mathcal{L} \):

### Examples

- **Style Guidance**:  
  \( \mathcal{L} \): LPIPS-based perceptual style loss

- **Protein Engineering**:  
  \( \mathcal{L} \): Physical constraints (e.g., polarizability)

- **Coherent Panoramas (SyncDiffusion)**:  
  - Define \( \mathcal{L}_{LPIPS}(x_0^{(t, i)}, x_0^{(t, j)}) \)
  - Backprop to \( x_t^i \), \( x_t^j \)
  - Average \( x_{t-1} \)

---

## Summary of Guided Generation Methods

| Method                | Conditions Needed                                           |
|-----------------------|-------------------------------------------------------------|
| **ControlNet**        | - Condition-output pairs available                          |
|                       | - Same modality & spatially aligned                         |
| **Classifier-Free**   | - Enough condition-output pairs                             |
|                       | - Different modality or non-aligned OK                      |
| **DPS**               | - No condition-output pairs                                 |
|                       | - Must define differentiable objective                      |
| **SDEdit**            | - No specified condition-output relationship                |
|                       | - Find realistic data point near unrealistic input          |
