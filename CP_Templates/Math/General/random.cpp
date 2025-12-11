#include <bits/stdc++.h>
using namespace std;

// Your RNG setup
mt19937_64 random_seed(time(0)); // Changed to 64 for safety with long long
long long rnd(long long l, long long r){
    uniform_int_distribution<long long> dist(l, r);
    return dist(random_seed);
}

int main() {
    int N = 10; // Example size
    int M = 15; // Example edges
    
    // ==========================================
    // 1. Generate a Tree (N nodes, N-1 edges)
    // Method: Connect node i to a random node in [1, i-1]
    // ==========================================
    vector<pair<int,int>> tree_edges;
    for(int i = 2; i <= N; ++i) {
        int u = rnd(1, i - 1); // Pick a parent from previous nodes
        int v = i;
        tree_edges.push_back({u, v}); 
        // permute labels later if you don't want 1 to always be root conceptually
    }

    // ==========================================
    // 2. Generate a Connected Graph (N nodes, M edges)
    // Method: Create a spanning tree first, then fill remaining edges
    // ==========================================
    set<pair<int,int>> graph_edges;
    
    // A. Ensure Connectivity (Spanning Tree)
    for(int i = 2; i <= N; ++i) {
        int p = rnd(1, i - 1);
        graph_edges.insert({p, i});
    }

    // B. Add random remaining edges
    while(graph_edges.size() < M) {
        int u = rnd(1, N);
        int v = rnd(1, N);
        if(u != v) {
            if(u > v) swap(u, v); // standardizing for set uniqueness
            graph_edges.insert({u, v});
        }
    }

    // ==========================================
    // 3. Shuffle Permutation (Array 1 to N)
    // Method: Fisher-Yates shuffle using your rnd
    // ==========================================
    vector<int> p(N);
    iota(p.begin(), p.end(), 1); // Fill 1, 2, ..., N

    // Option A: Standard library (Preferred)
    shuffle(p.begin(), p.end(), random_seed);

    // Option B: Manual using your rnd function
    for(int i = N - 1; i > 0; --i) {
        int j = rnd(0, i);
        swap(p[i], p[j]);
    }

    return 0;
}
