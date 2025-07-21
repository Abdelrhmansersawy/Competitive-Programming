// Finds the largest permutation of `s` that is lexicographically < `p`.
// O(26 * n)
string get_prev_perm(string s, const string& p) {
    const int n = s.length();
    const int m = p.length();

    // Edge case: if s is shorter, the largest perm is s sorted descendingly.
    if (n < m) {
        sort(s.begin(), s.end(), greater<char>());
        return s;
    }
    // Edge case: if s is longer, no permutation can be smaller.
    if (n > m) {
        return "";
    }

    // Main logic for n == m
    vector<int> cnt(26, 0);
    for (char ch : s) {
        cnt[ch - 'a']++;
    }

    string res;
    stack<pi> st;
    
    bool diverged = false;
    int i = 0;

    auto backtrack = [&]() -> bool {
        while (!st.empty()) {
            auto [prev_i, prev_c] = st.top();
            st.pop();
            res.pop_back();
            cnt[prev_c]++;
            i = prev_i;

            // Find largest available char < prev_c
            for (int c = prev_c - 1; c >= 0; --c) {
                if (cnt[c] > 0) {
                    cnt[c]--;
                    res.push_back('a' + c);
                    i++;
                    diverged = true;
                    return true;
                }
            }
        }
        return false;
    };
    
    while (true) {
        // Once diverged, fill rest with largest available chars.
        if (diverged) {
            for (int c = 25; c >= 0; --c) {
                if (cnt[c] > 0) {
                    res.append(cnt[c], 'a' + c);
                }
            }
            return res;
        }

        if (i == n) {
            if (!backtrack()) return ""; // No smaller perm exists.
            continue;
        }
        
        int p_char = p[i] - 'a';
        
        // Option 1: Greedily match p[i].
        if (cnt[p_char] > 0) {
            cnt[p_char]--;
            res.push_back(p[i]);
            st.push({i, p_char});
            i++;
            continue;
        }

        // Option 2: Can't match. Find largest char < p[i].
        int next_c = p_char - 1;
        while (next_c >= 0 && cnt[next_c] == 0) {
            next_c--;
        }
        
        if (next_c >= 0) {
            cnt[next_c]--;
            res.push_back('a' + next_c);
            i++;
            diverged = true;
            continue;
        }

        // Option 3: Can't match or diverge. Must backtrack.
        if (!backtrack()) {
            return "";
        }
    }
}
