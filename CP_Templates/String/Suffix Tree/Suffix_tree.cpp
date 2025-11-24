struct SuffixTree {
private:
    string S;
    ll cnt = 0;
    int remmed_leaf = 0;

    struct Node {
        SuffixTree *ctx;
        int l, r, leaf_id = -1;
        Node *par, *suflink = NULL;
        map<char, Node*> nxt;

        Node(SuffixTree *T, int L, int R, Node *P, bool LEAF) : ctx(T), l(L), r(R), par(P) {
            if(LEAF) leaf_id = sz(ctx->leaves);
        }
        bool is_leaf() { return leaf_id != -1; }
        int size() { return is_leaf() ? sz(ctx->S) - l : (par ? r - l + 1 : 0); }
    };

    struct State {
        Node *u; int pos;
        State() {}
        State(Node *U, int P = -666) : u(U), pos(P) { if(P == -666) pos = u->size() - 1; }
        void go_back() { if(pos-- == 0) u = u->par, pos = u->size() - 1; }
    } st;

    Node *root;
    vector<Node*> nodes, leaves;
    bool rule3;

    Node* make_node(int L, int R, Node *P, bool LEAF) {
        nodes.push_back(new Node(this, L, R, P, LEAF));
        return nodes.back();
    }

    Node* walkdown(char c) {
        Node *v = st.u;
        if(st.pos == v->size() - 1) {
            if(v->is_leaf()) { v->r++; st.pos++; return NULL; }
            if(!v->nxt[c]) {
                v->nxt[c] = make_node(sz(S) - 1, sz(S) - 1, v, true); cnt++;
                leaves.push_back(v->nxt[c]);
            } else rule3 = true;
            st.u = v->nxt[c]; st.pos = 0;
            return NULL;
        }
        Node *p = v->par;
        if(S[v->l + st.pos + 1] == c) { st.pos++; rule3 = true; return NULL; }
        Node *mid = make_node(v->l, v->l + st.pos, p, false);
        p->nxt[S[v->l]] = mid; mid->nxt[S[v->l + st.pos + 1]] = v; v->par = mid; v->l += st.pos + 1;
        mid->nxt[c] = make_node(sz(S) - 1, sz(S) - 1, mid, true); cnt++;
        st.u = mid->nxt[c]; st.pos = 0; leaves.push_back(st.u);
        return mid;
    }

    void find_suflink(int l, bool add = true) {
        Node *v = st.u;
        if(st.pos == v->size() - 1 && v->suflink) { st = State(v->suflink); return; }
        Node *p = v->par;
        if(p->suflink) { l = sz(S) - st.pos - add - 1; st = State(p->suflink); }
        else st = State(root, -1);
        while(l < sz(S) - add) {
            int rem = sz(S) - add - l, prem = st.u->size() - 1 - st.pos;
            if(rem <= prem) { st.pos += rem; break; }
            l += prem + 1; st.u = st.u->nxt[S[l - 1]]; st.pos = 0;
        }
    }

    void delete_node(Node *n) {
        if(!n->par) return;
        if(st.u == n) {
            int old_pos = st.pos; find_suflink(sz(leaves) + 1, false);
            cnt -= (n->size() - old_pos - 1);
            n->leaf_id = sz(leaves); n->suflink = NULL; leaves.push_back(n);
            n->l = sz(S) - old_pos - 1; return;
        }
        cnt -= n->size();
        Node *p = n->par; p->nxt.erase(S[n->l]);
        if(p->nxt.empty()) delete_node(p);
    }

    Node* traverse(string &P) {
        if(P.empty()) return root;
        Node *curr = root; int idx = 0;
        while(idx < sz(P)) {
            char c = P[idx];
            if(!curr->nxt.count(c)) return NULL;
            Node *nxt = curr->nxt[c];
            int len = nxt->size();
            for(int i = 0; i < len && idx < sz(P); i++, idx++)
                if(S[nxt->l + i] != P[idx]) return NULL;
            curr = nxt;
        }
        return curr;
    }

public:
    SuffixTree(string s = "") {
        root = new Node(this, -1, -1, NULL, false);
        nodes.push_back(root);
        for(char c : s) append_back(c);
    }

    /* Adds char to sliding window. 
       Time: Amortized O(1) */
    void append_back(char c) {
        S += c; rule3 = false;
        if(sz(S) == 1) { st = State(root, -1); walkdown(c); return; }
        cnt += sz(leaves) - remmed_leaf;
        st = State(leaves.back()); st.go_back();
        Node *old_w = NULL;
        for(int l = sz(leaves); l < sz(S); l++) {
            find_suflink(l);
            Node *w = walkdown(c); st.go_back();
            if(old_w) old_w->suflink = st.u; old_w = w;
            if(rule3) { walkdown(c); return; }
        }
    }

    /* Removes oldest char from window. 
       Time: Amortized O(1) */
    void pop_front() {
        if(remmed_leaf < sz(leaves)) delete_node(leaves[remmed_leaf++]);
    }

    /* Total distinct substrings in window. 
       Time: O(1) */
    ll no_distinct() { return cnt; }

    /* Checks if string P exists in window. 
       Time: O(|P|) */
    bool exist(string P) { return traverse(P) != NULL; }
};
