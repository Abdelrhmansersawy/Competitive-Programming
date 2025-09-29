/* 
 * cnt[u]
 * - Number of occurrences of the substring(s) represented by state u.
 * - Set cnt[cur] = 1 in sa_extend() and use propagation() to accumulate counts.
 */

void propagation() {
    // Order states by length (longest first → shortest)
    vector<int> order(sz);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        return st[a].len > st[b].len;
    });

    for (int i = 0; i < sz; i++) {
        int v = order[i];
        if (st[v].link != -1) {
            cnt[st[v].link] += cnt[v]; 
        }
    }
}

// Build suffix link tree and prepare binary lifting table
// - adj: adjacency list of suffix link tree
// - up[k][i]: the 2^k-th ancestor of state i in the suffix link tree
// This allows us to jump quickly along suffix links (binary lifting)
void build_SAM_tree() {
    up[0][0] = 0; // root has no parent
    for (int i = 1; i < sz; ++i) {
        adj[sam[i].link].push_back(i);   // build suffix link tree
        up[0][i] = sam[i].link;          // direct parent (1-step ancestor)
    }

    // Precompute ancestors for binary lifting
    for (int k = 1; k < LOG; ++k) {
        for (int i = 0; i < sz; ++i) {
            up[k][i] = up[k - 1][up[k - 1][i]];
        }
    }
}

// Get the state in the suffix automaton that represents substring s[l..r]
// Idea:
//   - Start from the state of prefix ending at r
//   - Climb suffix links (via binary lifting) until state's length >= substring length
int get_state_substring(int l, int r) {
    int len = r - l + 1;   // substring length
    int u = pos_state[r];  // state representing prefix ending at r

    // climb up using binary lifting until we reach the correct state
    for (int k = LOGN - 1; k >= 0; --k) {
        if (up[k][u] != 0 && sam[up[k][u]].len >= len) {
            u = up[k][u];
        }
    }
    return u; // final state corresponds to s[l..r]
}


int get_first_pos(const string &pat){
    int node = 0;
    for(auto &ch : pat){
        int nxt = st[node].nxt[ch-'a'];
        if(nxt == -1) return -1;
        node = nxt;
    }
    return st[node].first_pos - pat.size() + 2; 
}

array<int,4> get_lcs(const string &t){
    int cur_len = 0;
    int node = 0;
    pair<int,int> bst{0,-1}; // {length, end_index_in_t}
    int best_node = 0;

    for(int i = 0; i < (int)t.size(); ++i){
        int ch = t[i] - 'a';

        while(node != -1 && st[node].nxt[ch] == -1){
            node = st[node].link;
            if(node != -1) cur_len = st[node].len;
        }

        if(node == -1){
            node = 0;
            cur_len = 0;
            continue;
        }

        node = st[node].nxt[ch];
        ++cur_len;

        if(cur_len > bst.first){
            bst = {cur_len, i}; // store best length + end pos in t
            best_node = node;   // remember state in s
        }
    }

    if(bst.first == 0) return {-1,-1,-1,-1}; // no common substring

    int len = bst.first;
    int ed_t = bst.second;
    int st_t = ed_t - len + 1;

    // s: use first_pos of best_node
    int ed_s = st[best_node].first_pos;
    int st_s = ed_s - len + 1;

    return {st_s, ed_s, st_t, ed_t};
}
