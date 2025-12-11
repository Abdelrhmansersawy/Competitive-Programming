/*
 -------------------------------------------------------------------------------------
 ALGORITHM: Dinic's Max Flow & LR Flow (Circulation with Demands)
 -------------------------------------------------------------------------------------
 
 STRUCT 1: Dinic
 - Purpose: Standard Max Flow algorithm.
 - Complexity: O(V^2 * E), but often O(E * sqrt(V)) for unit capacity networks.
 - Usage: 
    1. Dinic D(nodes);
    2. D.add_edge(u, v, capacity, [id]); // id is optional tracking
    3. D.max_flow(source, sink);
 
 STRUCT 2: LR_Flow
 - Purpose: Max/Min Flow with Edge Lower (L) and Upper (R) bounds.
 - Technique: Transforms into circulation problem with Super Source/Sink.
 - Complexity: Runs Dinic internally.
 - Usage:
    1. LR_Flow lr(nodes);
    2. lr.add_edge(u, v, L, R, [id]);
    3. lr.max_flow(s, t) OR lr.min_flow(s, t);
    4. Returns -1 if no feasible flow exists.
 
 CONSTRAINTS & LIMITS:
 - Nodes (N): Up to ~5,000 - 10,000 usually safe (O(V^2 E) worst case).
 - Edges (M): Up to ~100,000.
 - Capacity: Use 'long long' for capacities to avoid overflow.
 - INF: 1LL << 61 (Safe for long long additions).
 -------------------------------------------------------------------------------------
*/

const long long inf = 1LL << 61;
struct Dinic {
  struct edge {
    int to, rev;
    long long flow, w;
    int id;
  };
  int n, s, t, mxid;
  vector<int> d, flow_through;
  vector<int> done;
  vector<vector<edge>> g;
  Dinic() {}
  Dinic(int _n) {
    n = _n + 10;
    mxid = 0;
    g.resize(n);
  }
  void add_edge(int u, int v, long long w, int id = -1) {
    edge a = {v, (int)g[v].size(), 0, w, id};
    edge b = {u, (int)g[u].size(), 0, 0, -1};//for bidirectional edges cap(b) = w
    g[u].emplace_back(a);
    g[v].emplace_back(b);
    mxid = max(mxid, id);
  }
  bool bfs() {
    d.assign(n, -1);
    d[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto &e : g[u]) {
        int v = e.to;
        if (d[v] == -1 && e.flow < e.w) d[v] = d[u] + 1, q.push(v);
      }
    }
    return d[t] != -1;
  }
  long long dfs(int u, long long flow) {
    if (u == t) return flow;
    for (int &i = done[u]; i < (int)g[u].size(); i++) {
      edge &e = g[u][i];
      if (e.w <= e.flow) continue;
      int v = e.to;
      if (d[v] == d[u] + 1) {
        long long nw = dfs(v, min(flow, e.w - e.flow));
        if (nw > 0) {
          e.flow += nw;
          g[v][e.rev].flow -= nw;
          return nw;
        }
      }
    }
    return 0;
  }
  long long max_flow(int _s, int _t) {
    s = _s;
    t = _t;
    long long flow = 0;
    while (bfs()) {
      done.assign(n, 0);
      while (long long nw = dfs(s, inf)) flow += nw;
    }
    flow_through.assign(mxid + 10, 0);
    for(int i = 0; i < n; i++) for(auto e : g[i]) if(e.id >= 0) flow_through[e.id] = e.flow;
    return flow;
  }
};
//flow_through[i] = extra flow beyond 'low' sent through edge i
struct LR_Flow {
  Dinic F;
  int n, s, t;
  struct edge {
    int u, v, l, r, id;
  };
  vector<edge> edges;
  LR_Flow() {}
  LR_Flow(int _n) {
    n = _n + 10;
    s = n - 2, t = n - 1;;
    edges.clear();
  }
  void add_edge(int u, int v, int l, int r, int id = -1) {
    assert(0 <= l && l <= r);
    edges.push_back({u, v, l, r, id});
  }
  bool feasible(int _s = -1, int _t = -1, int L = -1, int R = -1) {
    if (L != -1) edges.push_back({_t, _s, L, R, -1});
    F = Dinic(n);
    long long target = 0;
    for (auto e : edges) {
      int u = e.u, v = e.v, l = e.l, r = e.r, id = e.id;
      if (l != 0) {
        F.add_edge(s, v, l);
        F.add_edge(u, t, l);
        target += l;
      }
      F.add_edge(u, v, r - l, id);
    }
    auto ans = F.max_flow(s, t);
    if (L != -1) edges.pop_back();
    if (ans < target) return 0; //not feasible
    return 1;
  }
  int max_flow(int _s, int _t) { //-1 means flow is not feasible
    int mx = 1e5 + 9;
    if (!feasible(_s, _t, 0, mx)) return -1;
    return F.max_flow(_s, _t);
  }
  int min_flow(int _s, int _t) { //-1 means flow is not feasible
   int mx = 2e9; // increase it it you need
   int ans = -1, l = 0, r = mx;
    while (l <= r) {
      int mid = l + r >> 1;
      if (feasible(_s, _t, 0, mid)) ans = mid, r = mid - 1;
      else l = mid + 1;
    }
    return ans;
  }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    // 1. Initialize LR_Flow with number of nodes
    int n = 4;
    int source = 1;
    int sink = 4;
    LR_Flow lr(n);

    // 2. Add edges: u, v, l, r, id
    // We store 'l' (lower bound) separately to calculate total flow later
    // because the struct only tracks the "extra" flow above L.
    struct EdgeInfo { int u, v, l, r; };
    vector<EdgeInfo> original_edges;
    
    auto add = [&](int u, int v, int l, int r, int id) {
        lr.add_edge(u, v, l, r, id);
        original_edges.push_back({u, v, l, r});
    };

    // Constructing the graph
    add(1, 2, 2, 10, 0); // Edge 0
    add(1, 3, 0, 10, 1); // Edge 1
    add(2, 3, 1, 5,  2); // Edge 2
    add(2, 4, 2, 10, 3); // Edge 3
    add(3, 4, 0, 10, 4); // Edge 4

    // 3. Calculate Max Flow
    // Returns -1 if no feasible flow exists (i.e., constraints contradict)
    int total_flow = lr.max_flow(source, sink);

    if (total_flow == -1) {
        cout << "Impossible to satisfy constraints!" << endl;
    } else {
        cout << "Feasible Max Flow: " << total_flow << endl;
        
        cout << "Flow on each edge:" << endl;
        // 4. Retrieve flow for each edge
        // The struct stores 'flow_through[id]' which is flow ABOVE the lower bound.
        // Total Flow = LowerBound + flow_through[id]
        for (int i = 0; i < original_edges.size(); i++) {
            long long extra_flow = lr.F.flow_through[i];
            long long actual_flow = original_edges[i].l + extra_flow;
            
            cout << "Edge " << original_edges[i].u << " -> " << original_edges[i].v 
                 << " [" << original_edges[i].l << ", " << original_edges[i].r << "]"
                 << " | Used: " << actual_flow << endl;
        }
    }

    return 0;
}
