/* --------------------------------------------------------------------------
 * cnt[u]
 * - Number of occurrences of the substring(s) represented by state u.
 * - Set cnt[cur] = 1 in sa_extend() and then call propagation()
 *   to accumulate counts via suffix links.
 * -------------------------------------------------------------------------- */
void propagation() {
    // Order states by length (longest → shortest)
    vector<int> order(sz);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        return st[a].len > st[b].len;
    });

    for (int v : order) {
        if (st[v].link != -1) {
            cnt[st[v].link] += cnt[v];
        }
    }
}

/* --------------------------------------------------------------------------
 * Build adjacency list of the suffix link tree
 * - adj[i] contains all states whose suffix link points to i
 * -------------------------------------------------------------------------- */
void build_adj() {
    for (int i = 0; i < sz; ++i) adj[i].clear();
    for (int i = 1; i < sz; ++i) {
        adj[ st[i].link ].push_back(i);
    }
}

/* --------------------------------------------------------------------------
 * Build binary lifting table for suffix link tree
 * - up[k][i] is the 2^k-th ancestor of node i
 * Purpose:
 *   Allows fast traversal up suffix links (jumping in powers of 2).
 *   This is especially useful for substring → state queries.
 * -------------------------------------------------------------------------- */
void build_up() {
    up[0][0] = 0;
    for (int i = 1; i < sz; ++i) {
        up[i][0] = st[i].link;
    }

    for (int k = 1; k < LOG; ++k) {
        for (int i = 0; i < sz; ++i) {
            up[i][k] = up[ up[i][k - 1] ][k - 1];
        }
    }
}

/* --------------------------------------------------------------------------
 * Get state representing substring s[l..r]
 *
 * Idea:
 *   - Start from the state of prefix ending at r (pos_state[r]).
 *   - Climb suffix links using binary lifting until state's length ≥ substring length.
 *
 * Returns:
 *   State id in SAM that corresponds exactly to substring s[l..r].
 * -------------------------------------------------------------------------- */
int get_state_substring(int l, int r) {
    int len = r - l + 1;
    int u = pos_state[r];
    for (int k = LOG - 1; k >= 0; --k) {
        int anc = up[u][k];
        if (ST[anc].len >= len) u = anc;
    }
    return u;
}

/* --------------------------------------------------------------------------
 * Get first position of a pattern in the text (1-based index)
 *
 * Traverses SAM along the characters of `pat`. 
 * If traversal fails → pattern not found, return -1.
 * Otherwise → return (end_pos - |pat| + 2).
 * -------------------------------------------------------------------------- */
int get_first_pos(const string &pat) {
    int node = 0;
    for (auto &ch : pat) {
        int nxt = st[node].nxt[ch - 'a'];
        if (nxt == -1) return -1;
        node = nxt;
    }
    return st[node].first_pos - pat.size() + 2;
}

/* --------------------------------------------------------------------------
 * Longest Common Substring (LCS) between base string (SAM built on it) and t
 *
 * Returns: {st_s, ed_s, st_t, ed_t}
 *   - [st_s..ed_s] → indices in base string (s)
 *   - [st_t..ed_t] → indices in second string (t)
 *
 * Algorithm:
 *   - Traverse t through SAM of s, extending current match when possible.
 *   - When mismatch occurs, follow suffix links to restore validity.
 *   - Track the best match (longest substring).
 * -------------------------------------------------------------------------- */
array<int,4> get_lcs(const string &t) {
    int cur_len = 0, node = 0;
    pair<int,int> bst{0, -1}; // {length, end_index_in_t}
    int best_node = 0;

    for (int i = 0; i < (int)t.size(); ++i) {
        int ch = t[i] - 'a';

        while (node != -1 && st[node].nxt[ch] == -1) {
            node = st[node].link;
            if (node != -1) cur_len = st[node].len;
        }

        if (node == -1) {
            node = 0;
            cur_len = 0;
            continue;
        }

        node = st[node].nxt[ch];
        ++cur_len;

        if (cur_len > bst.first) {
            bst = {cur_len, i};
            best_node = node;
        }
    }

    if (bst.first == 0) return {-1, -1, -1, -1}; // no common substring

    int len = bst.first;
    int ed_t = bst.second;
    int st_t = ed_t - len + 1;

    int ed_s = st[best_node].first_pos;
    int st_s = ed_s - len + 1;

    return {st_s, ed_s, st_t, ed_t};
}

/* Count distinct rotations of string t in SAM
 * - Rotation = t[k..n-1] + t[0..k-1], for 0 ≤ k < n
 * - Duplicate string (t + t - 1) and traverse SAM
 * - When match length ≥ n, find state for length-n substring
 * - Use vis[] to mark counted states, add cnt[state] once
 */
ll count_rotations(const string &t) {
    int n = (int)t.size();
    if (n == 0) return 0;

    string s = t + t;
    s.pop_back();
    int node = 0, cur_len = 0;
    ll ans = 0;
    vector<int> reset;

    for (int i = 0; i < (int)s.size(); ++i) {
        int ch = s[i] - 'a';
        while (node != -1 && st[node].nxt[ch] == -1) {
            node = st[node].link;
            if (node != -1) cur_len = st[node].len;
            else cur_len = 0;
        }

        if (node == -1) {
            break; // no need to continue;
        }

        node = st[node].nxt[ch];
        ++cur_len;

        if (cur_len < n) continue;

        while (st[node].link != -1 && st[st[node].link].len >= n) {
            node = st[node].link;
        }

        if (!vis[node]) {
            ans += cnt[node];
            vis[node] = true;
            reset.emplace_back(node);
        }
    }

    for (int x : reset) vis[x] = false;
    return ans;
}
