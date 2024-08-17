struct SparseTable {
    vector<ll> A;
    vector<int> log;
    vector<vector<pair<ll, int>>> spt;
 
    void init(vector<ll> &a) {
        int n = a.size();
        A = a;
        log.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) {
            log[i] = 1 + log[i / 2];
        }
        int k = log[n] + 1;
        spt = vector<vector<pair<ll, int>>>(k, vector<pair<ll, int>>(n));
        for (int i = 0; i < n; i++) {
            spt[0][i] = { A[i], i };
        }
        for (int j = 1; 1 << j <= n; j++) {
            for (int i = 0; i + (1 << j) - 1 < n; i++) {
                spt[j][i] = merge(spt[j - 1][i], spt[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
 
    pair<ll, int> merge(pair<ll, int> &x, pair<ll, int> &y) {
        // choose x or y
    }
 
    pair<ll, int> query(int i, int j) {
        int len = j - i + 1;
        int k = log[len];
        return merge(spt[k][i], spt[k][j - (1 << k) + 1]);
    }
};
