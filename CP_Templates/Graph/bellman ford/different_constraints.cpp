// This module solves systems of difference constraints using the Bellman-Ford algorithm.
//
// A difference constraint has the form: x_v - x_u >= w
// This is modeled as a graph edge from u to v with weight w,
// and a solution can be found by computing the longest paths from a source node.

using ll = long long;
using namespace std;

struct DiffConstraint {
    int n;
    vector<array<ll, 3>> constraints;

    DiffConstraint(int n) : n(n) {}

    // Adds a constraint of the form: x_v - x_u >= w.
    void add_constraint(int u, int v, ll w) {
        constraints.push_back({u, v, w});
    }

 
    bool isSolvable() {
        vector<ll> dist(n, 0);
        for (int i = 0; i < n; i++) {
            bool updated = false;
            for (auto& edge : constraints) {
                int u = edge[0];
                int v = edge[1];
                ll w = edge[2];
                if (dist[v] < dist[u] + w) {
                    dist[v] = dist[u] + w;
                    updated = true;
                }
            }
            if (!updated) {
                return true; // No updates in a full pass, stable solution found.
            }
            // If an update occurs on the nth iteration, a positive-weight cycle exists.
            if (i == n - 1 && updated) {
                return false;
            }
        }
        return true;
    }

    vector<ll> getMinimalSolution() {
        vector<ll> dist(n, 0);
        for (int i = 0; i < n - 1; i++) {
            bool updated = false;
            for (auto& edge : constraints) {
                int u = edge[0];
                int v = edge[1];
                ll w = edge[2];
                if (dist[v] < dist[u] + w) {
                    dist[v] = dist[u] + w;
                    updated = true;
                }
            }
            if (!updated) break;
        }
        return dist;
    }

    vector<ll> getMaximalSolution() {
        vector<ll> dist(n, 0);
        for (int i = 0; i < n - 1; i++) {
            bool updated = false;
            for (auto& edge : constraints) {
                int u = edge[0];
                int v = edge[1];
                ll w = edge[2];
                // Corresponds to solving for x_u - x_v <= -w
                if (dist[v] > dist[u] - w) {
                    dist[v] = dist[u] - w;
                    updated = true;
                }
            }
            if (!updated) break;
        }

        // Negate the result to get the maximal solution for the original problem.
        for (int i = 0; i < n; i++) {
            dist[i] = -dist[i];
        }
        return dist;
    }
};
