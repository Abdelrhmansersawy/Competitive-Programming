## 1. Min/Max Identities

**Min using absolute value**

  $$
  \min(a,b) = \frac{a+b - |a-b|}{2}
  $$

**Min using max**

  $$
  \min(a,b) = a + b - \max(a,b)
  $$

 **Max using absolute value**

  $$
  \max(a,b) = \frac{a+b + |a-b|}{2}
  $$

---

## 2. Manhattan ↔ Chebyshev Distance

## 45° transform (Manhattan ↔ Chebyshev)

Define $p=x+y,\;q=x-y$. Then

$$
|x_1-x_2|+|y_1-y_2|=\max(|p_1-p_2|,|q_1-q_2|)
$$

and conversely (up to factor)

$$
\max(|x_1-x_2|,|y_1-y_2|)=\tfrac12\big(|p_1-p_2|+|q_1-q_2|\big)
$$

when $p,q$ are the rotated coordinates of the same $(x,y)$.

---

### High dimensions — simple

**Idea:**
  Pick a sign pattern $s=(s_1,\dots,s_d)$ with each $s_k\in\{+1,-1\}$.
  For a point $x=(x_1,\dots,x_d)$ define

  $$
  p_s(x)=\sum_{k=1}^d s_k x_k.
  $$

  Then the Manhattan distance between any two points satisfies

  $$
  \|x-y\|_1=\max_{s\in\{\pm1\}^d}\,|p_s(x)-p_s(y)|.
  $$

**Algorithm (for farthest distance):**
  For each sign pattern $s$, compute all values $p_s(x_i)$.
  The largest possible distance is

  $$
  \text{answer}=\max_{s\in\{\pm1\}^d}\Bigl(\max_i p_s(x_i)-\min_i p_s(x_i)\Bigr).
  $$

  (Only need half the patterns: $2^{d-1}$.)

**Complexity:**

  $$
  O\bigl(N\cdot d\cdot 2^{d-1}\bigr).
  $$


