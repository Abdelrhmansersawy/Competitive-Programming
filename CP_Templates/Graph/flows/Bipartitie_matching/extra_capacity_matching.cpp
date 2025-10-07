/* Simulate giving left vertex `u_left` `extra` additional copies.
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
    int cur_id = 0;

    function<bool(int)> dfs_local = [&](int u)->bool {
        for (int v : g[u]) {
            if (seenR[v] == cur_id) continue;
            seenR[v] = cur_id;
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
        cur_id++;
        if (dfs_local(u_left)) ++added;
        else break;
    }
    return added;
}
