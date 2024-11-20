/*
Problem Statement:
Given a rectangular grid of size n × m, create a map of '0' and '1' terrain types where:
1. Only two terrain types are allowed ('0' and '1')
2. There must be exactly k connected components
   - Connected components are adjacent cells of same value
   - Cells are adjacent if they share a side

Input: Three integers n, m, k where:
- 1 ≤ n ≤ 1000 (rows)
- 1 ≤ m ≤ 1000 (columns)
- 1 ≤ k ≤ n × m (desired components)

Output:
- "YES" + grid solution if possible
- "NO" if impossible
*/
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    int a[n][m];
    
    // Case 1: One-dimensional grid (single row or column)
    if (n == 1 || m == 1) {
        cout << "YES\n";
        int num = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << num;
                if (k > 1) {
                    num = 1 - num;
                    k--;
                }
            }
            cout << '\n';
        }
        return;
    }
    
    // Case 2: Impossible case - when components would equal n*m-1
    if (k == n * m - 1) {
        cout << "NO\n";
        return;
    }
    
    // Case 3: All other cases
    cout << "YES\n";
    int num = 0;
    int flag = 0;
    
    // Adjust k if (k+1) is divisible by m
    if ((k + 1) % m == 0) {
        k--;
        flag = 1;
    }
    
    // Fill the grid with alternating values until k components are created
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            a[i][j] = num;
            num = 1 - num;
            k--;
            if (k <= 0) break;
        }
        if (k <= 0) break;
        if (m % 2 == 0) num = 1 - num;
    }
    
    // Fill remaining cells in the current row
    if (i == 0) {
        for (int x = j + 1; x < m; x++) {
            a[i][x] = 1 - num;
        }
    } else if (j + 1 < m) {
        a[i][j + 1] = num;
    }
    
    // Fill remaining rows by copying values from above
    for (int x = 0; x < m; x++) {
        int st;
        if (x <= j + 1 || i == 0) {
            st = i;
        } else {
            st = i - 1;
        }
        for (int y = st + 1; y < n; y++) {
            a[y][x] = a[st][x];
        }
    }
    
    // Handle special case when (k+1) was divisible by m
    if (flag) {
        a[n - 1][m - 1] = 1 - a[n - 1][m - 2];
    }
    
    // Print the final grid
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << a[i][j];
        }
        cout << '\n';
    }
}
