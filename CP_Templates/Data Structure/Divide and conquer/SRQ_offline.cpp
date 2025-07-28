/*
 * ============================= Range Query Note =============================
 * 
 * Description:
 * A static range query structure supporting associative operations (e.g., multiplication, GCD, etc.)
 * using the "ZKW-style" divide-and-conquer sparse table approach.
 * 
 * Features:
 * - Preprocesses the array into a D&C-style 2D table in O(N log N).
 * - Answers queries for any [l, r) in O(1) using stor[l][t] and stor[r-1][t],
 *   where t = highest bit where l and r-1 differ.
 * 
 * Time Complexity:
 * - Build: O(N log N)
 * - Query: O(1)
 * 
 * Requirements:
 * - Define the associative operation in `comb(a, b)`.
 * - Set the identity element `id` based on that operation.
 * 
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template<class T, int SZ> struct RangeQuery {
private:
    int n;
    T stor[SZ][32 - __builtin_clz(SZ)];
    vector<T> a;

    /*
     * Identity Element `id`:
     * This is the neutral value for the operation `comb(a, b)`, meaning:
     *     comb(a, id) = comb(id, a) = a
     * 
     * Example identity elements for common operations:
     * - sum:           comb(a, b) = a + b     → id = 0
     * - multiplication: comb(a, b) = a * b     → id = 1
     * - gcd:           comb(a, b) = gcd(a, b) → id = 0
     * - min:           comb(a, b) = min(a, b) → id = INF
     * - max:           comb(a, b) = max(a, b) → id = -INF
     */
    const T id = 1;  // ← set this according to your operation

    // associative operation
    T comb(T a, T b) { 
        return a * b;  // Example: multiplication
    } 

    void fill(int l, int r, int ind) {
        if (ind < 0) return;
        int m = (l + r) / 2;
        T prod = id;
        for (int i = l; i < m; ++i) stor[i][ind] = prod = comb(a[i], prod);
        prod = id;
        for (int i = m; i < r; ++i) stor[i][ind] = prod = comb(prod, a[i]);
        fill(l, m, ind - 1); 
        fill(m, r, ind - 1);
    }

public:
    void init(vector<T> input) {
        a = input;
        n = 1;
        while ((1 << n) < int(a.size())) ++n;
        a.resize(1 << n, id);  // pad with identity
        fill(0, (1 << n), n - 1);
    }

    T query(int l, int r) {  // [l, r)
        if (l == r) return a[l];
        int t = 31 - __builtin_clz(r ^ l);
        return comb(stor[l][t], stor[r - 1][t]);
    }
};

// ============================= Example Usage =============================
int main() {
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);

    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif

    int n;
    cin >> n;
    vector<ll> input(n);
    for (int i = 0; i < n; i++) cin >> input[i];

    RangeQuery<ll, 1 << 18> rq;
    rq.init(input);

    int q;
    cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        cout << rq.query(l, r) << '\n';
    }
}
