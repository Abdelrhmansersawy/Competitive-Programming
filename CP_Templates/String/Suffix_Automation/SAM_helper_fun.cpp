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

/* 
 * mark_terminals()
 * - Marks all states that correspond to suffixes of the original string.
 * - A terminal node = a state representing a suffix.
 */
void mark_terminals() {
    int p = last;
    while (p != -1) {
        is_terminal[p] = true;
        p = st[p].link;
    }
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
