/**
 * Stoer-Wagner: Global Min Cut (Weighted, Undirected)
 * the Global Minimum Cut of a weighted undirected graph:
 * find a partition of a graph's vertices into two non-empty sets such that
 * the sum of the weights of the edges connecting the two sets is minimized
 * Complexity: O(V^3)
 * Returns: {cost, vector<nodes_in_one_partition>}
 */
using vi = vector<int>
pair<int, vi> globalMinCut(vector<vi> mat) {
    pair<int, vi> best = {INT_MAX, {}};
    int n = mat.size();
    vector<vi> co(n);
    for (int i = 0; i < n; i++) co[i] = {i};

    for (int ph = 1; ph < n; ph++) {
        vi w = mat[0];
        size_t s = 0, t = 0;
        for (int it = 0; it < n - ph; it++) { // O(V^2) => O(E log V) with prio. queue
            w[t] = INT_MIN;
            s = t, t = max_element(all(w)) - w.begin();
            for (int i = 0; i < n; i++) w[i] += mat[t][i];
        }
        best = min(best, {w[t] - mat[t][t], co[t]});
        
        // Merge nodes s and t
        co[s].insert(co[s].end(), all(co[t]));
        for (int i = 0; i < n; i++) mat[s][i] += mat[t][i];
        for (int i = 0; i < n; i++) mat[i][s] = mat[s][i];
        mat[0][t] = INT_MIN; // Mark t as removed
    }
    return best;
}
