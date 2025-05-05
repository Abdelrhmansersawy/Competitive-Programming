struct segtree_with_rollback {
private:
    struct Node {
        ll sum;
        
        Node() : sum(0) {}
        Node(ll val) : sum(val) {}
        
        Node operator + (const Node &other) const {
            Node res;
            res.sum = sum + other.sum;
            return res;
        }
    };

    struct seg_save {
        int time;
        int Node_idx;
        Node node_val;
        ll lazy_val;
    };

    int n, time = 0;
    vector<Node> tree;
    vector<ll> lazy;
    vector<int> upd_times;
    vector<seg_save> history;
    
    void add_history(int Node_idx) {
        history.push_back({time, Node_idx, tree[Node_idx], lazy[Node_idx]});
    }
    
    void push_down(int x, ll lazy_val) {
        if (lazy_val == 0) return;
        add_history(x);  
        tree[x].sum += lazy_val * (tree[x].sum == 0 ? 1 : tree[x].sum);   
        lazy[x] += lazy_val;
    }
    
    void propagate(int x, int l, int r) {
        if (r - l == 1) return;
        if (lazy[x] == 0) return;
        add_history(x);
        int mid = (l + r) / 2;
        push_down(2 * x + 1, lazy[x]);
        push_down(2 * x + 2, lazy[x]);
        
        lazy[x] = 0;
    }
    
    void upd(int lx, int rx, ll val, int x = 0, int l = 0, int r = -1) {
        if (r == -1) r = n;
        propagate(x, l, r);
        if (l >= rx || r <= lx) return;
        if (l >= lx && r <= rx) {
            tree[x].sum += val * (r - l);
            lazy[x] += val;
            return;
        }
        int mid = (l + r) / 2;
        upd(lx, rx, val, 2 * x + 1, l, mid);
        upd(lx, rx, val, 2 * x + 2, mid, r); 
        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

public:
    void init(int sz){
        this->n = sz;
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
    }

    void build(vector<ll> &a, int x = 0, int l = 0, int r = -1) {
        if (r == -1) r = n;
        
        if (r - l == 1) {
            tree[x] = Node(a[l]);
            return;
        }
        
        int mid = (l + r) / 2;
        build(a, 2 * x + 1, l, mid);
        build(a, 2 * x + 2, mid, r);
        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    void upd_with_rollback(int lx, int rx, ll val) {
        upd_times.push_back(time);
        upd(lx, rx, val);
        time++;
    }
    
    Node qry(int lx, int rx, int x = 0, int l = 0, int r = -1) {
        if (r == -1) r = n;
        propagate(x, l, r);
        if (l >= rx || r <= lx) return Node();
        if (l >= lx && r <= rx) return tree[x];
        int mid = (l + r) / 2;
        return qry(lx, rx, 2 * x + 1, l, mid) + qry(lx, rx, 2 * x + 2, mid, r);
    }

        void rollback() {
        if (upd_times.empty()) return;
        
        int last_time = upd_times.back();
        upd_times.pop_back();
        
        while (!history.empty() && history.back().time == last_time) {
            auto &save = history.back();
            tree[save.Node_idx] = save.node_val;
            lazy[save.Node_idx] = save.lazy_val;
            history.pop_back();
        }
    }
};
