struct DiffConstraintsMax {
    vector<array<ll,3>> constraints;  // {u, v, C} for X_u - X_v >= C
    int num_vars = 0;
    
    void setNumVariables(int n) {
        num_vars = n;
    }
    
    void addConstraint(int u, int v, ll C) {
        constraints.push_back({u, v, C});
    }
    
    // Check feasibility (no positive cycle) by transforming variables Y = -X
    bool isSolvable() const {
        vector<ll> dist(num_vars, 0);
        int m = constraints.size();
        
        for (int i = 0; i < num_vars; ++i) {
            bool updated = false;
            for (int j = 0; j < m; ++j) {
                auto [u,v,C] = constraints[j];
                
                // For X_u - X_v >= C with Y = -X, we get -Y_u + Y_v <= -C
                // Rearranged: Y_v <= Y_u - C
                if (dist[v] < dist[u] - C) {
                    dist[v] = dist[u] - C;
                    updated = true;
                }
            }
            if (!updated) return true;
            if (i == num_vars - 1) return false;  // Positive cycle detected
        }
        
        return true;
    }
    
    vector<ll> getMaxValues() const {
        if (!isSolvable()) {
            return {}; // Return empty vector if not solvable
        }
        
        vector<ll> dist(num_vars, 0);
        int m = constraints.size();
        
        // Run relaxation for n-1 iterations
        for (int i = 0; i < num_vars - 1; ++i) {
            for (int j = 0; j < m; ++j) {
                auto [u,v,C] = constraints[j];

                // For X_u - X_v >= C with Y = -X, we update Y_v when Y_v < Y_u - C
                if (dist[v] < dist[u] - C) {
                    dist[v] = dist[u] - C;
                }
            }
        }
        
        // Convert back to X values with X = -Y
        vector<ll> result(num_vars);
        for (int i = 0; i < num_vars; ++i) {
            result[i] = -dist[i];
        }
        
        return result;
    }
};
