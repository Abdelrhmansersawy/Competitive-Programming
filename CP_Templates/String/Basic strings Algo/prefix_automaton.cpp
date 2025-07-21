/**
 * Computes the prefix‐function (π) for a string s.
 *
 * For each position i, π[i] is the length of the longest proper prefix
 * of s[0…i] which is also a suffix of s[0…i].
 *
 * Time: O(n), where n = s.length()
 *
 * @param s  input string
 * @return   vector<int> π of length n
 */
vector<int> prefix_function(const string &s) {
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1, j = 0; i < n; ++i) {
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            ++j;
        pi[i] = j;
    }
    return pi;
}

/**
 * Builds the pattern‐matching automaton for s.
 *
 * A pattern‐matching automaton is a state machine that,
 * given the current matched prefix length and the next character,
 * tells you the new matched prefix length—so you can scan text
 * in one pass and detect occurrences of s in O(text_length).
 *
 * Appends ‘#’, computes π, and fills aut[state][c] = next state on 'a'+c.
 * 
 * Time: O((|s|+1)·26)
 *
 * @param s   input pattern
 * @param aut output table of size (|s|+1)×26
 */
void compute_automaton(const string &s, vector<vector<int>> &aut) {
    string T = s + '#';
    int n = T.size();
    vector<int> pi = prefix_function(T);
    aut.assign(n, vector<int>(26));
    for (int i = 0; i < n; ++i) {
        for (int c = 0; c < 26; ++c) {
            char ch = 'a' + c;
            if (i > 0 && ch != T[i])
                aut[i][c] = aut[pi[i - 1]][c];
            else
                aut[i][c] = i + (ch == T[i]);
        }
    }
}
