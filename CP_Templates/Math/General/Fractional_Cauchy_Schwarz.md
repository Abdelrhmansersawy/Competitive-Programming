You are asked to minimize a sum of fractions where the denominators are variables that sum up to a fixed constant.

### **The Formula:**

$$
\text{Minimize } S = \sum_{i=1}^n \frac{A_i}{x_i}
\quad \text{subject to }
\sum x_i = T
$$

### **The Shortcut Solution:**

$$
S_{\min} = \frac{\left(\sum_{i=1}^n \sqrt{A_i}\right)^2}{T}
$$

---

### **Cauchy–Schwarz Inequality (Standard)**

For any real numbers (x_1, \dots, x_n) and (y_1, \dots, y_n):

$$
\left( \sum x_i y_i \right)^2
\le
\left( \sum x_i^2 \right)\left( \sum y_i^2 \right)
$$

**Equality holds when:**
$$
\frac{x_i}{y_i} = k \quad \text{for all } i
$$

---

### **2. The "Fraction Minimization" Trick (Titu's Lemma)**

This is the specific variant useful for competitive programming. It is derived from Cauchy–Schwarz but is faster to apply.

**Problem:**
Minimize
$$
\sum \frac{a_i^2}{x_i}
$$
subject to
$$
\sum x_i = T,\quad x_i > 0
$$

**Inequality:**
$$
\sum_{i=1}^n \frac{a_i^2}{x_i}
\ge
\frac{\left( \sum_{i=1}^n a_i \right)^2}{\sum_{i=1}^n x_i}
==========================================================

\frac{(\sum a_i)^2}{T}
$$
