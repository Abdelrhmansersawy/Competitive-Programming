const ll INF = (ll)2e18; // must match the INF used in Hungarian implementation

/* Hungarian algorithm:
   Solves the minimum-cost assignment between nL left nodes and nR right nodes.
   Each left node must be matched to at most one right node, and vice-versa,
   choosing matches so that the total cost is minimized.
   If nL != nR, the algorithm pads with dummy nodes to allow a full assignment.
   Returns: {minimum total cost, list of (left,right) matched pairs}.
   Complexity: O(N^3), N = max(nL, nR).
*/
struct Hungarian {
    int nL, nR, N;
    vector<vector<ll>> a;

    Hungarian(int n, int m)
        : nL(n), nR(m), N(max(n, m)), a(N + 1, vector<ll>(N + 1, INF)) {
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                if (i > n || j > m) a[i][j] = 0;
    }

    void add_edge(int u, int v, ll c) {
        a[u][v] = min(a[u][v], c);
    }

    pair<ll, vector<pair<int, int>>> solve() {
        vector<ll> u(N + 1, 0), v(N + 1, 0);
        vector<int> p(N + 1, 0), way(N + 1, 0);

        for (int i = 1; i <= N; i++) {
            vector<ll> minv(N + 1, INF);
            vector<char> used(N + 1, 0);
            p[0] = i;
            int j0 = 0;

            do {
                used[j0] = 1;
                int i0 = p[j0];
                ll delta = INF;
                int j1 = 0;

                for (int j = 1; j <= N; j++) if (!used[j]) {
                    ll cur = a[i0][j] - u[i0] - v[j];
                    if (cur < minv[j]) { minv[j] = cur; way[j] = j0; }
                    if (minv[j] < delta) { delta = minv[j]; j1 = j; }
                }

                for (int j = 0; j <= N; j++) {
                    if (used[j]) { u[p[j]] += delta; v[j] -= delta; }
                    else minv[j] -= delta;
                }

                j0 = j1;
            } while (p[j0] != 0);

            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }

        vector<pair<int, int>> ans;
        ll tot = 0;
        for (int j = 1; j <= N; j++) {
            int i = p[j];
            if (i >= 1 && i <= nL && j >= 1 && j <= nR && a[i][j] < INF / 2) {
                ans.emplace_back(i, j);
                tot += a[i][j];
            }
        }
        return {tot, ans};
    }
};
