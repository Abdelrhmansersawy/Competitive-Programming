Here’s the same README rewritten in a plain, natural style with no emojis:

---

# Floating Point Comparison Guide

When working with floating-point numbers (such as `double`), direct comparisons like `a == b` are unreliable because of small rounding errors.
To handle this correctly, we use a small tolerance value called **EPS** (epsilon).

---

## Definition

```cpp
const double EPS = 1e-9;
```

---

## 1. Comparing Two Doubles

Instead of:

```cpp
if (a == b)
```

write:

```cpp
if (fabs(a - b) < EPS)
```

This checks whether the numbers are close enough to be considered equal.

---

## 2. Comparing with `<`, `<=`, `>`, `>=`

To check if `a < b` (with tolerance):

```cpp
if (a < b - EPS)
```

To check if `a <= b`:

```cpp
if (a < b + EPS)
```

Similarly:

```cpp
if (a > b + EPS)   // for a > b
if (a > b - EPS)   // for a >= b
```

---

## Notes

* The value of `EPS` (for example, `1e-9` or `1e-12`) depends on the required precision of the problem.
* Use `fabs()` from `<cmath>` to compute the absolute value of floating-point numbers.
* Always use this technique in geometry, distance comparison, and binary search problems involving floating-point values.

---
