// DSU with parity: bipartite check and cycle detection
struct DSU {
    vector<pair<int,int>> p;   // parent, parity to parent
    vector<array<int,2>> sz;   // sz[root][0] = size of parity 0, sz[root][1] = size of parity 1
    vector<int> is_bip, isInCyc;

    // Initialize DSU
    DSU(int n) {
        p.resize(n);
        is_bip.assign(n, 1);
        sz.resize(n);
        isInCyc.assign(n, 0);
        for (int i = 0; i < n; i++) {
            p[i] = {i, 0};
            sz[i] = {1, 0};
        }
    }

    // Find root and parity from node to root
    pair<int,int> find(int x) {
        if (p[x].first != x) {
            auto r = find(p[x].first);
            p[x] = {r.first, p[x].second ^ r.second};
        }
        return p[x];
    }

    // Merge x and y with opposite parity constraint
    bool merge(int x, int y) {
        auto rx = find(x);
        auto ry = find(y);

        if (rx.first == ry.first) {
            isInCyc[rx.first] = 1;
            return is_bip[rx.first] &= (rx.second != ry.second);
        }

        if ((sz[rx.first][0] + sz[rx.first][1]) < (sz[ry.first][0] + sz[ry.first][1])) {
            swap(rx, ry);
        }

        int w = rx.second ^ ry.second ^ 1;
        p[ry.first] = {rx.first, w};
        is_bip[rx.first] &= is_bip[ry.first];
        isInCyc[rx.first] |= isInCyc[ry.first];
        sz[rx.first][0] += sz[ry.first][0 ^ w];
        sz[rx.first][1] += sz[ry.first][1 ^ w];
        return is_bip[rx.first];
    }

    bool isBipartite(int u) {
        return is_bip[find(u).first];
    }

    bool isComponentCyclic(int u) {
        return isInCyc[find(u).first];
    }

    // Get size of u's parity group in its component
    int getSize(int u) {
        auto r = find(u);
        return sz[r.first][r.second];
    }
    
    // Helper to get total size of component
    int getTotalSize(int u) {
        auto r = find(u);
        return sz[r.first][0] + sz[r.first][1];
    }
};
