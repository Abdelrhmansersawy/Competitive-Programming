# ICPC Cheat‑Sheet — Fusion & Colon Principles (very short)

**Fusion Principle**

* If two adjacent vertices `u,v` lie on the same cycle (≥2 distinct paths between them) then **contracting** them preserves the Grundy number **for structural games only**.
* If moves depend on per-vertex state (weights, tokens, colors, costs) verify fusion preserves move-equivalence before using it.

**Colon Principle (trees)**

* For the standard "cut-a-subtree / play-inside-subtree" game on a rooted tree:

```
G(u) = ⊕_{v child of u} ( G(v) + 1 )
G(leaf) = 0
```

**Quick proof idea:** each child contributes `G(v)+1` (cut or play inside); mex/bitwise argument yields the xor.

**Fast C++ snippet (root at 0)**

```cpp
int dfs(int u,int p,const vector<vector<int>>& adj){
    int g=0;
    for(int v: adj[u]) if(v!=p) g ^= (dfs(v,u,adj) + 1);
    return g;
}
// call dfs(root,-1,adj)
```

**Usage tips**

* Simplify cycles by fusion (when valid), then run DFS from root computing `G(u)`.
* For weighted variants, state the exact weight→contribution rule before applying.

*End — concise for contest use.*

**Vertex-cut → Edge-cut (rooted trees)**

```cpp
int dfs(int u,int p,const vector<vector<int>>& adj){
    int g=0;
    for(int v: adj[u]) if(v!=p) g ^= dfs(v,u,adj);
    return (g + 1);
}
```

*Use this edge-cut style DFS when treating vertex-cuts as edge-cuts in rooted trees.*

**Weighted tree rule**

```
G(u) = ⊕_{v child of u} (
    w(u,v) == 1   → G(v) + 1,
    w(u,v)  > 1 && odd → G(v) ^ 1,
    w(u,v)  > 1 && even → G(v)
)
```

**C++ snippet**

```cpp
long long dfs(int u,int p){
    long long x=0;
    for(auto [v,w]: adj[u]) if(v!=p){
        long long child = sg(v,u);
        if(w==1) x ^= (child + 1);      // w = 1
        else if((w & 1LL) == 0) x ^= child; // w > 1 even
        else x ^= (child ^ 1LL);        // w > 1 odd
    }
    return x;
}
```

*Handles edge weights according to parity rule; use in weighted tree Grundy computations.**



Got it! Here's a clean way to add your `S(G)` note to your ICPC cheat-sheet README, keeping the formatting consistent with the rest of your notes:

------

## Subgraph / Move Set Grundy (S(G))

For a game with move set `S(G)` from graph `G`:

```
F_t(G) = mex( { F_{t-1}(G) } ∪ { F_t(g') : g' in S(G) } ),   t>1
F_1(G) = mex( { 0 } ∪ { F_1(g') : g' in S(G) } )
```

- `S(G)` = set of all reachable subgraphs (or moves) from `G`.
- `F_t(G)` = Grundy number at turn `t`.
- `mex(...)` = minimum excluded non-negative integer.
