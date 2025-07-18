### Contribution of a Single Node

The problem asks for this sum:

$$
S = \sum_{\text{all subsegments } x} \frac{\text{number of infected nodes in } x}{\text{length of } x}.
$$

A key insight in combinatorics is to change the order of summation. Instead of summing over subsegments, we can sum over each infected node. The formula can be rewritten as:

$$
S = \sum_{\substack{\text{infected nodes } w\\\text{on the path}}}
      \Biggl(\sum_{\substack{\text{subsegments } x\\\text{that contain } w}}
             \frac{1}{\text{length of } x}\Biggr).
$$

---

### 2. Computing Each Node’s Contribution in $O(1)$ with Modular Inverses

$$
\mathrm{Contrib}(i)
= \sum_{L=1}^{i}\sum_{R=i}^{k}\frac{1}{R-L+1}
=\sum_{d=0}^{i-1}\sum_{d'=0}^{k-i}\frac{1}{d+d'+1}.
$$

Using precomputed **modular inverses** instead of floating‐point, the same identity holds:

$$
\sum_{L=1}^{i}\sum_{R=i}^{k}\frac{1}{R-L+1}
\;=\;
SH_{k-1}\;-\;SH_{i-1}\;-\;SH_{k-i}
\pmod{M},
$$

where all operations are modulo $M$ (e.g.\ $10^9+7$) and

$$
H_n = \sum_{t=1}^n \tfrac1t \;=\;\sum_{t=1}^n \text{inv}[t],
\qquad
SH_n = \sum_{t=1}^n H_t,
$$

with $\text{inv}[t]$ the modular inverse of $t \bmod M$.


**Total**

   $$
     S \;=\;\sum_{\text{infected }w}\mathrm{Contrib}(w)\;\pmod{M}.
   $$

This yields an $O(N + I)$ algorithm using purely integer arithmetic and modular inverses.
