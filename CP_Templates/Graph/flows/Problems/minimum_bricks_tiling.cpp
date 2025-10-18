/*
Problem:
  Given an n×m grid of '.' and '#' (at least one '#'), place "bricks" so that
  every '#' cell is covered by exactly one brick and '.' cells are not covered.
  A brick is an axis-aligned rectangle with integer sides and with at least one
  side equal to 1 (i.e. a 1×k or k×1 segment). Minimize the number of bricks.

Complexity:
  - Building H and V and edges: O(n*m).
  - Hopcroft–Karp for maximum matching: O(E * sqrt(V)) which is fast enough
    for n,m ≤ 200 in practice.


Intuition:
 - Start with every black cell as a 1×1 brick.
 - Removing a border between two adjacent black cells merges them and saves 1 brick.
 - But removing two borders that meet at a corner makes an 'L' (invalid).
 - Build a graph: each removable border is a node; connect two nodes if they conflict.
 - Let H = number of horizontal borders, V = number of vertical borders, P = H+V.

Key relations:
 - A valid set of removals = an independent set in this graph.
 - min vertex cover + max independent set = P.
 - By König (bipartite graphs): min vertex cover = max matching.
 - Hence max independent set = P - max_matching.
 - Answer = black - max_independent_set = black - (P - max_matching) = black - P + max_matching.

Compute max_matching with Hopcroft–Karp.
*/

int n, m;
    if(!(cin >> n >> m)) return 0;
    vector<string> a(n);
    for(int i=0;i<n;++i) cin >> a[i];
 
    int black = 0;
    for(int i=0;i<n;++i) for(int j=0;j<m;++j) if(a[i][j]=='#') ++black;
 
    // enumerate horizontal pairs: (i,j) -- (i,j+1)
    vector<vector<int>> Hid(n, vector<int>(m, -1));
    int H = 0;
    for(int i=0;i<n;++i){
        for(int j=0;j+1<m;++j){
            if(a[i][j]=='#' && a[i][j+1]=='#'){
                Hid[i][j] = H++;
            }
        }
    }
 
    // enumerate vertical pairs: (i,j) -- (i+1,j)
    vector<vector<int>> Vid(n, vector<int>(m, -1));
    int V = 0;
    for(int i=0;i+1<n;++i){
        for(int j=0;j<m;++j){
            if(a[i][j]=='#' && a[i+1][j]=='#'){
                Vid[i][j] = V++;
            }
        }
    }
 
    HopcroftKarp hk(H, V);
 
    for(int i=0;i<n;++i){
        for(int j=0;j+1<m;++j){
            int hid = Hid[i][j];
            if(hid == -1) continue;
            // vertical at (i-1, j)
            if(i-1 >= 0 && Vid[i-1][j] != -1) hk.add_edge(hid, Vid[i-1][j]);
            // vertical at (i, j)
            if(i+1 <= n-1 && Vid[i][j] != -1) hk.add_edge(hid, Vid[i][j]);
            // vertical at (i-1, j+1)
            if(i-1 >= 0 && Vid[i-1][j+1] != -1) hk.add_edge(hid, Vid[i-1][j+1]);
            // vertical at (i, j+1)
            if(i+1 <= n-1 && Vid[i][j+1] != -1) hk.add_edge(hid, Vid[i][j+1]);
        }
    }
 
    int P = H + V;
    int M = hk.max_matching();
    int ans = black - P + M;
    cout << ans << '\n';
