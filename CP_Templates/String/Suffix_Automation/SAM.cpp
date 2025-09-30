// A state in the Suffix Automaton (SAM)
// len        : Length of the longest substring in this equivalence class
// link       : Suffix link (the "failure link" to the largest proper suffix state)
// first_pos  : End position of the substring's first appearance in the text
// nxt[26]    : Transitions for each character (here fixed for lowercase 'a'–'z')
// ------------------------------------------
// cnt[cur] = 1; 
//    → Marks that this state corresponds to 1 occurrence initially.
//      Later, you can propagate these counts through suffix links
//      to compute how many times each substring appears in the text.

// is_terminal[cur] = 1;
//    → Marks this state as "terminal" (i.e., corresponds to some suffix of the text).
//      Collecting all terminal states lets you check whether a substring
//      is also a suffix, or solve problems like finding all suffixes.

// pos_state[pos] = cur;
//    → Maps the text position `pos` to the state representing the whole
//      prefix ending at that position. Useful when you need to link
//      specific positions in the string back to SAM states
//      (e.g., for LCS queries or substring reconstruction).


struct state {
    int len, link, first_pos;
    int nxt[26];
};

const int MAXN = 1e5+9;
state st[2 * MAXN];
int sz, last;

void sa_init() {
    st[0].len = 0;
    st[0].link = -1;
    fill(st[0].nxt, st[0].nxt + 26, -1);
    sz = 1;
    last = 0;
}

void sa_extend(char c, int pos) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    st[cur].first_pos = pos;
    fill(st[cur].nxt, st[cur].nxt + 26, -1);

    // cnt[cur] = 1; 
    // is_terminal[cur] = 1;
    // pos_state[pos] = cur;
    
    int p = last, letter = c - 'a';
    while (p != -1 && st[p].nxt[letter] == -1) {
        st[p].nxt[letter] = cur;
        p = st[p].link;
    }

    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].nxt[letter];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            copy(st[q].nxt, st[q].nxt + 26, st[clone].nxt);
            st[clone].link = st[q].link;
            st[clone].first_pos = st[q].first_pos;

            while (p != -1 && st[p].nxt[letter] == q) {
                st[p].nxt[letter] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

void build(const string &s) {
    sa_init();
    for (int i = 0; i < (int)s.size(); i++) {
        sa_extend(s[i], i);
    }
}
