Given an array $a$ of size $n$ and need to split the array into $k$ regions such that the summation of every region cost is $\min/\max$.

If $Cost(l..r)$ --- the cost of region $a[l+1...r]$

$Cost(l..r)= (prefF[r] - F[l]) \cdot (prefG[r] - prefG[l])$

Where $prefF[i] = \sum_{j<i}{F[j]}, prefG[i] = \sum_{j<i}{G[j]}$

This problem can be solved using $CHT$ but defining

$W[i] = \sum_{j<i}{F[j]\cdot prefG[j-1]}$

The transition will be

$dp[k][r] = prefF[r] \cdot prefG[r] - W[r] + \min_{\leq l < r}{(-prefF[l]\cdot prefG[r] + W[l] + dp[k-1][l])} $

## CHT intergration:

- Slope $(m_l): -prefF[l]$
  
- Intercept $(c_l): dp[k-1][l] + W[l]$
  
- Variable $(x): prefG[r]$
  
- Constant $(C): prefF[r] \cdot prefG[r] - W[r]$
