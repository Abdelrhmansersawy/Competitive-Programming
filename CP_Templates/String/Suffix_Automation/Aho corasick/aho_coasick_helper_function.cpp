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
