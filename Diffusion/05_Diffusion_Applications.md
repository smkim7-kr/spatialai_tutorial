# Conditional Generation in Diffusion Models

## Overview
Conditional generation in diffusion models enhances the generative process by incorporating external signals like class labels, text prompts, or images. These methods can either rely on classifiers or be classifier-free and often utilize fine-tuning techniques for practical deployment.

---

## Classifier Guidance

### Joint Distribution
We aim to model the joint distribution \( p(\mathbf{x}_t, y) = p(\mathbf{x}_t) p(y|\mathbf{x}_t) \), where \( \mathbf{x}_t \) is the noisy data at timestep \( t \), and \( y \) is a class label.

### Score Function
The score function:
\[
\nabla_{\mathbf{x}_t} \log p(\mathbf{x}_t, y) = \nabla_{\mathbf{x}_t} \log p(\mathbf{x}_t) + \nabla_{\mathbf{x}_t} \log p(y | \mathbf{x}_t)
\]

The noise predictor \( \epsilon_\theta(\mathbf{x}_t, t) \) is modified to incorporate gradient from classifier \( \nabla_{\mathbf{x}_t} \log p(y | \mathbf{x}_t) \):
\[
\hat{\epsilon}_\theta(\mathbf{x}_t, y, t) = \epsilon_\theta(\mathbf{x}_t, t) - \omega (1 - \alpha_t) \nabla_{\mathbf{x}_t} \log p(y|\mathbf{x}_t)
\]

- \( \omega \geq 1 \): Strength of guidance (Condition Enhancement)
- High \( \omega \): Higher fidelity, lower diversity

### Pros & Cons
- **(+)** Enables conditional generation with explicit label guidance
- **(-)** Requires additional classifier training

---

## Classifier-Free Guidance (CFG)

### Method
Train a single noise prediction network with conditional input \( \epsilon(\mathbf{x}_t, y, t) \) and unconditional input \( \epsilon(\mathbf{x}_t, \phi, t) \) (where \( \phi \) is a null label).

### Condition Enhancement by Extrapolation
\[
\hat{\epsilon}(\mathbf{x}_t, y, t) = (1 + \omega) \epsilon(\mathbf{x}_t, y, t) - \omega \epsilon(\mathbf{x}_t, \phi, t)
\]

Equivalent to:
\[
\epsilon(\mathbf{x}_t, \phi, t) + \lambda (\epsilon(\mathbf{x}_t, y, t) - \epsilon(\mathbf{x}_t, \phi, t)), \quad \lambda = 1 + \omega
\]

### Connection to Classifier Guidance
CFG implicitly amplifies \( p(y|\mathbf{x}_t) \) like classifier guidance but without an explicit classifier.

### Pros & Cons
- **(+)** No need for classifier; works with arbitrary conditions (text, image, audio)
- **(-)** Slower inference due to two forward passes (conditional + unconditional)

### Applications
- Text-to-Image (e.g., Stable Diffusion 3)
- Image-to-Image (e.g., InstructPix2Pix)
- 3D Generation (e.g., SALAD)
- Pose transfer (e.g., InterHandGen)
- Audio-to-Image
- **Negative Prompting**: Manipulate outputs by providing negative descriptors in place of null prompts

---

## Latent Diffusion

### Motivation
High-resolution generation requires excessive GPU resources.

### Solution: Compression via Autoencoder
- Compress \( 512\times512\times3 \rightarrow 64\times64\times4 \) using VAE
- Train diffusion model in latent space

### Architecture
- **Noise Predictor**: U-Net with self-attention
- **Cross-Attention**: Incorporates conditions (e.g., text/image) as key-value pairs

### Tools
- Huggingface Diffusers: https://huggingface.co/docs/diffusers

---

## Evaluation: Fréchet Inception Distance (FID)

### Definition
- Measures distributional similarity between real and generated images
- Based on 2-Wasserstein distance in Inception v3 feature space

### Imperfections
- Sensitive to small distortions (e.g., JPEG compression)
- Assumes Gaussian distribution in latent space

---

## Fine-Tuning-Based Methods

### ControlNet
Converts unconditional diffusion model into conditional with image inputs using few-shot training.

#### Procedure
1. **Freeze** pretrained noise prediction network
2. **Copy** encoder to process conditional image
3. **Combine** via **Zero Convolution**:
   \[ Z(x) = ax + b \] (where \( a, b \) initialized as 0)

- During training, Zero Conv gradually integrates conditional info

#### Advantages
- Requires only ~100k training pairs
- Applicable to image-to-image settings (sketches, poses, depth maps, etc.)

### GLIGEN
Uses **Gated Self-Attention** instead of Zero Conv
- Targeted for weak conditioning like bounding boxes

---

## Personalization via LoRA

### Goal
Adapt pretrained model to generate specific objects (e.g., self portraits)

### Challenge
Naively duplicating layers doubles parameters

### Solution: Low-Rank Adaptation
Approximate weight matrix:
\[ W \approx BA \quad \text{where } A \in \mathbb{R}^{d \times r}, B \in \mathbb{R}^{r \times d}, r \ll d \]

- Reduces parameter count
- Fine-tunes using small dataset

---

## Zero-Shot Adaptation

### SDEdit
- Perturb input image with noise
- Apply reverse diffusion
- Timestep controls realism vs. faithfulness

### RePaint
- Masked inpainting
- Alternating forward + reverse processes
- Fixes background, regenerates foreground

---
