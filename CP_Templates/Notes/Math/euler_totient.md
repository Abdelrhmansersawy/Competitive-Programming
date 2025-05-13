##  Properties of Euler’s Totient Function $\phi(n)$

### 1. **Prime Number Case**

If $p$ is a **prime**, then:
$$
\phi(p) = p - 1
$$Because every number from $1$ to $p-1$ is **coprime to $p$**.

---
### 2. **Prime Powers**
If $p$ is a prime and $k \geq 1$, then:
$$
\phi(p^k) = p^k - p^{k-1}
$$
Explanation: In $1$ to $p^k$, every $p$-th number is divisible by $p$, and there are $p^{k-1}$ such numbers. So subtract those.

---
### 3. **Multiplicativity (Coprime Numbers)**

If $a$ and $b$ are **coprime** (Multiplicative function), then:
$$
\phi(ab) = \phi(a) \cdot \phi(b)
$$
This follows from the **Chinese Remainder Theorem** — there's a 1-to-1 mapping between residues modulo $ab$ and pairs of residues modulo $a$ and $b$.

---
### 4. **Non-coprime Multiplication Formula**

If $\gcd(a, b) = d$, then:

$$
\phi(ab) = \phi(a) \cdot \phi(b) \cdot \frac{d}{\phi(d)}
$$

This generalizes the previous rule for when $a$ and $b$ are **not coprime**.

### 5. Divisor sum property $\displaystyle \sum_{d \mid n} \phi(d) = n$

Let $n \in \mathbb{Z}^+$. We want to prove:

$$
\sum_{d \mid n} \phi(d) = n
$$

**Partition the integers $\{1, 2, \dots, n\}$**

For each $k \leq n$, define $d = \gcd(k, n)$. Then $d \mid n$, and every $k \in [1, n]$ belongs to a unique set:

$$
A_d = \{k \leq n \mid \gcd(k, n) = d\}
$$

These sets $A_d$ form a **disjoint partition** of $\{1, 2, \dots, n\}$, so:

$$
\sum_{d \mid n} |A_d| = n
$$

**Count $|A_d|$**

Let $d \mid n$, so $n = d \cdot m$. Any $k \in A_d$ can be written as:

$$
k = d \cdot t \quad \text{with} \quad 1 \leq t \leq m, \; \gcd(t, m) = 1
$$

So the number of such $k$'s is:

$$
|A_d| = \phi(m) = \phi\left(\frac{n}{d}\right)
$$

**Substitute and change variables**

$$
\sum_{d \mid n} |A_d| = \sum_{d \mid n} \phi\left(\frac{n}{d}\right)
$$

Let $m = \frac{n}{d} \Rightarrow d = \frac{n}{m}$, then $m \mid n$. So:

$$
\sum_{d \mid n} \phi\left(\frac{n}{d}\right) = \sum_{m \mid n} \phi(m)
$$

Thus:

$$
\sum_{d \mid n} \phi(d) = n
$$

---

## General Formula Using Prime Factorization

To compute $\phi(n)$ for **any positive integer** $n$, write $n$ as its prime factorization:

$$
n = p_1^{a_1} \cdot p_2^{a_2} \cdots p_k^{a_k}
$$

Then use:

$$
\phi(n) = n \cdot \left(1 - \frac{1}{p_1}\right) \cdot \left(1 - \frac{1}{p_2}\right) \cdots \left(1 - \frac{1}{p_k}\right)
$$

This works because of the multiplicative property and the prime power formula.

---

## Implementation
Here is an implementation using factorization in $\sqrt(n)$
```cpp
int phi(int n) {
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}
```

Finding the totient from 1 to   n<math xmlns="http://www.w3.org/1998/Math/MathML"><mi>n</mi></math>$n$  using the divisor sum property
```cpp
void phi_1_to_n(int n) {
    vector<int> phi(n + 1);
    phi[0] = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
        phi[i] = i - 1;

    for (int i = 2; i <= n; i++)
        for (int j = 2 * i; j <= n; j += i)
              phi[j] -= phi[i];
}
```

---
## Application

### 1. Count how many integers $k \leq n$ satisfy $\gcd(k, n) = d$

Let $d \mid n$, then $n = d \cdot m$. Any number $k \leq n$ with $\gcd(k, n) = d$ can be written as $k = d \cdot t$, where $1 \leq t \leq m$ and $\gcd(t, m) = 1$.

So the number of such $k$'s is equal to the number of $t \leq m$ such that $\gcd(t, m) = 1$, which is:

The final answer will be: 
$$
\phi(m) = \phi\left(\frac{n}{d}\right)
$$
---
### 2. Count how many positive integer pairs $(k_1, k_2)$ satisfy $k_1 + k_2 = n$ and $\gcd(k_1, k_2) = 1$

Since $k_1 + k_2 = n$, we can write $k_2 = n - k_1$, and we must have $1 \leq k_1 \leq n - 1$.

Note that:

$$
\gcd(k_1, k_2) = \gcd(k_1, n - k_1) = \gcd(k_1, n)
$$

So the condition $\gcd(k_1, k_2) = 1$ becomes $\gcd(k_1, n) = 1$.

Thus, we are counting the number of integers $k_1 \in [1, n - 1]$ such that $\gcd(k_1, n) = 1$.

The final answer will be:

$$
\phi(n)
$$

---

### 3. 