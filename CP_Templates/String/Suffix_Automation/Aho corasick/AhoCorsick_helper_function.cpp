// Returns index of longest word ending at each position, or -1 if none
// Time: O(|word|) where |word| is text length
vector<int> find(string &word) {
    int node = 0;
    vector<int> res;
    for(auto &c : word) {
        node = v[node].nxt[c - first];
        res.push_back(v[node].end);
    }
    return res;
}

// Finds all patterns starting at each position (shortest first)
// Time: O(N+M) where N = text length, M = number of matches
// Can find up to N√N matches if no duplicate patterns
vector<vector<int>> findAll(vector<string> &pat, string word) {
    vector<int> r = find(word);
    vector<vector<int>> res(word.size());
    for(int i = 0; i < word.size(); ++i) {
        int ind = r[i];
        while(ind != -1) {
            res[i - pat[ind].size() + 1].push_back(ind);
            ind = backup[ind];
        }
    }
    return res;
}

// Counts number of ways to construct the string using given patterns
// Each pattern can be used multiple times
// Uses Aho-Corasick + DP
// Time: O(N+M) where N = text length, M = number of matches
// Can find up to N√N matches if no duplicate patterns
ll count(vector<string> &pat, string &word) {
    vector<int> r = find(word); // r[i] = ID of pattern ending at i-th position, or -1
    vector<ll> dp(word.size() + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= word.size(); ++i) {
        int ind = r[i - 1];
        while (ind != -1) {
            dp[i] += dp[i - pat[ind].size()];
            if (dp[i] >= mod) dp[i] -= mod;
            ind = backup[ind]; // follow suffix chain of patterns
        }
    }
    return dp[word.size()];
}

// Propagates values up the suffix links in decreasing depth order
// Useful for transferring match info (e.g., pattern IDs, frequencies, counts, etc.)
// Nodes are processed deepest to shallowest to ensure correctness
// Time: O(total number of nodes)
void propagate() {
    int N = v.size() - 1; // exclude dummy node
    int ind[N];
    iota(ind, ind + N, 0); // fill with 0..N-1
    sort(ind, ind + N, [&](int x, int y) {
        return v[x].lvl > v[y].lvl; // sort by depth descending
    });
    for (int i = 0; i < N; ++i) {
        int x = ind[i];
        int link = v[x].suflink;
        // TODO: propagate information from node x to its suffix link
        // Example: v[link].value += v[x].value;
    }
}

// Builds the transition matrix of the automaton
// m[i][j] = 1 if there's a valid transition from node i to node j 
// using some character, and node j does NOT lead to any forbidden string
// (i.e., it does not match or lie on a suffix that matches a restricted pattern)
vector<vector<int>> getMat() {
    int N = v.size() - 1; // exclude dummy node
    vector<vector<int>> m(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < alpha; ++j) {
            int nxt = v[i].nxt[j];
            if (nxt >= N) continue;            // skip dummy or out-of-bound node
            if (v[nxt].nmatches) continue;     // skip terminal (forbidden) states
            m[i][nxt]++;
        }
    }
    return m;
}
