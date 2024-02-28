/*
    # Hierholzer’s Algorithm for directed graph
    
    Euler circuit is a path that traverses every edge of a graph, and the path ends on the starting vertex
    Problem: Given a directed Eulerian graph, print an Euler circuit
    
    restrictions:
    A directed graph has an eulerian cycle if following conditions are true
        1. All vertices with nonzero degree belong to a single strongly connected component. 
        2. In degree is equal to the out degree for every vertex.

    Idea:
    Choose any starting vertex v, and follow a trail of edges from that vertex until returning to v. It is not possible to get stuck at any vertex other than v,
    because indegree and outdegree of every vertex must be same, when the trail enters another vertex w there must be an unused edge leaving w.
    The tour formed in this way is a closed tour, but may not cover all the vertices and edges of the initial graph.
    As long as there exists a vertex u that belongs to the current tour, but that has adjacent edges not part of the tour,
    start another trail from u, following unused edges until returning to u, and join the tour formed in this way to the previous tour.


    Time complexity : O(V+E)
    Space complexity : O(V+E)
*/


// Don't forget to check if the graph has an euler circuite or not.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
#define all(v) v.begin() , v.end()
#ifndef ONLINE_JUDGE 
#define debug(x) cerr << #x << ": " << x << '\n';
#else
#define debug(x)
#endif
const int N = 1e5 + 9;
vector<int> adj[N];
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif
    int n , m; cin >> n >> m;
    for(int i = 0; i < m; ++i){
        int u , v; cin >> u >> v;
        --u; --v;
        adj[u].emplace_back(v);
    }
    vector<int> edge_count(n);
    for (int i= 0; i< n; i++) edge_count[i] = adj[i].size();
    stack<int> cur_path;  // Maintain a stack to keep vertices
    vector<int> circuit;  // vector to store final circuit
    cur_path.push(0);  // start from any vertex
    int cur_v = 0; // curent vertex
    while (!cur_path.empty()){
        if (edge_count[cur_v]){  // If there's remaining edge
            cur_path.push(cur_v); // Push the vertex
            int next_v = adj[cur_v].back(); // Find the next vertex using an edge
            edge_count[cur_v]--; // and remove that edge
            adj[cur_v].pop_back();
            cur_v = next_v; // Move to next vertex
        }
 
        else{ // back-track to find remaining circuit
            circuit.push_back(cur_v);
            // Back-tracking
            cur_v = cur_path.top();
            cur_path.pop();
        }
    }
 
    // we've got the circuit, now print it in reverse
    reverse(circuit.begin() , circuit.end());
    for(auto &i : circuit) cout << i + 1 << ' ';
}
