# Expected Squared Palindromic Substrings (Algorithm)

This document describes the $O(N^2)$ algorithm used to calculate the expected value of the square of the number of palindromic substrings, $\mathbb{E}[f^2]$.

## The Formula

Let $f = \sum x_i$ be the number of palindromic substrings. We want to find:

$$\mathbb{E}[f^2] = \mathbb{E}\left[ \left( \sum_{i} x_i \right) \left( \sum_{j} x_j \right) \right] = \sum_{i, j} \mathbb{E}[x_i \cdot x_j]$$

Directly summing this is difficult. Instead, we use a **Correction Method** based on independence assumptions.

### 1. The Naive "Independence" Assumption
If we assume **all** pairs of substrings $(i, j)$ are independent, the expectation becomes the square of the sum of individual probabilities:

$$\text{Naive Ans} = \left( \sum_{\text{all } S} P(S) \right)^2$$

In the code, this is calculated as `good * good`.
* **Problem:** This assumption is valid for non-concentric substrings but **incorrect** for concentric substrings (which are dependent).

### 2. The Correction
We must remove the incorrect contributions from concentric pairs and add the correct values.

#### Step A: Remove Incorrect (Independent) Term
For every center $C$, the naive formula incorrectly added the square of the sum of probabilities for that center:

$$\text{Bad} = \sum_{\text{centers } C} \left( \sum_{r \in C} P(r) \right)^2$$

This represents the contribution of concentric pairs if they *were* independent. We subtract this.

#### Step B: Add Correct (Dependent) Term
For every center $C$, the correct probability for a pair of radii $r_1, r_2$ is determined by the longer string: $P(r_1 \cap r_2) = P(\max(r_1, r_2))$.

$$\text{Same} = \sum_{\text{centers } C} \left( \sum_{r_1, r_2 \in C} P(\max(r_1, r_2)) \right)$$

Using the property that each radius $r$ is the maximum in $(2r - 1)$ pairs:

$$\text{Same} = \sum_{\text{centers } C} \sum_{r \in C} P(r) \times (2r - 1)$$

---

## Final Algorithm

The final answer is computed as:

$$\mathbb{E}[f^2] = \underbrace{(\text{Good})^2}_{\text{All Independent}} - \underbrace{\text{Bad}}_{\text{Remove Concentric Errors}} + \underbrace{\text{Same}}_{\text{Add Correct Concentric}}$$

### Variable Mapping
| Variable | Formula Term | Description |
| :--- | :--- | :--- |
| `good` | $\sum P(S)$ | Linear sum of probabilities for all substrings. |
| `bad` | $\sum_C (\sum P(S_C))^2$ | The error term introduced by squaring `good`. |
| `same` | $\sum_C \sum P(\max(S_1, S_2))$ | The true probability sum for concentric groups. |

### Complexity
* **Time:** $O(N^2)$ — We iterate every center and every radius once.
* **Space:** $O(1)$ — Only a few accumulators are needed.
