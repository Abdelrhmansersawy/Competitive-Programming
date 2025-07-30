/**
 * Implicit Treap with Lazy Reversal
 * ----------------------------------
 * - Supports reverse operations in O(log n) per query.
 * - Maintains string as a balanced binary tree with heap property on random priorities.
 *
 * Operations:
 * - reverse(l, r): Reverse substring in range [l, r] (0-indexed)
 * - print(): In-order traversal to print current string
 *
 * Time: O(log n) per operation
 */
 
#include <bits/stdc++.h>
using namespace std;
 
#define all(v) (v).begin(), (v).end()
typedef long long ll;
 
/// Implicit Treap Node
struct Node {
    char key;
    int prior, size;
    bool rev;
    Node *l, *r;
 
    Node(char _c) : key(_c), prior(rand()), size(1), rev(false), l(nullptr), r(nullptr) {}
};
 
typedef Node* PNode;
 
/// Implicit Treap with Lazy Propagation
struct Treap {
    PNode root = nullptr;
 
    int sz(PNode t) { return t ? t->size : 0; }
 
    // Pull size from children
    void pull(PNode t) {
        if (!t) return;
        t->size = 1 + sz(t->l) + sz(t->r);
    }
 
    // Push lazy reversal flag down
    void push(PNode t) {
        if (!t || !t->rev) return;
        swap(t->l, t->r);
        if (t->l) t->l->rev ^= 1;
        if (t->r) t->r->rev ^= 1;
        t->rev = false;
    }
 
    // Split treap 't' into 'l' (first k elements) and 'r' (rest)
    void split(PNode t, int k, PNode &l, PNode &r) {
        if (!t) { l = r = nullptr; return; }
        push(t);
        if (sz(t->l) < k) {
            split(t->r, k - sz(t->l) - 1, t->r, r);
            l = t;
        } else {
            split(t->l, k, l, t->l);
            r = t;
        }
        pull(t);
    }
 
    // Merge treaps 'l' and 'r' into 't'
    void merge(PNode &t, PNode l, PNode r) {
        push(l);
        push(r);
        if (!l || !r) t = l ? l : r;
        else if (l->prior > r->prior) {
            merge(l->r, l->r, r);
            t = l;
        } else {
            merge(r->l, l, r->l);
            t = r;
        }
        pull(t);
    }
 
    // Reverse characters in range [l, r] (0-indexed)
    void reverse(int l, int r) {
        PNode t1, t2, t3;
        split(root, l, t1, t2);
        split(t2, r - l + 1, t2, t3);
        if (t2) t2->rev ^= 1;
        merge(t2, t2, t3);
        merge(root, t1, t2);
    }
 
    // Print in-order traversal (the string)
    void print(PNode t) {
        if (!t) return;
        push(t);
        print(t->l);
        cout << t->key;
        print(t->r);
    }
 
    // Free memory
    void clear(PNode &t) {
        if (!t) return;
        clear(t->l);
        clear(t->r);
        delete t;
        t = nullptr;
    }
 
    ~Treap() { clear(root); }
};
 
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    srand(time(0));  // Seed for random priorities
 
    
 
    int n, m;
    cin >> n >> m;
    string s; cin >> s;
 
    Treap tr;
    for (char c : s)
        tr.merge(tr.root, tr.root, new Node(c));
 
    while (m--) {
        int l, r;
        cin >> l >> r;
        tr.reverse(l - 1, r - 1); // 1-based to 0-based
    }
 
    tr.print(tr.root);
    cout << '\n';
    return 0;
}
