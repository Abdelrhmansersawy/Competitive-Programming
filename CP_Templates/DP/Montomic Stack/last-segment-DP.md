# Monotone-stack DP (Last-segment DP) — README

## Overview

A small, practical optimization for DP recurrences of the form

```
dp[i] = min_{1 ≤ j ≤ i} ( dp[j-1] + cost(j..i) )
```

When `cost(j..i)` depends on a range statistic (e.g. `min(a_j..a_i)`, `max(a_j..a_i)`) that changes only at a few left indices as `j` moves, we can compress many `j` into a small set of *undominated* candidates `(stat, best_dp)` and maintain them in a monotone stack or deque. This makes the DP fast in practice (often `O(n · log(max ai))` or close to linear).

---

## When to use

Use this trick when most of these are true:

* Your recurrence is a *last-segment* DP.
* `cost(j..i)` is determined by a range statistic that is monotone when extending the left border (e.g. `min` or `max`).
* For fixed `i`, many `j` share the same statistic value.
* Among `j` that share the same statistic you only need the minimum `dp[j-1]`.
* There is a clear dominance rule allowing safe removal of dominated candidates.

If yes → good candidate for monotone-stack compression.

---

## Core idea (short)

For each `i` keep a small list `st` of pairs `(stat, best_dp)` where:

* `stat` = a distinct value of the range-statistic (e.g. segment-min) for some `j`.
* `best_dp` = minimum `dp[j-1]` among `j` that produce this `stat`.

To update when moving to a new `a[i]` we:

1. Merge all stored `stat` ≥ `a[i]` into one entry for `a[i]` (update `best_dp`).
2. Remove any stored pair whose `best_dp` is ≥ the new `best_dp` (dominated).
3. Insert `(a[i], best_dp)`.
4. Compute `dp[i]` by scanning `st` and taking `min( ceil(a[i]/stat) + best_dp )` (or your equivalent cost function).

The stack remains small because dominated entries get removed and the number of useful distinct `stat` values is logarithmic in `max ai` in many problems.

---

## Stack invariants (what `st` guarantees)

* `stat` values in `st` are strictly increasing (or strictly decreasing depending on implementation).
* `best_dp` values are strictly increasing (or strictly decreasing) corresponding to the `stat` order.
* For each `stat` present, `best_dp` equals the minimal `dp[j-1]` among all `j` that yield that `stat` for the current `i`.

These invariants ensure correctness: scanning `st` is enough to cover all possible last-segment choices.

---

## Short pseudocode

```text
for i in 0..n-1:
  prv = (i? dp[i-1] : 0)
  while st not empty and st.back().stat >= a[i]:
    prv = min(prv, st.back().best_dp)
    pop st
  while st not empty and st.back().best_dp >= prv:
    pop st
  push (a[i], prv)
  dp[i] = +inf
  for each (stat, best) in st:
    dp[i] = min(dp[i], cost_using(stat, a[i]) + best)
```

Replace `cost_using(stat, a[i])` with your problem-specific cost formula.

---

## Complexity

* Each array element (pair) is pushed and popped at most once → `O(n)` amortized for stack operations.
* The per-`i` scan over `st` costs `O(|st|)`; `|st|` is often small (bounded by `O(log max ai)` in problems like CF partition with `ceil(a_i/min)`), so total time `O(n · C)` where `C` ≪ `n` in practice.

---

## Quick proof sketch (1-line)

For fixed `i`, all `j` whose segment-minimum equals the same `stat` have identical `cost(j..i)` except for `dp[j-1]`. So keep only the smallest `dp[j-1]` for each `stat`. Removing dominated `(stat, best_dp)` pairs cannot eliminate an optimal choice because a dominated pair is strictly worse (larger `best_dp`) while having no advantage in `stat`.

---

## Hints & practical tips

* Always reason about *which* range-statistic the cost depends on. If it’s `min` or `max`, monotone stack is natural.
* Carefully implement the dominance conditions — off-by-one or wrong comparison direction kills correctness.
* Remove duplicates: push each representative exactly once per `i` (no accidental double-pushes).
* If the per-`i` scan is still too slow, try to prove a smaller bound on `|st|` or use additional pruning (binary search on `st` when cost is monotone in `stat`).
* Draw the stack evolution for a small example to understand merges and pops.

---

## Example (very short)

Problem in this conversation: `cost = ceil(a_i / min(a_j..a_i))`. `stat` = `min(a_j..a_i)`. Use the stack idea above. The stack size ≤ `O(log max ai)` by the standard exchange argument in the tutorial.

---

## Gotchas

* Not every last-segment DP is compressible — if `cost` depends on a complicated function of the whole range (not reducible to a small set of `stat` values), this trick won't help.
* Wrong dominance conditions can remove optimal states. Test on small brute-force cases.

---

If you want, I can also produce a 1-page printable cheat-sheet version (even shorter) or a minimal corrected C++ implementation of the code you posted. Which would you like?
