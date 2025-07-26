## Game Theory Overview


## 1. Terminology

1. **Partisan vs. Impartial**

   * **Partisan games**: Moves depend on the player. *Example:* In Chess, White-only moves vs. Black-only moves.
   * **Impartial games**: Moves depend only on the position, not on the player. *Example:* Nim.

2. **Perfect vs. Imperfect Information**

   * **Perfect information**: All past moves and current state are known to both players. *Example:* Chess.
   * **Imperfect information**: Some elements (e.g., cards) are hidden. *Example:* Poker.

---

## 2. Game Variations

| Category                | Examples                         |
| ----------------------- | -------------------------------- |
| Number of players       | Two-player, Multiplayer          |
| Timing                  | Sequential, Simultaneous         |
| Information             | Perfect, Imperfect               |
| Duration                | Finite, Infinite                 |
| State space             | Discrete, Continuous             |
| Move structure          | Partisan, Impartial              |
| Chance elements         | Deterministic, Randomized        |
| Combinatorial structure | Combinatorial, Non-combinatorial |

---

## 3. Position Properties

1. **Winning position**: There exists at least one move to a **losing position**.
2. **Losing position**: All moves lead to **winning positions**.
3. **Terminal position**: No legal moves (always a **losing position**).

---

## 4. Playing Strategies

1. **Symmetry (Duplication)**: Mirror opponent’s moves to maintain balance.  *Example:* Turning Toads and Frogs or Bowling Pins.
2. **Cancellation**: Neutralize opponent’s threats to preserve a known state.  *Example:* Nim move pairing.

---

## 5. Game Types

* **Search-based games**: Use tree search + pruning (e.g., minimax with alpha–beta).
* **Sprague–Grundy (Impartial)**: Compute nimbers to predict play without full search.

---

## 6. Selected Impartial Games

### 6.1 Simple Subtraction Game

* **Game Rules:** From a pile of size \$x\$, remove \$k\$ stones where \$1 ≤ k ≤ r\$.
* **Grundy Formula:** \$g(x) = x \bmod (r+1)\$.
---

### 6.2 Bounded Subtraction (General Range)

* **Game Rules:** From a pile of size \$x\$, remove any \$k\$ satisfying \$l ≤ k ≤ r\$.
* **Grundy Formula:**
  $g(x) = \left\lfloor \frac{x \bmod (l+r)}{l} \right\rfloor$
* **Explanation:** Periodic behavior with period \$l+r\$ partitioned by step \$l\$.

---

### 6.3 Moore’s Nim-\$K\$

* **Game Rules:** Given \$N\$ piles, in each move remove stones from any **\$K\$ distinct** piles.
* **Key Fact:** Express each pile size in binary; the first player loses iff
  $\sum_{\text{all piles}} x_i \equiv 0 \pmod{K+1}.$
* **Explanation:** Equivalent to a multi-pile Nim with combined parity condition mod \$(K+1)\$.

---

### 6.4 Game of Divisors

* **Game Rules:** Start with integer \$N\$. A move replaces \$N\$ by one of its **proper divisors**.
* **Grundy Formula:** If \$N= p\_1^{a\_1} p\_2^{a\_2}\cdots p\_k^{a\_k}\$,
  $g(N) = a_1 \oplus a_2 \oplus \cdots \oplus a_k.$
* **Explanation:** Equivalent to Nim with piles of sizes \$a\_i\$; reducing exponents corresponds to Nim moves.

---

### 6.5 Fibonacci Nim

* **Game Rules:** Pile of \$N\$ stones. First move: remove \$1 ≤ k < N\$. Thereafter, remove up to twice the opponent’s last take.
* **Losing Positions:** Those whose Zeckendorf representation ends in \$F\_2=1\$ (smallest Fibonacci).
* **Explanation:** Winning strategy maintains opponent’s pile with Zeckendorf sum starting with minimal Fibonacci.
* **How to Solve:**

```text
function zeckendorf(n):
    fibs = generate_fibs_up_to(n)
    res = []
    for i from len(fibs)-1 downto 0:
        if fibs[i] <= n:
            res.append(fibs[i])
            n -= fibs[i]
            i -= 1  // skip next Fibonacci to ensure non-consecutive
    return res

function is_losing(n):
    z = zeckendorf(n)
    return z[-1] == 1

function best_move(n, prev=None):
    max_take = n-1 if prev is None else min(n, 2*prev)
    for k in range(1, max_take+1):
        if is_losing(n - k):
            return k
    return -1  // no winning move
```

* **Idea:** Always leave your opponent with a position whose Zeckendorf sum ends in 1.
