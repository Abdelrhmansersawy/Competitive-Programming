
  $$
  d_{Chebyshev}(x_1,y_1,x_2,y_2) = \max(|x_1 - x_2|,\; |y_1 - y_2|)
  $$


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
