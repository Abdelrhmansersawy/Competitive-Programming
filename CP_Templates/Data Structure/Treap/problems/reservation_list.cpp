/*
 * Implicit Treap (Rope) Solution for Dynamic Array Median Problem
 * * Supports operations in O(log N):
 * 1. Insert range of values after a specific value.
 * 2. Delete range of values after a specific value.
 * 3. Find 0-based index of a specific value (using parent pointers/map).
 * 4. Find K-th element (for median calculation).
 */

#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node;
using PNode = Node*;
map<int, PNode> mp;

struct Node {
    Node *l = 0, *r = 0, *par = 0;
    ull prior = rng();
    int st, len, sz;
    Node(int s, int e) : st(s), len(e-s+1), sz(e-s+1) { mp[st] = this; }
    ~Node() { if(mp.count(st) && mp[st] == this) mp.erase(st); }
};

// Returns subtree size, handles nullptr
int sz(PNode t){ return t ? t->sz : 0; }

// Updates node size based on children
void pull(PNode t){ if(t) t->sz = sz(t->l) + t->len + sz(t->r); }

// Joins trees l and r into t, maintains parent pointers
void merge(PNode &t, PNode l, PNode r){
    if(!l || !r) t = l ? l : r;
    else if(l->prior > r->prior) {
        merge(l->r, l->r, r);
        if(l->r) l->r->par = l;
        t = l;
    }
    else {
        merge(r->l, l, r->l);
        if(r->l) r->l->par = r;
        t = r;
    }
    pull(t);
}

// Splits t into l (first k elements) and r, maintains parents & map
void split(PNode t, int k, PNode &l, PNode &r){
    if(!t){ l = r = 0; return; }
    int L = sz(t->l);
    if(k <= L) {
        split(t->l, k, l, t->l);
        if(t->l) t->l->par = t;
        r = t; pull(r);
        if(l) l->par = 0;
    }
    else if(k >= L + t->len) {
        split(t->r, k - L - t->len, t->r, r);
        if(t->r) t->r->par = t;
        l = t; pull(l);
        if(r) r->par = 0;
    }
    else { // Split strictly inside the node range
        PNode tl = t->l, tr = t->r;
        if(tl) tl->par = 0;
        if(tr) tr->par = 0;
        PNode n1 = new Node(t->st, t->st + k - L - 1);
        PNode n2 = new Node(t->st + k - L, t->st + t->len - 1);
        merge(l, tl, n1);
        merge(r, n2, tr);
        delete t;
    }
}

// Recursively deletes tree to free memory
void clean(PNode t){
    if(!t) return;
    clean(t->l); clean(t->r); delete t;
}

// Inserts range [s, e] after index idx
void ins(PNode &t, int idx, int s, int e){
    PNode l, r; 
    split(t, idx, l, r);
    merge(l, l, new Node(s, e));
    merge(t, l, r);
}

// Deletes k elements starting after index idx
void del(PNode &t, int idx, int k){
    PNode l, m, r;
    split(t, idx, l, r);
    split(r, k, m, r);
    clean(m);
    merge(t, l, r);
}

// Returns the k-th value in the implicit array
int get_k(PNode t, int k){
    if(!t || k < 0 || k >= sz(t)) return -1;
    int L = sz(t->l);
    if(k < L) return get_k(t->l, k);
    if(k < L + t->len) return t->st + (k - L);
    return get_k(t->r, k - L - t->len);
}

// Returns 0-based index of value val by climbing parent pointers
int get_idx(int val) {
    auto it = mp.upper_bound(val);
    if(it == mp.begin()) return -1;
    --it;
    PNode curr = it->second;
    int idx = sz(curr->l) + (val - curr->st);
    while(curr->par) {
        PNode p = curr->par;
        if(p->r == curr) idx += sz(p->l) + p->len;
        curr = p;
    }
    return idx;
}

// Debug: Prints the array ranges in order
void print(PNode t) {
    if(!t) return;
    print(t->l);
    cout << "[" << t->st << ".." << t->st + t->len - 1 << "] ";
    print(t->r);
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int q; if(!(cin >> q)) return 0;
    
    PNode rt = new Node(0,0);
    long long nxt = 1;

    while(q--){
        int p; long long k; cin >> p >> k;
        int idx = get_idx(p);
        
        if(k > 0) {
            ins(rt, idx + 1, nxt, nxt + k - 1);
            nxt += k;
        } else {
            del(rt, idx + 1, -k);
        }
        cout << get_k(rt, (sz(rt) + 1) / 2 - 1) << '\n';
    }
}
