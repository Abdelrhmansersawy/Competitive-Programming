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

## 6.6 Half-Division Game

**Game Rules:**

* Start with **n piles**, each with some number of stones.
* Players take turns; **Alice starts**.
* On each turn, the player picks any pile and reduces it using this rule:

```cpp
int move(int x) {
    if (x % 2 == 0) return x / 2;
    while (x % 2 != 0) x /= 2;
    return x / 2;
}
```

* A pile becomes invalid if its size is `1`, since it can't be halved further.
* A player **loses** if they cannot make a valid move on any pile.

## 6.7 Misère Nim

**Game Rules:**

* Standard Nim setup: several piles of stones, and on each turn, a player removes any number of stones from a single pile.
* **Twist:** The player **who removes the last stone *loses***.
* This version is called **Misère Nim**.

---

### C++ Implementation

```cpp
/**
    In misere nim, the player who makes the last move **loses**.
    Special Case: When all piles have size 1, the XOR rule fails.
    - If all piles are size 1:
        - Even number of piles → First player wins
        - Odd number of piles → Second player wins
    - Otherwise, play like normal nim.
**/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);

    int tc; cin >> tc;
    while(tc--){
        int n; cin >> n;
        int xor_sum = 0, ones = 0;
        for(int i = 0; i < n; ++i){
            int x; cin >> x;
            ones += (x == 1);
            xor_sum ^= x;
        }
        if(ones == n) cout << (n & 1 ? "Second\n" : "First\n");
        else cout << (xor_sum ? "First\n" : "Second\n");
    }
}
```
### 6.8 Matrix Pile Game (Diagonal XOR Variant)

* **Game Rules:**
  You are given an `r × c` matrix where each cell contains a pile of stones.
  A move consists of selecting any pile and transferring stones to either the **right** or **downward** adjacent cell.
  The player who makes the **last move wins**.

* **Grundy Formula:**
  Only consider cells `(i, j)` such that
  $(i + j) \bmod 2 \ne (r + c) \bmod 2$
  Then take the XOR of all such cell values:
  $\text{Result} = a_{i_1,j_1} \oplus a_{i_2,j_2} \oplus \cdots$

* **Explanation:**
  The key idea is that due to directional move constraints, only **half the matrix** affects the outcome.
  This partition is based on parity: reachable positions alternate per turn, and only those with opposite parity to `(r + c)` are considered.
  The game reduces to computing the XOR over these diagonally offset cells, similar to classical Nim.
