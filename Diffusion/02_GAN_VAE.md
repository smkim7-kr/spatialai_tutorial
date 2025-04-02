# CS492D: Introduction to Generative Models — GAN & VAE

## Main Objective

> From data, how can we create new data following the trained data distribution?

**Flow:**  
**Data** → **Train a model** → **Probability distribution** → **Sample from it** → **Generate new data**

---

## Sampling from a Data Distribution

### Inverse Transform Sampling

- Use the **cumulative distribution function (CDF)**:
  - Sample `u ~ Uniform(0, 1)`
  - Find `x_i` such that `P_{i-1} ≤ u ≤ P_i`
- CDF: `F(x)` maps `x → probability`
- Inverse CDF: `u → x`, so we need to know the inverse of the CDF
- **Limitation**: Only applicable when inverse CDF is computable.

### Rejection Sampling

Used when inverse CDF is **not** computable:

1. Choose a proposal distribution `q(x)` such that `q(x) ≥ p(x)` for all `x`
2. Sample `x ~ q(x)` and `h ~ Uniform(0, q(x))`
3. Accept `x` if `h ≤ p(x)`, otherwise reject

### Reparameterization Trick

Used for **normal distributions**:

- Transform standard normal samples:  
  `z = μ + Σ^(1/2) * ε`, where `ε ~ N(0, I)`
- Enables gradient-based optimization with stochastic variables

---

## Generative Adversarial Networks (GAN)

### Intuition

- Neural networks are powerful at **understanding** images (e.g., classification)
- But they are vulnerable to **adversarial examples**

### GAN Setup

- **Discriminator (D)**: Classifies inputs as **real or fake**
- **Generator (G)**: Generates synthetic images from latent variables to **fool the discriminator**

### Architecture

- Generator: `G(z)` maps latent vector `z` (sampled from unit Gaussian) to synthetic image
- Discriminator: `D(x)` outputs probability of input `x` being a real image

### Minimax Loss

\[
\min_G \max_D \mathbb{E}_{x \sim p_{	ext{data}}(x)}[\log D(x)] + \mathbb{E}_{z \sim p(z)}[\log(1 - D(G(z)))]
\]

### Training Challenges

1. **Discriminator overpowers generator** early on
2. **Mode collapse**: Generator outputs limited modes of data

### GAN Advances

- **StyleGAN2**
- **Diffusion models** (alternative with better convergence, stability)

---

## Variational Autoencoder (VAE)

### Motivation

- Avoid **minimax optimization** (which is unstable and hard to train)
- Represent mapping from latent distribution to data distribution using **conditional probability** `p(x|z)`

### VAE Assumptions

- Prior: `p(z) = N(0, I)`
- Likelihood: `p(x|z) = N(D(z), σ²I)` where `D(z)` is a neural decoder

---

### Objective: Maximize Marginal Likelihood `p(x)`

\[
p(x) = \int p(x|z) p(z) \, dz
\]

But this is **intractable**, so we approximate using **variational inference**.

---

## Evidence Lower Bound (ELBO)

We approximate the intractable posterior `p(z|x)` with a variational distribution `q(z|x)`.

Let:

- `q(z|x)` be a learned distribution (e.g., `N(z; μ(x), σ²(x)I)`)

Using **Jensen's inequality**:

\[
\log p(x) \geq \mathbb{E}_{z \sim q(z|x)} \left[\log rac{p(x, z)}{q(z|x)} 
ight]
\]

---

### ELBO Decomposition

\[
	ext{ELBO} = \mathbb{E}_{z \sim q(z|x)} [\log p(x|z)] - D_{KL}(q(z|x) \| p(z))
\]

- **Reconstruction term**: Maximize likelihood of data given latent variable
- **KL divergence term**: Encourage `q(z|x)` to match the prior `p(z)`

---

### Summary

- **GAN**: Uses adversarial training to match data distribution
- **VAE**: Uses variational inference and maximizes ELBO
- Both aim to generate **realistic data** from latent space samples

---

