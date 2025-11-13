# Continued Fractions for Competitive Programming

This repository contains a small C++ template for working with **continued fractions** in competitive programming.

Typical use-cases:

- Comparing big rational numbers safely.
- Finding a fraction with **minimal denominator** between two given fractions.
- Implementing number-theoretic tricks based on the Euclidean algorithm.

The core idea is that a rational number

$$
x = \frac{p}{q}
$$

can be written as a finite **continued fraction**

$$
x = a_0 + \cfrac{1}{a_1 + \cfrac{1}{a_2 + \dots + \cfrac{1}{a_k}}}
$$

which we store as a vector of integers `[a0, a1, ..., ak]`.  
All operations we need (comparison, “best” approximations, searching between two rationals) can be expressed in terms of these partial quotients.

The implementation is completely integer-based and runs in

$$
O(\log \max(p, q))
$$

time for a single fraction.

---

## Features

The template provides:

- `vector<long long> contfrac(long long p, long long q)`
  - Builds the continued fraction expansion of `p / q` (with `q > 0`).
- `pair<long long,long long> from_contfrac(const vector<long long> &a)`
  - Reconstructs the fraction from its continued fraction (returns `(num, den)`).
- `pair<long long,long long> middle_fraction(long long A, long long B, long long C, long long D)`
  - Given `A/B < C/D`, returns the **lexicographically first** fraction `p/q` with
    `A/B < p/q < C/D`. In particular, `q` is the minimal possible denominator.

You can drop the single file into your CP template and just call these helpers.

---

## Example 1 – AtCoder ABC408 G: `A/B < p/q < C/D`

**Problem:**  
Given positive integers `A, B, C, D` with `A/B < C/D`, find the smallest positive integer `q` such that there exists an integer `p` with

$$
\frac{A}{B} < \frac{p}{q} < \frac{C}{D}.
$$

Up to `2 ⋅ 10^5` test cases and `A,B,C,D ≤ 10^{18}`.

The official editorial solves this using a recursive continued-fraction / Euclidean-algorithm style procedure in

$$
O(\log \max\{A,B,C,D\})
$$

per test case.

### How the continued-fraction view helps

Consider the interval `(A/B, C/D)`. Both endpoints have finite continued-fraction expansions:
A/B = [a0; a1, a2, ..., ak]
C/D = [b0; b1, b2, ..., bm]
We want the first rational lying strictly inside this interval in the Stern–Brocot tree / Farey order, which corresponds to taking a common prefix of these expansions and then adjusting the next partial quotient appropriately.

The editorial’s recursion can be written as:
'''cp
pair<long long,long long> dfs(long long a,long long b,long long c,long long d) {
    long long n = a / b;      // integer part of A/B
    a -= n * b;
    c -= n * d;
    if (c > d) return {n + 1, 1};
    auto [p, q] = dfs(d, c, b, a);
    return {p * n + q, p};
}
'''

# Continued Fractions for Competitive Programming

This repository provides a small **C++ helper** for working with *continued fractions* in competitive programming.

Typical use-cases:

- Comparing big rational numbers safely (without overflow).
- Finding a fraction with **minimal denominator** between two rationals.
- Implementing number-theoretic tricks based on the Euclidean algorithm.

A rational number

$$
x = \frac{p}{q}
$$

can be written as a finite continued fraction

$$
x = a_0 + \cfrac{1}{a_1 + \cfrac{1}{a_2 + \dots + \cfrac{1}{a_k}}}
$$

which we store as a vector of integers `[a0, a1, ..., ak]`.

All the useful operations (comparison, best approximation, searching between two rationals) can be expressed via these partial quotients.  
Everything is done with integers and runs in

$$
O(\log \max(p, q))
$$

time for a single fraction.

---

## API Overview

- `vector<long long> contfrac(long long p, long long q)`
  - Returns the continued fraction expansion of `p / q` (with `q > 0`).
- `pair<long long,long long> from_contfrac(const vector<long long> &a)`
  - Reconstructs `(num, den)` from a continued fraction.
