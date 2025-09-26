# Math Identities & Distance Tricks (CP Cheatsheet)

---

## 1. Min/Max Identities

*(use to avoid `if` in DP/expressions)*

* **Min with abs**

  $$
  \min(a,b) = \tfrac{a+b - |a-b|}{2}
  $$

* **Max with abs**

  $$
  \max(a,b) = \tfrac{a+b + |a-b|}{2}
  $$

* **Min via max**

  $$
  \min(a,b) = a+b-\max(a,b)
  $$

---

## 2. Manhattan ↔ Chebyshev (2D Rotation)

*(rotation trick: p=x+y, q=x−y)*

* **Manhattan**

  $$
  |x_1-x_2|+|y_1-y_2|=\max(|p_1-p_2|,|q_1-q_2|)
  $$

* **Chebyshev**

  $$
  \max(|x_1-x_2|,|y_1-y_2|)=\tfrac12(|p_1-p_2|+|q_1-q_2|)
  $$

💡 *Hint: Convert Manhattan ↔ Chebyshev by rotating coords.*

---

## 3. Manhattan in Higher Dimensions

*(farthest pair trick, small d ≤ 10)*

For sign pattern $s=(s_1,\dots,s_d)\in\{\pm1\}^d$:

$$
p_s(x)=\sum_{k=1}^d s_k x_k
$$

Then

$$
\|x-y\|_1=\max_{s} |p_s(x)-p_s(y)|
$$

* **Farthest pair:**

  $$
  \max_{s}\bigl(\max_i p_s(x_i)-\min_i p_s(x_i)\bigr)
  $$

* Only need $2^{d-1}$ patterns.

* Complexity: $O(N\cdot d\cdot 2^{d-1})$.

💡 *Hint: project points with sign patterns → max−min gives distance.*

---

## 4. Distances on a Line (1D)

* **Farthest two points:**

  $$
  \max_{i,j} |x_i-x_j| = \max_i x_i - \min_i x_i
  $$

💡 *Hint: Always max−min, don’t overcomplicate.*

* **Special case (3 points):**

  $$
  \max_{i,j} |x_i-x_j| = \tfrac12 \sum_{i<j} |x_i-x_j|
  $$

💡 *Hint: neat identity, rarely needed but elegant.*
