#include <bits/stdc++.h>
using namespace std;


// --- DEBUGGING TOOLS ---

// 1. Table View: States & Transitions
void debug_states() {
    cerr << "\n=== SAM STATES TABLE ===\n";
    cerr << "ID\tLen\tLink\tClone\tPos\tTransitions\n";
    for(int i = 0; i < sz; i++) {
        cerr << i << "\t" 
             << st[i].len << "\t" 
             << st[i].link << "\t" 
             << (st[i].is_clone ? "YES" : "NO") << "\t"
             << st[i].first_pos << "\t";
        
        for(int c = 0; c < 26; c++) {
            if(st[i].nxt[c] != -1) {
                cerr << (char)('a' + c) << "->" << st[i].nxt[c] << "  ";
            }
        }
        cerr << "\n";
    }
    cerr << "========================\n";
}

// 2. Tree View: Suffix Links
vector<int> tree_adj[2 * MAXN];

void dfs_print_tree(int u, int depth) {
    for(int i = 0; i < depth; i++) cerr << "  "; // Indent
    
    cerr << "|- [" << u << "] len:" << st[u].len;
    if(st[u].is_clone) cerr << " (Clone)";
    cerr << "\n";

    for(int v : tree_adj[u]) {
        dfs_print_tree(v, depth + 1);
    }
}

void debug_tree() {
    cerr << "\n=== SUFFIX LINK TREE ===\n";
    // Build adjacency list for links
    for(int i = 0; i < sz; i++) tree_adj[i].clear();
    for(int i = 1; i < sz; i++) {
        if(st[i].link != -1) tree_adj[st[i].link].push_back(i);
    }
    
    dfs_print_tree(0, 0);
    cerr << "========================\n";
}

int main() {
    // Fast I/O
    ios::sync_with_stdio(0); cin.tie(0);

    // Example Input
    string s = "abcbc";
    cout << "Building SAM for string: " << s << "\n";
    
    build(s);

    // Call Debug Functions (Outputs to stderr)
    debug_states();
    debug_tree();

    return 0;
}

/*
debug_states()

ID  Len Link Clone Pos   Transitions
0   0   -1   NO    0     a->1 b->2 c->3 
1   1   0    NO    0     b->4 
2   1   0    NO    1     c->5 
...
*/

/*
debug_tree();

[0] len:0
  [1] len:1
    [4] len:2
      [6] len:3 (C)
  [2] len:1
    [5] len:2
      [7] len:3 (C)
        [8] len:4
          [9] len:5
...
*/
