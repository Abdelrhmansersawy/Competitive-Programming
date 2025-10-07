/* Simulate giving left vertex `u_left` `extra` additional copies.
 * Include Kuhn aglorthim template
 * Call this AFTER running max_matching().
 * It tests how many additional matches could be formed if `u_left`
 * were allowed to match up to `extra` more times (without changing the real matching).
 * Returns the number of extra matches possible.
 * Time: O(n + m + extra * E) — for small extra (e.g. 2) ≈ O(E).
 */
int extra_matches_if_plugged(int u_left, int extra) {
    vector<int> lmatch = matchL;
    vector<int> rmatch = matchR;
    vector<int> seenR(m, 0);

    function<bool(int)> dfs_local = [&](int u)->bool {
        int left_rep = (u < n ? u : u_left);
        for (int v : g[left_rep]) {
            if (seenR[v]) continue;
            seenR[v] = 1;
            if (rmatch[v] == -1 || dfs_local(rmatch[v])) {
                rmatch[v] = u;
                if (u < n) lmatch[u] = v;
                return true;
            }
        }
        return false;
    };

    int added = 0;
    for (int i = 0; i < extra; ++i) {
        fill(seenR.begin(), seenR.end(), 0);
        int virtual_id = n + i;
        if (dfs_local(virtual_id)) ++added;
        else break;
    }
    return added;
}
