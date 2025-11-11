# Range-hash (Add-on-Range, Set Version)

## Problem

You have an array `a[]` and need to:

* **Add x** to all elements in a range `[L, R]`.
* **Get a hash** that represents the *set* of elements in `[L, R]` (order doesn’t matter), even after many updates.
  Goal: support both operations efficiently.

---

## Idea

Represent each value as `base^val (mod MOD)`.
Set hash of a range = `Σ base^{a[i]}`.
Adding `+x` to all elements ⇒
`base^{a[i]+x} = base^{a[i]} * base^x`,
so the **whole range sum** is multiplied by `base^x`.

Thus:

* **Range add (+x)** → multiply range by `base^x`.
* **Range hash** = sum of `base^{val}` → same for any permutation of elements.

---

## Data Structure

Use a **lazy segment tree** that supports:

* Range **sum** (to get the set hash).
* Range **multiply** (to apply `base^x` to all elements).

Each node stores:

* `sum`: Σ base^{a[i]} (mod MOD)
* `mul`: lazy multiplier (`base^x`, initially 1)

Operations:

* `apply(node, mul)`: multiply node’s sum and lazy tag by `mul`.
* `update(L, R, mul)`: multiply the whole range by `mul`.
* `query(L, R)`: return sum hash.

---

## Collision Handling

* Pick random `base` and large prime `MOD` (e.g., 1e9+7, 1e9+9).
* Use **double hashing** for safety.

---

## Complexity

| Operation      | Time     |
| -------------- | -------- |
| Range Add (+x) | O(log n) |
| Range Query    | O(log n) |
| Build          | O(n)     |

---

## Notes

* Precompute or use fast `powmod(base, x)` for updates.
* Handle negative `x` using modular inverse of `base`.
* Order doesn’t affect hash → works as **set hash**.
* Double hash if comparing ranges for equality.
