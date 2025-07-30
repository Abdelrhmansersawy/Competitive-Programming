/**
 * Treap (Multiset Style)
 * ----------------------
 * A randomized BST supporting:
 * - insert(k), erase(k)
 * - find_by_order(k), order_of_key(k)
 * - All in O(log N) amortized
 *
 * Supports multiple identical elements (multiset behavior).
 * For set-like behavior, erase before insert.
 */

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key, prior, size;
    Node *l, *r;
    Node(int v) : key(v), prior(rand()), size(1), l(NULL), r(NULL) {}
};

typedef Node* pNode;

struct Treap {
    pNode t = NULL;

    int sz(pNode t) { return t ? t->size : 0; }

    void pull(pNode t) {
        if (t) t->size = sz(t->l) + 1 + sz(t->r);
    }

    void split(pNode t, pNode &l, pNode &r, int key) {
        if (!t) l = r = NULL;
        else if (t->key < key) split(t->r, t->r, r, key), l = t;
        else split(t->l, l, t->l, key), r = t;
        pull(t);
    }

    void merge(pNode &t, pNode l, pNode r) {
        if (!l || !r) t = l ? l : r;
        else if (l->prior > r->prior) merge(l->r, l->r, r), t = l;
        else merge(r->l, l, r->l), t = r;
        pull(t);
    }

    void insert(pNode &t, pNode it) {
        if (!t) t = it;
        else if (it->prior > t->prior) split(t, it->l, it->r, it->key), t = it;
        else insert((it->key < t->key ? t->l : t->r), it);
        pull(t);
    }

    void erase(pNode &t, int key) {
        if (!t) return;
        if (t->key == key) {
            pNode tmp = t;
            merge(t, t->l, t->r);
            delete tmp;
        } else erase((key < t->key ? t->l : t->r), key);
        pull(t);
    }

    int getKth(pNode t, int k) {
        if (!t) return -1;
        int L = sz(t->l);
        if (k == L) return t->key;
        if (k < L) return getKth(t->l, k);
        return getKth(t->r, k - L - 1);
    }

    int orderOf(pNode t, int key) {
        if (!t) return 0;
        if (key <= t->key) return orderOf(t->l, key);
        return sz(t->l) + 1 + orderOf(t->r, key);
    }

    void nullify(pNode t) {
        if (!t) return;
        nullify(t->l), nullify(t->r);
        delete t;
    }

    // Public interface

    void insert(int k) {
        insert(t, new Node(k));
    }

    void erase(int k) {
        erase(t, k);
    }

    int find_by_order(int k) {
        return getKth(t, k);  // 0-based
    }

    int order_of_key(int k) {
        return orderOf(t, k);
    }

    void clear() {
        nullify(t);
        t = NULL;
    }

} treap;
int main() {
    treap.insert(5);
    treap.insert(2);
    treap.insert(5);
    treap.erase(2);
    cout << treap.find_by_order(0) << "\n";  // Output: 5
    cout << treap.order_of_key(6) << "\n";   // Output: 2
}
