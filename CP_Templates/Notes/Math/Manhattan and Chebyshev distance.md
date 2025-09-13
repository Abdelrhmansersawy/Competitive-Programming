
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

### (a) Manhattan → Chebyshev

**Definition**:

  $$
  d_{Manhattan}(x_1,y_1,x_2,y_2) = |x_1 - x_2| + |y_1 - y_2|
  $$

**Trick**: Rotate 45° using transformations:

  $$
  p = x+y, \quad q = x-y
  $$

**Result**:

  $$
  d_{Chebyshev} = \max\big(|p_1 - p_2|,\; |q_1 - q_2|\big)
  $$

---

### (b) Chebyshev → Manhattan

**Definition**:

**Trick**: Rotate 45° as above.

 **Result**:

  $$
  d_{Manhattan} = \tfrac{1}{2}\Big(|p_1 - p_2| + |q_1 - q_2|\Big)
  $$
