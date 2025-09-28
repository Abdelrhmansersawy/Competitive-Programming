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
