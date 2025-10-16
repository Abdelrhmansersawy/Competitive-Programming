#include <bits/stdc++.h>
using namespace std;

// Solves Strongly Connected Components using Tarjan's algorithm
struct SCC_Solver {
    int n;
    vector<vector<int>> g;
    SCC_Solver(int n) : n(n), g(n) {}
    void add_edge(int u, int v) { g[u].push_back(v); }
    pair<int, vector<int>> scc_ids() {
        vector<int> tin(n, -1), low(n), id(n), stk;
        int timer = 0, scc_cnt = 0;
        stk.reserve(n);
        function<void(int)> dfs = [&](int v) {
            low[v] = tin[v] = timer++;
            stk.push_back(v);
            for (int to : g[v]) {
                if (tin[to] == -1) {
                    dfs(to);
                    low[v] = min(low[v], low[to]);
                } else if (tin[to] < n) { // Node is on stack
                    low[v] = min(low[v], tin[to]);
                }
            }
            if (low[v] == tin[v]) {
                while (true) {
                    int u = stk.back(); stk.pop_back();
                    tin[u] = n; // Mark as processed
                    id[u] = scc_cnt;
                    if (u == v) break;
                }
                scc_cnt++;
            }
        };
        for (int i = 0; i < n; i++) if (tin[i] == -1) dfs(i);
        for (auto& x : id) x = scc_cnt - 1 - x;
        return {scc_cnt, id};
    }
    vector<vector<int>> sccs() {
        auto p = scc_ids();
        int scc_cnt = p.first; vector<int> id = p.second;
        vector<vector<int>> res(scc_cnt);
        for (int i = 0; i < n; i++) res[id[i]].push_back(i);
        return res;
    }
};

// 2-Satisfiability Solver
struct TwoSAT {
    int n; vector<bool> ans; SCC_Solver g;
    TwoSAT(int n) : n(n), ans(n), g(2 * n) {}
    // Adds the constraint: (variable i is f) OR (variable j is g)
    void add_or(int i, bool f, int j, bool g) {
        g.add_edge(2 * i + !f, 2 * j + g);
        g.add_edge(2 * j + !g, 2 * i + f);
    }
    // Adds the constraint: (variable i is f) XOR (variable j is g)
    void add_xor(int i, bool f, int j, bool g) { add_or(i, f, j, g); add_or(i, !f, j, !g); }
    // Adds the constraint: IF (variable i is f) THEN (variable j is g)
    void add_imply(int i, bool f, int j, bool g) { add_or(i, !f, j, g); }
    // Adds the constraint: (variable i is f) IFF (variable j is g)
    void add_iff(int i, bool f, int j, bool g) { add_imply(i, f, j, g); add_imply(j, f, i, g); }
    // Forces variable 'i' to be true
    void force_true(int i) { add_or(i, true, i, true); }
    // Forces variable 'i' to be false
    void force_false(int i) { add_or(i, false, i, false); }

    // Checks if a solution exists. O(N + M) where N is variables, M is clauses.
    // If it exists, it computes a valid assignment.
    bool solve() {
        auto p = g.scc_ids(); vector<int> id = p.second;
        for (int i = 0; i < n; i++) {
            if (id[2 * i] == id[2 * i + 1]) return false;
            ans[i] = id[2 * i] < id[2 * i + 1];
        }
        return true;
    }
    // Returns one possible solution (a valid assignment) if solve() was true.
    vector<bool> get_ans() { return ans; }
};
