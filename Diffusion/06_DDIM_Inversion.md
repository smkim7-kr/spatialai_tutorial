# DDIM Inversion and Null-Text Inversion (CS492D Lecture 9)

## Recap: Denoising Diffusion Implicit Models (DDIM)

DDIM modifies the traditional DDPM sampling to allow for deterministic sampling:

Given the noise prediction model \( \epsilon_\theta(x_t, t) \), the DDIM transition can be written as:

\[ x_{t-1} = \sqrt{\alpha_{t-1}} x_0 + \sqrt{1 - \alpha_{t-1} - \sigma_t^2} \epsilon_\theta(x_t, t) + \sigma_t z \]

Where:
- \( x_t \): Noisy latent at time \( t \)
- \( x_0 \): Predicted denoised image
- \( \sigma_t \): Controls stochasticity. If \( \sigma_t = 0 \), the process becomes deterministic.

## Deterministic Sampling (\( \sigma_t = 0 \))

- When noise is removed completely (\( \sigma_t = 0 \)), each \( x_{t-1} \) is a deterministic function of \( x_t \) and \( \epsilon_\theta(x_t, t) \).
- The forward mapping \( x_T \rightarrow x_0 \) is fixed.

## DDIM Inversion

**Goal**: Recover \( x_T \) from a given \( x_0 \).

**Challenge**: The reverse of the denoising process is not straightforward.

### Key Idea:

Assuming small time intervals:
- Approximate the forward process as:
  \[
  x_{t+1} - x_t \approx \text{replace } t-1 \text{ with } t+1 \text{ in the deterministic formula for } x_{t-1} - x_t
  \]

- Allows constructing an approximate inversion trajectory from \( x_0 \) to \( x_T \).

### Observation:
- Finer time steps (larger \( T \)) lead to better reconstructions.
- If \( T \) is too small (i.e., time intervals too large), the reconstructed image diverges from the original input.

## Application: Image Editing via DDIM Inversion

### Workflow:
1. **Inversion**: Apply DDIM inversion on the input image using its original prompt (CFG guidance).
2. **Editing**: Apply the denoising process using a new prompt.

### Examples:
- Face \( \rightarrow \) Face with sunglasses
- Dog \( \rightarrow \) Cat
- Portrait \( \rightarrow \) Abstract painting

### CFG Weight Sensitivity:
- **High CFG weight** improves generation but worsens inversion.
- **Low CFG weight** during inversion preserves fidelity but limits editing.

## Null-Text Inversion (Mokady et al., CVPR 2023)

### Motivation:
Achieve accurate inversion while retaining high CFG weight benefits for editing.

### Method:
1. **Low CFG Inversion**:
   - Invert the image with \( \omega = 1 \) to obtain reference latents \( x^*_1, \dots, x^*_T \).

2. **High CFG Inversion with Tuning**:
   - Invert again with \( \omega \gg 1 \) (e.g., 7.5).
   - Tune only the *null text embedding* \( \phi \) such that:
     \[
     \sum_t \| x_t(x_0, c, \phi) - x^*_t \|^2
     \]
     is minimized.

3. **Editing**:
   - Use the tuned \( \phi \) and a new prompt to regenerate images.

### Benefits:
- Allows **zero-shot image editing**.
- Maintains **fidelity to input** during inversion.

### Caveats:
- Null text embedding \( \phi \) must be tuned per image.

### Results:
- Without tuning, high CFG inversion fails to reconstruct input accurately.
- With null-text tuning, inversion closely matches the original.

---

### References:
- Dhariwal and Nichol, *Diffusion Models Beat GANs on Image Synthesis*, NeurIPS 2021
- Mokady et al., *Null-text Inversion for Editing Real Images using Guided Diffusion Models*, CVPR 2023
- Lecture 9, CS492D (KAIST, Fall 2024)
- [Lecture video](https://www.youtube.com/watch?v=l1bYcU6Z7iU)
- [Lecture slides (PDF)](kaist_cs492d_fall_2024_lecture_9.pdf)
