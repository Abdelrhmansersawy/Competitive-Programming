// problem link: https://codeforces.com/gym/102412/problem/H
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
#define all(v) v.begin() , v.end()

struct SCC_Solver {
    int n; 
    vector<vector<int>> g, gr;
    vector<int> comp, order;
    vector<char> vis;

    SCC_Solver(int n) : n(n), g(n), gr(n), comp(n, -1), vis(n, 0) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        gr[v].push_back(u);
    }

    void dfs1(int u) {
        vis[u] = 1;
        for (int v : g[u]) if (!vis[v]) dfs1(v);
        order.push_back(u);
    }

    void dfs2(int u, int c) {
        comp[u] = c;
        for (int v : gr[u]) if (comp[v] == -1) dfs2(v, c);
    }

    bool solve(int vars, vector<bool>& assign) {
        order.clear();
        fill(vis.begin(), vis.end(), 0);
        fill(comp.begin(), comp.end(), -1);

        for (int i = 0; i < n; ++i) if (!vis[i]) dfs1(i);
        reverse(order.begin(), order.end());
        int c = 0;
        for (int u : order) if (comp[u] == -1) dfs2(u, c++);
        assign.assign(vars, 0);
        for (int i = 0; i < vars; ++i) {
            if (comp[2*i] == comp[2*i+1]) return false;
            assign[i] = comp[2*i] < comp[2*i+1];
        }
        return true;
    }
};


// 2-Satisfiability Solver
struct TwoSAT {
    int n, vars;
    vector<bool> ans;
    vector<pair<int,int>> E; // implication edges (u->v)

    TwoSAT(int n): n(n), vars(n), ans(n) {}

    int add_var(){ return vars++; } // create fresh helper variable

    // internal: add implication by node indices
    void add_edge_node(int u,int v){ E.emplace_back(u,v); }

    // Adds the constraint: (variable i is f) OR (variable j is g)
    // (0,1) , (1,0) , (1,1)
    void add_or(int i, bool f, int j, bool g) {
        add_edge_node(2*i + !f, 2*j + g);
        add_edge_node(2*j + !g, 2*i + f);
    }
    // Adds the constraint: (variable i is f) XOR (variable j is g)
    // (0,1) , (1,0)   
    void add_xor(int i, bool f, int j, bool g) { add_or(i, f, j, g); add_or(i, !f, j, !g); }

    // Adds the constraint: IF (variable i is f) THEN (variable j is g)
    // (1,1) , (0,1) , (0,0)
    void add_imply(int i, bool f, int j, bool g) { add_or(i, !f, j, g); } // kept yours

    // Adds the constraint: (variable i is f) IFF (variable j is g)
    // (0,0) , (1,1)
    void add_iff(int i, bool f, int j, bool g) { add_imply(i, f, j, g); add_imply(j, f, i, g); }
    
    // Forces variable 'i' to be true
    void force_true(int i) { add_or(i, true, i, true); }
    
    // Forces variable 'i' to be false
    void force_false(int i) { add_or(i, false, i, false); }

    // Adds the constraint: at most one of (i, j) can be true
    void add_at_most_one(int i, int j) { add_or(i, false, j, false); }


    // Checks if a solution exists. O(N + M) where N is variables, M is clauses.
    // If it exists, it computes a valid assignment.
    bool solve() {
        SCC_Solver S(2 * vars);
        for (auto &e : E) S.add_edge(e.first, e.second);
        return S.solve(n, ans);
    }
    // Returns one possible solution (a valid assignment) if solve() was true.
    vector<bool> get_ans() { return ans; }
};

const int N = 2000;
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif

    int n; cin >> n;
    int m = 2*n;
    vector<pair<int,int>> edges(m);
    for(int i = 0; i < m; ++i){
        int u,v; cin >> u >> v;
        --u; --v;
        edges[i] = {u,v};
    }

    auto build_reach = [&](int mex){
        vector<bitset<N>> reach(n);
        vector<int> deg(n) , rev_adj[n];
        for(int i = 0; i < m; ++i){
            auto &[u,v] = edges[i];
            rev_adj[v].emplace_back(u);
            deg[u]++;
        }
        queue<int> q;
        for(int i = 0; i < n; ++i){
            if(deg[i] == 0) q.push(i);
            reach[i][i] = true;
        }
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(auto &v : rev_adj[u]){
                reach[v] |= reach[u];
                if(--deg[v] == 0) q.push(v);
            }
        }
        return reach;
    };

    auto can = [&](int mex){
        if(mex == 0) return true;

        auto reach = build_reach(mex);
        auto same_path = [&](int i , int j){
            auto &[a,b] = edges[i];
            auto &[x,y] = edges[j];
            return reach[b][x] || reach[y][a];
        };

        int k = 2 * mex;
        TwoSAT sat(k);
        for(int i = 0; i < k; i += 2){
            sat.add_or(i,true,i+1,true);
        }
        for(int i = 0; i < k; ++i){
            for(int j = i+1; j < k; ++j){
                // if edges[i] , edges[j] not belong to the same path
                if(!same_path(i,j)){
                    sat.add_or(i, false, j, false);
                }
            }
        }
        return sat.solve();
    };

    int lo = 0 , hi = n+1;
    while(lo < hi){
        int mid = lo + (hi - lo + 1) / 2;
        if(can(mid)) lo = mid;
        else hi = mid - 1;
    }

    cout << lo << '\n';
    return 0;
}
