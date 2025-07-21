// Finds the smallest permutation of `s` that is lexicographically > `p`.
// O(26 * n)
string get_next_perm(const string& s, const string& p) {
    vector<int> cnt(26, 0);
    for (char ch : s) {
        cnt[ch - 'a']++;
    }

    string res;
    // Backtrack stack: {index, char_value}
    stack<pi> st;
    
    bool diverged = false;
    int i = 0;
    const int n = s.length();
    const int m = p.length();

    // Lambda to handle backtracking logic.
    auto backtrack = [&]() -> bool {
        while (!st.empty()) {
            auto [prev_i, prev_c] = st.top();
            st.pop();

            // Restore state
            res.pop_back();
            cnt[prev_c]++;
            i = prev_i;

            // Find the next lexicographically larger char to place.
            for (int c = prev_c + 1; c < 26; ++c) {
                if (cnt[c] > 0) {
                    cnt[c]--;
                    res.push_back('a' + c);
                    i++;
                    diverged = true;
                    return true;
                }
            }
        }
        return false; // Backtracking failed.
    };
    
    while (true) {
        // Once diverged, fill the rest greedily with the smallest available chars.
        if (diverged) {
            for (int c = 0; c < 26; ++c) {
                if (cnt[c] > 0) {
                    res.append(cnt[c], 'a' + c);
                }
            }
            return res;
        }

        // Finished placing all characters.
        if (i == n) {
            if (!backtrack()) return ""; // No greater permutation exists.
            continue;
        }
        
        // Matched all of p, and s is longer. Must diverge now.
        if (i >= m) {
            diverged = true;
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

        // Option 2: Can't match. Find smallest char > p[i].
        int next_c = p_char + 1;
        while (next_c < 26 && cnt[next_c] == 0) {
            next_c++;
        }
        
        if (next_c < 26) {
            cnt[next_c]--;
            res.push_back('a' + next_c);
            i++;
            diverged = true;
            continue;
        }

        // Option 3: Can't match or diverge. Must backtrack.
        if (!backtrack()) {
            return ""; // No solution.
        }
    }
}
