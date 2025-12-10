/*
 * Problem:   Construct a Connected Directed Graph from given Out-Degree (A) and In-Degree (B).
 * Algorithm: Havel–Hakimi Algorithm (Greedy Strategy).
 * Logic:
 * 1. Greedy Construction: Uses a Priority Queue to connect the current node to available 
 * nodes with the highest remaining In-degree (Standard Havel-Hakimi logic).
 * 2. Constraints: Skips self-loops (if the best target is the node itself).
 * 3. Validation: Performs a BFS at the end to ensure the graph is fully connected (1 component).
 */
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 1e5+5;
int a[N], b[N], n;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    
    int sumA = 0, sumB = 0;
    // Read Out-degrees
    for (int i=0; i<n; ++i) {
        cin >> a[i];
        sumA += a[i];
    }
    
    // Read In-degrees
    for (int i=0; i<n; ++i) {
        cin >> b[i];
        sumB += b[i];
    }
    
    // Logic 1: Basic Math Validation
    // The total number of outgoing edges must equal incoming edges.
    if (sumA != sumB) {
        cout << "impossible" << endl;
        return 0;
    }
    
    // Logic 2: Max Degree Constraint
    // In a simple graph, a node cannot connect to more than n-1 other nodes.
    for (int i=0; i<n; ++i) {
        if (a[i] > n-1 or b[i] > n-1) {
            cout << "impossible" << endl;
            return 0;
        }
    }

    // Logic 3: Prepare Greedy Selection
    // Store all nodes that need incoming edges in a Max-Heap.
    priority_queue<pair<int,int>> pq;
    for (int i=0; i<n; ++i) if (b[i] > 0) {
        pq.push({b[i], i});
    }
    
    vector<pair<int,int>> edList;

    // Logic 4: Process each node's Out-degree
    for (int i=0; i<n; ++i) {
        int x = a[i]; // Edges this node needs to send
        if (x == 0) continue;
        
        vector<pair<int,int>> devolver; // Temp storage for nodes we pop
        
        while (x > 0) {
            if (pq.empty()) {
                // We need to send an edge, but no one wants to receive.
                cout << "impossible" << endl;
                return 0;
            }
            
            auto [recibe, nodo] = pq.top(); pq.pop();
            
            // Self-loop check: Don't connect node i to itself.
            if (nodo == i) {
                devolver.push_back({recibe, nodo});
                continue;
            }
            
            // Connect i -> nodo
            x--;
            edList.push_back({i, nodo});
            
            // If 'nodo' still needs more incoming edges later, save it to push back.
            if (recibe-1 > 0) {
                devolver.push_back({recibe-1, nodo});
            }
        }   
        
        // Return valid targets back to the pool for future nodes
        for (auto [u, v] : devolver) {
            pq.push({u, v});
        }
    }

    // Logic 5: Final Sanity Check
    // If PQ is not empty, it means some nodes still expect incoming edges 
    // but all outgoing edges are already used up.
    if (!pq.empty()) {
        cout << "impossible" << endl;
        return 0;
    }

    // Logic 6: Check Connectivity via BFS
    // Construct adjacency list (undirected view) to check if graph is 1 component.
    vector<vector<int>> adj(n);
    for (auto e : edList) {
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
    }

    int comps = 0;
    vector<int> vis(n, -1);
    for (int i=0; i<n; ++i) {
        if (vis[i] > -1) continue;
        vis[i] = ++comps;
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (vis[v] > -1) continue;
                vis[v] = comps;
                q.push(v);
            }
        }
    }

    // If there is more than 1 component, the graph is not connected.
    if (comps > 1) {
        cout << "impossible" << endl;
        return 0;
    }

    cout << n << ' ' << edList.size() << endl;
    for (auto e : edList) {
        cout << e.first+1 << ' ' << e.second+1 << endl;
    }
}
