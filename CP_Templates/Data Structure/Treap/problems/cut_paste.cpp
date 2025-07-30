/*
------------------------------------------------------
    Implicit Treap - Cut and Paste Substring Problem
------------------------------------------------------
 
Problem:
---------
You are given a string of `n` characters and `m` operations. Each operation
consists of a pair of indices `[a, b]` (1-based). For each operation, cut the 
substring from position `a` to `b`, remove it from the string, and append it to the end.
 
Time Complexity:
----------------
- Each operation (split/merge) runs in **O(log n)** expected time.
- Total complexity: **O(n log n + m log n)**.
 
------------------------------------------------------
*/
 
#include <bits/stdc++.h>
using namespace std;
 
#define all(x) begin(x), end(x)
#define sz(x) int((x).size())
typedef long long ll;
 
// Treap node definition
struct Node {
    char key;     // Character value
    int prior;    // Random priority for balancing
    int size;     // Subtree size
    Node *l, *r;  // Left and right children
 
    Node(char c) : key(c), prior(rand()), size(1), l(nullptr), r(nullptr) {}
};
 
typedef Node* PNode;
 
struct Treap {
    PNode root = nullptr;
 
    int getSize(PNode t) {
        return t ? t->size : 0;
    }
 
    void pull(PNode t) {
        if (t) t->size = 1 + getSize(t->l) + getSize(t->r);
    }
 
    // Split treap into [0...k-1] and [k...end]
    void split(PNode t, int k, PNode &l, PNode &r) {
        if (!t) return void(l = r = nullptr);
        if (getSize(t->l) < k) {
            split(t->r, k - getSize(t->l) - 1, t->r, r);
            l = t;
        } else {
            split(t->l, k, l, t->l);
            r = t;
        }
        pull(t);
    }
 
    // Merge two treaps into one
    void merge(PNode &t, PNode l, PNode r) {
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
 
    // Perform cut-and-paste operation from index l to r (0-indexed)
    void cut_and_paste(int l, int r) {
        PNode left, mid, right;
        split(root, r + 1, root, right);
        split(root, l, left, mid);
        merge(root, left, right);
        merge(root, root, mid);
    }
 
    // In-order traversal to output the final string
    void print(PNode t) {
        if (!t) return;
        print(t->l);
        cout << t->key;
        print(t->r);
    }
 
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
    ios::sync_with_stdio(0);
    cin.tie(0);
    srand(time(0)); // Random seed for treap balancing
 
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
 
    Treap tr;
    for (char c : s)
        tr.merge(tr.root, tr.root, new Node(c));
 
    while (m--) {
        int l, r;
        cin >> l >> r;
        tr.cut_and_paste(l - 1, r - 1); // Convert to 0-based indexing
    }
 
    tr.print(tr.root);
    cout << '\n';
 
    return 0;
}