- `pair<long long,long long> middle_fraction(long long A, long long B, long long C, long long D)`
  - Given `A/B < C/D`, returns a fraction `p/q` such that  
    `A/B < p/q < C/D` and `q` is the **minimal possible denominator**.

Drop this file into your CP template and call these helpers directly.

---

## Example – AtCoder ABC408 G

**Task (simplified):**

Given positive integers `A, B, C, D` with

$$
\frac{A}{B} < \frac{C}{D},
$$

find the smallest positive integer `q` such that there exists an integer `p` with

$$
\frac{A}{B} < \frac{p}{q} < \frac{C}{D}.
$$

Constraints: up to `2 · 10^5` test cases, `A,B,C,D ≤ 10^{18}`.

Using continued fractions / Euclidean algorithm, we can construct a fraction `p/q` in that open interval whose denominator `q` is minimal. That is exactly what `middle_fraction(A,B,C,D)` returns.

Minimal usage:

```cpp
int T;
cin >> T;
while (T--) {
    long long A,B,C,D;
    cin >> A >> B >> C >> D;
    auto [p, q] = middle_fraction(A,B,C,D);
    cout << q << '\n';
}
```

---

## Complexity

All operations are Euclidean-algorithm-based:

- `contfrac(p, q)`:  
  $$O(\log \min(p, q))$$
- `middle_fraction(A,B,C,D)`:  
  $$O(\log \max(A,B,C,D))$$

OK for:

- `p, q` up to `10^18`,
- `10^5`–`10^6` queries in total.

---

## Implementation (single header / file)

```cpp
#pragma once
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;

// Build continued fraction expansion of p/q (q > 0)
vector<ll> contfrac(ll p, ll q) {
    vector<ll> a;
    while (q) {
        ll t = p / q;
        a.push_back(t);
        ll r = p - t * q;
        p = q;
        q = r;
    }
    return a;
}

// Reconstruct (num, den) from continued fraction
pair<ll,ll> from_contfrac(const vector<ll> &a) {
    int n = (int)a.size();
    if (n == 0) return {0, 1};

    i128 p_nm2 = 0, p_nm1 = 1;
    i128 q_nm2 = 1, q_nm1 = 0;
    i128 p_n = 0, q_n = 0;

    for (int i = 0; i < n; ++i) {
        p_n = (i128)a[i] * p_nm1 + p_nm2;
        q_n = (i128)a[i] * q_nm1 + q_nm2;
        p_nm2 = p_nm1;
        p_nm1 = p_n;
        q_nm2 = q_nm1;
        q_nm1 = q_n;
    }
    return {(ll)p_n, (ll)q_n};
}

// Strict comparison of a/b and c/d (all ll, avoid overflow via __int128)
int cmp_frac_ll(ll a, ll b, ll c, ll d) {
    i128 x = (i128)a * d;
    i128 y = (i128)c * b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

// Internal recursive helper for middle_fraction
pair<ll,ll> middle_fraction_rec(ll A, ll B, ll C, ll D) {
    // assumes A/B < C/D and all positive
    ll n = A / B;
    A -= n * B;
    C -= n * D;

    if (C > D) {
        // Next partial quotient differs here -> answer is (n+1)/1
        return {n + 1, 1};
    }

    auto p = middle_fraction_rec(D, C, B, A);
    return {p.first * n + p.second, p.first};
}

// Public wrapper: returns p/q with A/B < p/q < C/D and minimal q
pair<ll,ll> middle_fraction(ll A, ll B, ll C, ll D) {
    // You may assert(cmp_frac_ll(A,B,C,D) < 0);
    return middle_fraction_rec(A, B, C, D);
}
```

---

## Minimal `main.cpp` Example

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;

// paste the same implementations here (or #include "continued_fraction.hpp")

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        ll A,B,C,D;
        cin >> A >> B >> C >> D;
        auto [p, q] = middle_fraction(A,B,C,D);
        cout << q << '\n';
    }
}
```

---
