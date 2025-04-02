---
title: "Generative Models: VAE and DDPM"
author: "CS492D Lecture 3 (KAIST, Fall 2024)"
date: "Lecture Notes"
---

## Fundamentals of Generative Models

- **Core idea**: Rather than sampling directly from the complex data distribution \( p(x) \), we sample from a simpler latent distribution \( p(z) \) and map it to the data distribution through a decoder (neural network).

---

## Variational Autoencoder (VAE)

### Motivation
- GANs use a discriminator; VAEs instead introduce an encoder to approximate the posterior \( q(z|x) \).
- Based on **Bayes' rule**:
  \[
  p(z|x) = \frac{p(x|z) p(z)}{p(x)}
  \]
- Since \( p(x) \) is intractable, we approximate it via the **Evidence Lower Bound (ELBO)**.

### Objective
Maximize:
\[
p(x) = \int p(x|z)p(z)dz \quad \Rightarrow \quad \text{maximize ELBO}
\]

ELBO decomposition:
\[
\log p(x) \geq \mathbb{E}_{q(z|x)}[\log p(x|z)] - D_{\text{KL}}[q(z|x)\|p(z)]
\]

### Architecture
- **Encoder**: \( q(z|x) = \mathcal{N}(z; \mu(x), \sigma^2(x)) \)
- **Decoder**: \( p(x|z) = \mathcal{N}(x; D(z), \sigma^2) \)
- Use **Monte Carlo sampling** + **reparameterization trick**: \( z = \mu(x) + \sigma(x)\cdot\epsilon \), where \( \epsilon \sim \mathcal{N}(0, I) \)

### Training Steps
1. Feed \( x \) to encoder, get \( \mu(x), \sigma(x) \)
2. Sample \( z \sim q(z|x) \) using reparameterization
3. Decode \( z \rightarrow \hat{x} \)
4. Optimize negative ELBO

### Recap
- **Why ELBO?** Lower bound on \( \log p(x) \)
- **Loss =** Reconstruction loss + KL divergence
- **Expectation =** Approximate via Monte Carlo
- **Reparameterization =** Enables backpropagation through sampling

### Generation
1. Sample \( z \sim p(z) = \mathcal{N}(0, I) \)
2. Decode \( z \rightarrow x \)

### Limitations
- Gaussian \( q(z|x) \) may not capture true posterior \( p(z|x) \)
- ELBO is a lower bound; becomes tight when \( q = p \)
- What if \( p(z|x) \) is non-Gaussian? => Need better approximations

### Hierarchical VAE
- Sequence of latent variables \( x_0 \rightarrow x_1 \rightarrow \cdots \rightarrow x_T \)
- Markov property:
\[
p(x_0, \dots, x_T) = p(x_T) p(x_{T-1}|x_T) \dots p(x_0|x_1)
\]
- Posterior:
\[
q(x_{1:T}|x_0) = q(x_1|x_0) \dots q(x_T|x_{T-1})
\]
- ELBO can be computed similarly

---

## Denoising Diffusion Probabilistic Models (DDPM)

### Key Assumptions
- Markovian forward and reverse process
- Latent space = data space (no dimension reduction)
- **Forward process** is *predefined*, not learned

### Forward Process
\[
q(x_t|x_{t-1}) = \mathcal{N}(x_t; \sqrt{1-\beta_t}x_{t-1}, \beta_t I)
\]
- Noise schedule \( \beta_t \in (0,1) \), increasing over time
- Define \( \alpha_t = 1 - \beta_t \)
- Compose multiple steps:
\[
q(x_t|x_0) = \mathcal{N}(\sqrt{\bar{\alpha}_t}x_0, (1-\bar{\alpha}_t)I)
\]

### Reverse Process
- Learnable conditional distributions:
\[
p_\theta(x_{t-1}|x_t) = \mathcal{N}(\mu_\theta(x_t, t), \Sigma_t)
\]
- Goal: approximate true reverse \( q(x_{t-1}|x_t, x_0) \)
- From Bayes rule, \( q(x_{t-1}|x_t, x_0) = \mathcal{N}(\mu(x_t, x_0), \Sigma_t) \)
- Use noise term \( \epsilon_t \) s.t.
\[
x_t = \sqrt{\bar{\alpha}_t}x_0 + \sqrt{1 - \bar{\alpha}_t}\epsilon_t
\]

### Training Objective
- Minimize negative ELBO, decomposed into:
  1. **Reconstruction term**: often negligible
  2. **Prior matching term**: converges to 0 when \( T \rightarrow \infty \)
  3. **Denoising matching term**: primary objective

#### Denoising Matching Term
\[
\mathbb{E}_{t, x_0, \epsilon_t} \left[ \| \epsilon_t - \epsilon_\theta(x_t, t) \|^2 \right]
\]

### Three Prediction Objectives (equivalent in form)
1. Predict \( \mu(x_t, t) \)
2. Predict \( x_0 \) from \( x_t, t \)
3. Predict \( \epsilon_t \) (standard, easier to train)

### Training Steps
1. Sample \( x_0 \sim \mathcal{D} \) (e.g., real image)
2. Sample timestep \( t \sim \mathcal{U}(1, T) \)
3. Sample \( \epsilon_t \sim \mathcal{N}(0, I) \)
4. Compute:
\[
x_t = \sqrt{\bar{\alpha}_t}x_0 + \sqrt{1 - \bar{\alpha}_t}\epsilon_t
\]
5. Minimize:
\[
\| \epsilon_t - \epsilon_\theta(x_t, t) \|^2
\]

### Generation (Reverse Process)
1. Sample \( x_T \sim \mathcal{N}(0, I) \)
2. For \( t = T, \dots, 1 \):
   - Predict \( \epsilon_\theta(x_t, t) \)
   - Compute:
     \[
x_0 = \frac{1}{\sqrt{\bar{\alpha}_t}} (x_t - \sqrt{1 - \bar{\alpha}_t} \cdot \epsilon_\theta(x_t, t))
\]
   - Compute \( \mu(x_t, \epsilon_\theta) \), then sample \( x_{t-1} \)

---

## Summary

| Concept                  | VAE                                   | DDPM                               |
|--------------------------|----------------------------------------|-------------------------------------|
| Inference type           | Variational inference                 | Score matching (denoising loss)     |
| Latent space             | Lower-dimensional                     | Same as data space                 |
| Training loss            | ELBO (Reconstruction + KL)            | Denoising L2 loss                   |
| Sampling path            | One-shot decoding                     | Sequential denoising                |
| Generation speed         | Fast                                  | Slow (many steps)                   |
| Posterior approximation | Gaussian \( q(z|x) \)                 | Predefined forward + learned reverse|
| Reparameterization trick | Used                                  | Used (in forward + reverse)         |

---
