/**
 * @brief Decomposes the total flow into individual s-t paths.
 * @usage Must be called *after* `flow()` has been executed.
 * @complexity O(num_paths * E).
 * @return A vector of pairs {flow_amount, path_nodes}.
 */
vector<pair<long long, vector<int>>> get_flow_paths() {
    vector<pair<long long, vector<int>>> result_paths;
    
    vector<long long> current_flows;
    for(const auto& edge : edges) {
        current_flows.push_back(edge.flow);
    }

    while (true) {
        vector<int> parent(n, -1);
        vector<int> edge_to(n, -1);
        queue<int> path_q;

        path_q.push(s);
        parent[s] = s;

        while (!path_q.empty()) {
            int u = path_q.front();
            path_q.pop();
            if (u == t) break;

            for (int id : adj[u]) {
                if (edges[id].v == u && current_flows[id] > 0 && parent[edges[id].u] == -1) {
                    parent[edges[id].u] = u;
                    edge_to[edges[id].u] = id;
                    path_q.push(edges[id].u);
                }
            }
        }

        if (parent[t] == -1) break;

        long long path_flow = flow_inf;
        vector<int> current_path_nodes;
        vector<int> current_path_edges;

        int curr = t;
        while (curr != s) {
            current_path_nodes.push_back(curr);
            int edge_id = edge_to[curr];
            current_path_edges.push_back(edge_id);
            path_flow = min(path_flow, current_flows[edge_id]);
            curr = parent[curr];
        }
        current_path_nodes.push_back(s);
        reverse(current_path_nodes.begin(), current_path_nodes.end());

        if (path_flow > 0) {
             result_paths.emplace_back(path_flow, current_path_nodes);
        }

        for (int edge_id : current_path_edges) {
            current_flows[edge_id] -= path_flow;
        }
    }
    return result_paths;
}


/**
 * @brief Finds the edges of a minimum s-t cut.
 * @usage Must be called *after* `flow()` has been executed.
 * @complexity O(V + E).
 * @return A vector of pairs (u, v) representing an edge in the min cut.
 */
vector<pair<int, int>> get_min_cut_edges() {
    vector<bool> visited(n, false);
    queue<int> q_cut;
    q_cut.push(s);
    visited[s] = true;
    while (!q_cut.empty()) {
        int v = q_cut.front(); q_cut.pop();
        for (int id : adj[v]) {
            int u = edges[id].u;
            if (!visited[u] && edges[id].cap > edges[id].flow) {
                visited[u] = true;
                q_cut.push(u);
            }
        }
    }

    vector<pair<int, int>> cut_edges;
    for (const FlowEdge& e : edges) {
        if (e.cap > 0 && visited[e.v] && !visited[e.u]) {
            cut_edges.emplace_back(e.v, e.u);
        }
    }
    return cut_edges;
}


/**
 * @brief Extracts the maximum matching from a flow network.
 * @usage For bipartite matching. Must be called *after* `flow()` on a 0-1 network.
 * @complexity O(E) for extraction, but dominated by `flow()` call.
 * @return A vector of pairs (u, v) representing the matched nodes.
 */
vector<pair<int, int>> get_matching() {
    vector<pair<int, int>> matching;
    for (const FlowEdge& e : edges) {
        // A matched edge has capacity 1, flow 1, and is not connected to s or t.
        if (e.cap == 1 && e.flow == 1 && e.v != s && e.u != t) {
            matching.emplace_back(e.v, e.u);
        }
    }
    return matching;
}
