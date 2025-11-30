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

    // enforce x_u - x_v == w
    void add_equality(int u, int v, ll w) {
        add_constraint(v, u, w);   // x_u - x_v >= w
        add_constraint(u, v, -w);  // x_v - x_u >= -w  => x_u - x_v <= w
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

    vector<ll> getSolution() {
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
};
