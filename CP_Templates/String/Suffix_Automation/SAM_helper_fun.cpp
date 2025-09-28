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
