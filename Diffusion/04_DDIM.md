# Denoising Diffusion Models: Score-Based Methods and DDIM

## Direct Sampling vs. Generative Models

**Question**: If we already have a massive dataset of images, why not just sample directly from them?

**Advantages of Generative Models**:
1. **Efficiency & Scalability**: Compress data distribution into neural network weights; no need to store all raw data.
2. **Novelty & Diversity / Privacy**: Generate plausible new samples that aren't exact copies of the training data, offering privacy benefits.
3. **Adaptability**: Enables conditional generation (e.g., weather conditions), making them more versatile.

> Note: In some applications like global matching in SLAM, direct retrieval might be more suitable.

---

## Score-Based Models

### Score Function
- Defined as the gradient of the log-density: \( \nabla_x \log p(x) \)
- In diffusion models:
  - Score of forward noise: \( \nabla_{x_t} \log q(x_t | x_0) \)
  - This is analytically tractable because \( q(x_t | x_0) \) is Gaussian.

**Relation to \( \epsilon_t \):**
- \( \nabla_{x_t} \log q(x_t | x_0) = -\epsilon_t / \sqrt{1 - \alpha_t} \)
- The noise predictor \( \epsilon_t \) approximates the score up to a scaling factor.

### Tweedie's Formula
- A way to estimate the mean of a Gaussian distribution from noisy samples.
- Allows relating the score function to \( \epsilon_t \).

### Langevin Dynamics
- **Goal**: Sample from a target distribution using only its score.
- **Algorithm**:
  1. Initialize \( x \sim \mathcal{N}(0, I) \)
  2. For \( T \) steps: \( x \leftarrow x + \eta \cdot \nabla_x \log p(x) + \sqrt{2\eta} \cdot z \)
- As \( \eta \to 0 \), \( T \to \infty \): \( x \to p(x) \)

```
Langevin Dynamics Sampling
Initial noise x ~ N(0, I)
    ↓
x = x + η ∇ log p(x) + noise
    ↓
Repeat T steps → Converge to p(x)
```

### Score Matching
- Learn a neural network \( s_\theta(x) \approx \nabla_x \log p(x) \)
- Loss: \( \mathbb{E}_x \left[ \| s_\theta(x) - \nabla_x \log p(x) \|^2 \] \)
- Problem: Cannot directly compute \( \nabla_x \log p(x) \)

### Noise-Conditional Score-Based Models
- Use perturbed data: \( q(x_t | x_0) \)
- Let \( q(x) = q(x_0) \) and define it as a mixture of Gaussians.
- Objective becomes equivalent to DDPM's denoising loss (up to scale).

```
Annealed Langevin Dynamics
Start with large σ → explore low-density regions
Gradually decrease σ → refine samples in high-density regions
```

#### Choosing \( \sigma \) in Perturbations
- **Small \( \sigma \)**:
  - Closer to true data
  - Poor score estimates in low-density regions
- **Large \( \sigma \)**:
  - Better generalization
  - Harder to learn due to large corruption
- **Solution**: Annealed Langevin Dynamics
  - Start with large \( \sigma \), reduce gradually
  - Encourages accurate score prediction across both low and high-density regions

**Final Objective**:
\[ \mathbb{E}[\| s_\theta(x_t, t) - \nabla_{x_t} \log q(x_t | x_0) \|^2] \approx \mathbb{E}[\| s_\theta(x_t, t) + \epsilon_t / \sqrt{1 - \alpha_t} \|^2] \]

**Connection to SDEs**:
- Continuous-time version of annealed Langevin = solving SDEs
- DDPM is a discretization of this process

```
Forward Process (DDPM)
x₀ → x₁ → x₂ → ... → x_T (add noise step-by-step)

Reverse Process (DDPM)
x_T → x_{T-1} → ... → x₀ (denoise step-by-step)
```

---

## Summary: Diffusion Models Comparison
| Model | Pros | Cons |
|-------|------|------|
| GAN   | High quality, fast sampling | Mode collapse |
| VAE   | Fast, mode coverage         | Poor quality |
| DDPM  | High quality, mode coverage | Slow sampling |

---

## DDIM: Denoising Diffusion Implicit Models

**Goal**: Accelerate DDPM's slow sampling without retraining.

### Key Differences
- DDIM uses a **non-Markovian** forward process:
\[ q(x_{1:T} | x_0) = q(x_T | x_0) \prod_{t=2}^T q(x_{t-1} | x_t, x_0) \]
- Reverse process is defined directly as:
\[ q(x_{t-1} | x_t, x_0) = \mathcal{N}(w_0 x_0 + w_t x_t + b, \sigma_t^2) \]
- Parameters \( w_0, w_t, b \) chosen to match DDPM marginals.

```
DDIM Reverse Process (Deterministic if σ=0):
x_T → x_{T-1} → ... → x₀
      ↑ use noise predictor and mean function
```

### Deterministic Sampling
- If \( \sigma = 0 \), reverse process becomes deterministic:
\[ x_{t-1} = \mu(x_t, \epsilon_t) \]

### DDIM vs. DDPM Summary
| Aspect | DDPM | DDIM |
|--------|------|------|
| Forward Process | Markov | Non-Markov |
| Reverse Process | Stochastic | Can be deterministic |
| Objective | ELBO (same) | ELBO (same) |
| Noise Predictor | \( \epsilon_t \) | \( \epsilon_t \) |
| Retraining | Needed for other models | Not needed (reuse DDPM predictor) |

**Steps to Sample with DDIM**:
1. Predict \( x_0 \) from \( x_t \) and \( \epsilon_t \)
2. Compute DDIM mean
3. Sample \( z \sim \mathcal{N}(0, I) \)
4. Compute \( x_{t-1} = \text{mean} + \sigma_t \cdot z \)

### Tuning \( \sigma \): Control Stochasticity
- \( \sigma = 0 \): Deterministic, fast
- \( \sigma = \sqrt{1 - \alpha_{t-1}} \): Most stochastic
- No need to retrain noise predictor

**Speed-Quality Tradeoff**:
- Use fewer time steps (e.g., 10 instead of 1000)
- Deterministic DDIM maintains quality better than stochastic DDPM
- FID degradation is small for DDIM even with aggressive step reduction

```
Trade-off Visualization
↑ Quality
│          DDPM (full steps)
│          DDIM (full steps)
│      DDIM (reduced steps)
│
└────────────→ Speed ↑
```

---


