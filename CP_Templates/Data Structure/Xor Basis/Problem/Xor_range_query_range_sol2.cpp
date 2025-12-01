/**
 * Solution Idea: Parity Tracking Linear Basis
 * * Core Logic:
 * 1. Standard Linear Basis fails with Range XOR Updates because we lose track of 
 * how many original numbers formed a basis element.
 * - Even combination: (a ^ x) ^ (b ^ x) = a ^ b (Update cancels out).
 * - Odd combination: (a ^ x) = a ^ x (Update stays).
 * * 2. The Trick: Map every value v -> (v << 1) | 1.
 * - This adds a "Tracking Bit" (LSB) to every number.
 * - XORing an ODD number of elements results in LSB = 1.
 * - XORing an EVEN number of elements results in LSB = 0.
 * * 3. Lazy Propagation (pushdown):
 * - If (basis_element & 1): It's an ODD combination. Apply the lazy value.
 * - If !(basis_element & 1): It's an EVEN combination. The lazy value cancels out.
 * * 4. Query: Shift the result right (ans >> 1) to discard the tracking bit.
 */

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
#define sz(s) (int)(s).size()
#define all(s) s.begin(),s.end()

void Speed() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

const int max_bit = 32;
struct xor_basis {
    array<int, max_bit> basis{};
    int cur_size = 0;

    bool insert(int mask) {
        for (int i = max_bit - 1; i >= 0; --i) {
            if (((mask >> i) & 1) ^ 1) continue;
            if (!basis[i]) {
                basis[i] = mask;
                cur_size++;
                return 1;
            }
            mask ^= basis[i];
        }
        return 0;
    }
};

struct Node {
    xor_basis val;
    int lazy = 0;
} neutral;

struct segtree {
    segtree *left = nullptr, *right = nullptr;

    Node node = {};

    int start, end;

    segtree(int l = 0, int r = 0) : start(l), end(r) {}

    void extend() {
        if (left == nullptr) {
            int mid = start + end >> 1;
            left = new segtree(start, mid);
            right = new segtree(mid + 1, end);
        }
    }

    Node pushup(Node a, Node b) {
        Node ret = a;
        for(int x : b.val.basis){
            ret.val.insert(x);
        }
        return ret;
    }

    void pushdown(){
        if(!node.lazy) return;
        vector<int> temp;
        for(int& x : node.val.basis){
            if(x & 1){
                temp.push_back(x ^ node.lazy);
                x = 0;
            }
        }
        for(int x : temp) node.val.insert(x);
        if (start != end) {
            extend();
            left->node.lazy ^= node.lazy;
            right->node.lazy ^= node.lazy;
        }
        node.lazy = 0;
    }

    void build(vector<int>& v) {
        if (start == end) {
            node.val.insert(v[start]);
            return;
        }
        extend();
        left->build(v);
        right->build(v);
        node = pushup(left->node, right->node);
    }
    
    void update(int l, int r, int val) {
        pushdown();
        if (start > r || end < l)
            return;
        if (start >= l && end <= r) {
            node.lazy = val;
            pushdown();
            return;
        }
        extend();
        left->update(l, r, val);
        right->update(l, r, val);
        node = pushup(left->node, right->node);
    }

    Node query(int l, int r) {
        pushdown(); 
        if (r < start || end < l)
            return neutral;
        if (l <= start && end <= r)
            return node;
        extend();
        Node ret = pushup(left->query(l , r), right->query(l , r));
        return ret;
    }

    ~segtree() {
        if (left == nullptr)return;
        delete left;
        delete right;
    }
};

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    // Important: Shift left and add 1 for tracking
    for(auto& it : a) cin >> it, it = it << 1 | 1;
    segtree* root = new segtree(0, n - 1);
    root->build(a);
    while(q--){
        int t, l, r; cin >> t >> l >> r; l--; r--;
        if(t == 1){
            int x; cin >> x; x <<= 1; // Update value also shifted
            root->update(l, r, x);
        }
        if(t == 2){
            auto node = root->query(l, r).val;
            xor_basis ans;
            // Shift back to get actual values
            for(int x : node.basis) ans.insert(x >> 1);
            cout << (1LL << ans.cur_size) << '\n';
        }
    }
}

int main() {
    Speed();
    int tc = 1;
    //cin >> tc;
    while (tc--) {
        solve();
    }
    return 0;
}
