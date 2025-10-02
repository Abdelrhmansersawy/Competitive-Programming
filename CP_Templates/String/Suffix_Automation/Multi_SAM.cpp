#include <bits/stdc++.h>
using namespace std;

/*
  multi_SAM

  - Alphabet: lowercase 'a'..'z' (26). Change if needed.
  - Set MAXN to expected max single-string length or the sum of lengths
    (better: sum of lengths of all strings you'll insert).
  - Call sa_init() once, then call build(s) for every string s you want to register.
  - Use find_state(t) + st[v].cnt to get "in how many inserted strings does t appear".
*/

namespace multi_SAM {

const int MAXN = 100000 + 9;         // adjust as needed (sum of lengths)
struct state {
    int len;
    int link;
    int first_pos;
    bool is_clone;
    int nxt[26];

    // multi-string helpers:
    int lastString; // marker: last string id that touched this state
    int cnt;        // number of distinct strings containing substrings of this state
};

static state st[2 * MAXN];
static int sz, last;
static int stringCount; // current string id (starts from 1)

/* initialize SAM (call once before adding strings) */
void sa_init() {
    // initialize root
    st[0].len = 0;
    st[0].link = -1;
    st[0].first_pos = -1;
    st[0].is_clone = false;
    for (int i = 0; i < 26; ++i) st[0].nxt[i] = -1;

    st[0].lastString = 0;
    st[0].cnt = 0;

    sz = 1;
    last = 0;
    stringCount = 0;
}

/* Count: walk suffix links and increment cnt for the current string id.
   Ensures each state is counted at most once per inserted string. */
void Count(int node) {
    while (node != -1) {
        if (st[node].lastString == stringCount) return; // already counted for this string
        st[node].cnt += 1;
        st[node].lastString = stringCount;
        node = st[node].link;
    }
}

/* extend SAM by char c (pos is optional: end position in the current string) */
void sa_extend(char c, int pos) {
    int letter = c - 'a';
    // fast path: existing transition of correct length
    if (st[last].nxt[letter] != -1 && st[ st[last].nxt[letter] ].len == st[last].len + 1) {
        last = st[last].nxt[letter];
        Count(last);
        return;
    }

    int cur = sz++;
    st[cur].len = st[last].len + 1;
    st[cur].first_pos = pos;
    st[cur].is_clone = false;
    for (int i = 0; i < 26; ++i) st[cur].nxt[i] = -1;
    st[cur].lastString = 0;
    st[cur].cnt = 0;

    int p = last;
    while (p != -1 && st[p].nxt[letter] == -1) {
        st[p].nxt[letter] = cur;
        p = st[p].link;
    }

    if (p == -1) {
        st[cur].link = 0;
        Count(cur);
    } else {
        int q = st[p].nxt[letter];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
            Count(cur);
        } else {
            int clone = sz++;
            // copy q -> clone
            st[clone].len = st[p].len + 1;
            for (int i = 0; i < 26; ++i) st[clone].nxt[i] = st[q].nxt[i];
            st[clone].link = st[q].link;
            st[clone].first_pos = st[q].first_pos;
            st[clone].is_clone = true;

            // clone inherits multi-string metadata
            st[clone].lastString = st[q].lastString;
            st[clone].cnt = st[q].cnt;

            while (p != -1 && st[p].nxt[letter] == q) {
                st[p].nxt[letter] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
            Count(cur);
        }
    }
    last = cur;
}

/* Build (add) one string into the multi-SAM.
   Call this for each string you want to register. */
void build(const string &s) {
    // start a new string id
    ++stringCount;
    last = 0; // reset to root so substrings don't cross string boundaries
    for (int i = 0; i < (int)s.size(); ++i) {
        sa_extend(s[i], i);
    }
}

/* find_state: follow t from root and return state index or -1 if not present */
int find_state(const string &t) {
    int v = 0;
    for (char ch : t) {
        int letter = ch - 'a';
        if (letter < 0 || letter >= 26) return -1;
        if (st[v].nxt[letter] == -1) return -1;
        v = st[v].nxt[letter];
    }
    return v;
}

/* count_strings_with_substring: how many added strings contain substring t? */
int count_strings_with_substring(const string &t) {
    int v = find_state(t);
    if (v == -1) return 0;
    return st[v].cnt;
}

} // namespace multi_SAM

// ---------------------- Example usage --------------------------------------
// int main() {
//     // Make sure MAXN (inside multi_SAM) is large enough for total length.
//     multi_SAM::sa_init();
//     multi_SAM::build("abc");
//     multi_SAM::build("bcd");
//     cout << multi_SAM::count_strings_with_substring("bc") << "\n"; // -> 2
//     cout << multi_SAM::count_strings_with_substring("abc") << "\n"; // -> 1
//     return 0;
// }
// ---------------------------------------------------------------------------

