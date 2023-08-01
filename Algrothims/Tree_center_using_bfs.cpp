const int N = 1e5;
vector<int> pre(N);
auto bfs = [&](int s) {
    int d[N];
    memset(d, -1, sizeof(d));
    queue<int> q;
    q.push(s), d[s] = 0;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int u : adj[v]) if (d[u] == -1) {
            q.push(u), d[u] = d[v] + 1, pre[u] = v;
        }
    }
    return max_element(d, d + n ) - d;
};
int s = bfs(1), t = bfs(s);
vector<int> V;
for (int i = t; ; i = pre[i]) {
    V.push_back(i);
    if (i == s) break;
}
int center = V[V.size() / 2];
