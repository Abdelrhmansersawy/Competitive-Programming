struct DiffConstraints {
    vector<array<ll,3>> constraints;  // {u, v, C} for X_u - X_v >= C
    int num_vars = 0;
    
    void setNumVariables(int n) {
        num_vars = n;
    }
    
    void addConstraint(int u, int v, ll C) {
        constraints.push_back({u, v, C});
    }
    
    bool isSolvable() {
        int n = num_vars;
        vector<ll> dist(n, 0);
        int m = constraints.size();
        
        // Run Bellman-Ford algorithm n times
        for (int i = 0; i < n; ++i) {
            bool updated = false;
            for (int j = 0; j < m; ++j) {            
                auto [u,v,C] = constraints[j];
                
                // Corrected: For X_u - X_v ≥ C, the constraint is X_v + C ≤ X_u
                if (dist[v] + C > dist[u]) {
                    dist[u] = dist[v] + C;
                    updated = true;
                }
            }
            if (!updated) return true;
        }
        
        // Check for negative cycles in the nth iteration
        for (int j = 0; j < m; ++j) {
            auto [u,v,C] = constraints[j];
            if (dist[v] + C > dist[u]) {
                return false; // Negative cycle detected
            }
        }
        
        return true;
    }
    
    vector<ll> getMinValues() {
        if (!isSolvable()) {
            // Handle unsolvable case
            return {};
        }
        
        int n = num_vars;
        vector<ll> dist(n, 0);
        int m = constraints.size();
        
        // Run Bellman-Ford to find minimum values
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < m; ++j) {
                auto [u,v,C] = constraints[j];
                
                // Corrected: For X_u - X_v ≥ C, the constraint is X_v + C ≤ X_u
                dist[u] = max(dist[u] , dist[v] + C);
            }
        }
        
        return dist;
    }
};
