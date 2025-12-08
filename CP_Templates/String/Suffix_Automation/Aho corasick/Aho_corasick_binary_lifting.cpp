// ------------------------------------------------------------------
// THE STRATEGY: "Reverse 1 Substring to Maximize Matches"
// TRICK: We can't simulate every reversal in O(N). Too slow!
//        Instead, we use Binary Lifting (Powers of 2) to "jump" 
//        through the AC Automaton in O(log N).
// ------------------------------------------------------------------

int n, m, LG;
// up1 = Forward Jumps, up2 = Backward Jumps (because we reverse!)
vector<int> up1, up2;
vector<ll> res1, res2;

// FLATTENING TRICK:
// Maps 3D state [Level][Index][Node] -> 1D array to keep cache happy.
int id(int k, int i, int u) {
    return (k * n + i) * m + u;
}

// SETUP PHASE: The "Heavy Lifting"
// Precomputes where you land if you jump 2^k steps from any state.
// Crucial: We build BOTH forward (normal) and backward (reversed) tables.
void build(const string &s, const AhoCorasick &ac) {
    n = s.size();
    m = ac.v.size();
    
    // Calculate max power of 2 needed
    LG = 0;
    while ((1 << LG) <= n) ++LG;

    // Reset everything
    up1.assign(LG * n * m, -1);
    up2.assign(LG * n * m, -1);
    res1.assign(LG * n * m, 0LL);
    res2.assign(LG * n * m, 0LL);

    // Base case: k=0 (Jump size 1)
    for (int i = 0; i < n; ++i) {
        for (int u = 0; u < m; ++u) {
            int v = ac.v[u].nxt[s[i] - 'a'];
            // Single char jump is same forward or backward
            up1[id(0, i, u)] = up2[id(0, i, u)] = v;
            res1[id(0, i, u)] = res2[id(0, i, u)] = ac.v[v].nmatches;
        }
    }

    // DP Step: Combine two jumps of size 2^(k-1) to make 2^k
    for (int k = 1; k < LG; ++k) {
        int h = 1 << (k - 1); // Half jump length
        for (int i = 0; i + (1 << k) <= n; ++i) {
            for (int u = 0; u < m; ++u) {
                // 1. Forward Table (Normal)
                int v = up1[id(k - 1, i, u)];
                if (v != -1) {
                    up1[id(k, i, u)] = up1[id(k - 1, i + h, v)];
                    if (up1[id(k, i, u)] != -1)
                        res1[id(k, i, u)] = res1[id(k - 1, i, u)] + res1[id(k - 1, i + h, v)];
                }
            }
        }
        // 2. Backward Table (Reversed String Logic)
        // Watch out: 'i' needs to accommodate the backward reach!
        for (int i = (1 << k) - 1; i < n; ++i) {
            for (int u = 0; u < m; ++u) {
                int v = up2[id(k - 1, i, u)];
                if (v != -1) {
                    up2[id(k, i, u)] = up2[id(k - 1, i - h, v)];
                    if (up2[id(k, i, u)] != -1)
                        res2[id(k, i, u)] = res2[id(k - 1, i, u)] + res2[id(k - 1, i - h, v)];
                }
            }
        }
    }
}

// THE TIME TRAVELER:
// Instantly simulates traversing 'len' chars starting at 'i', state 'u'.
// rev=true  -> Walking BACKWARDS (simulating a reversed string)
// rev=false -> Walking FORWARDS (normal string)
pair<int, ll> query(int i, int u, int len, bool rev) {
    ll cur_res = 0;
    for (int b = 0; b < LG; ++b) {
        // If bit 'b' is set in 'len', take the jump!
        if ((len >> b) & 1) {
            if (u == -1) break; // Safety break
            int I = id(b, i, u);
            
            // Add matches from this jump
            cur_res += rev ? res2[I] : res1[I];
            
            // Move state 'u' to new node
            u = rev ? up2[I] : up1[I];
            
            // Update index 'i' (Add for normal, Subtract for reverse)
            i += rev ? -(1 << b) : (1 << b);
        }
    }
    return {u, cur_res};
}

// THE MAIN SOLVER:
// Tries every possible substring reversal [l, r]
// 1. Prefix [0...l-1] is just normal traversal (incremental).
// 2. Middle [l...r] is REVERSED -> use query(..., true).
// 3. Suffix [r+1...end] is NORMAL -> use query(..., false).
ll solve(string &s, AhoCorasick &ac) {
    int n = s.size();
    
    // Baseline: Don't reverse anything (just query the whole string)
    ll ans = query(0, 0, n, false).second;
    
    ll pre_m = 0; // Accumulated matches for prefix
    int pre_n = 0; // Current AC node for prefix

    // Iterate L (start of reversal)
    for (int l = 0; l < n; ++l) {
        // Iterate R (end of reversal)
        for (int r = l; r < n; ++r) {
            ll total = pre_m; // Start with prefix matches
            
            // MAGIC STEP: Simulate the reversed middle part S[l..r]
            // We start at 'r' and walk backwards 'r-l+1' steps!
            auto [mid_n, mid_m] = query(r, pre_n, r - l + 1, true);

            if (mid_n != -1) {
                total += mid_m;
                // If there is a suffix remaining, add its matches too
                if (r + 1 < n)
                    total += query(r + 1, mid_n, n - (r + 1), false).second;
                
                ans = max(ans, total);
            }
        }
        // Update prefix state for the next L
        pre_n = ac.v[pre_n].nxt[s[l] - 'a'];
        pre_m += ac.v[pre_n].nmatches;
    }
    return ans;
}
