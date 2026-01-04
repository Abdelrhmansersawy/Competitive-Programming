
struct Node {
    ll sum = 0;
    ll lazy = 0;
    Node *L = nullptr, *R = nullptr;
    int len = 0;
    Node() {}
    Node(int _len): sum(0), lazy(0), L(nullptr), R(nullptr), len(_len) {}
    Node(ll s, ll laz, int _len, Node* l = nullptr, Node* r = nullptr)
        : sum(s), lazy(laz), L(l), R(r), len(_len) {}
};

Node* cloneNode(Node* v) {
    if (!v) return nullptr;
    return new Node(v->sum, v->lazy, v->len, v->L, v->R);
}

inline ll getSum(Node* v) { return v ? v->sum : 0; }

void push(Node* v) {
    if (!v || v->lazy == 0 || v->len == 1) {
        return;
    }
    int leftLen = (v->len + 1) / 2;
    int rightLen = v->len - leftLen;

    if (!v->L) v->L = new Node(leftLen);
    else v->L = cloneNode(v->L);
    if (!v->R) v->R = new Node(rightLen);
    else v->R = cloneNode(v->R);

    // update v data and propagate
    v->L->lazy += v->lazy;
    v->L->sum += 1LL * leftLen * v->lazy;

    v->R->lazy += v->lazy;
    v->R->sum += 1LL * rightLen * v->lazy;

    v->lazy = 0;
}

Node* upd(int nl, int nr, int l, int r, ll delta, Node* version) {
    Node* v = version ? cloneNode(version) : new Node(nr - nl + 1);

    if (l <= nl && nr <= r) {
        // add to lazy and update v data
        v->lazy += delta;
        v->sum += 1LL * (nr - nl + 1) * delta;
        return v;
    }
    if (nl > r || nr < l) return v;

    push(v);
    int mid = (nl + nr) >> 1;
    v->L = upd(nl, mid, l, r, delta, v->L);
    v->R = upd(mid + 1, nr, l, r, delta, v->R);
    v->sum = getSum(v->L) + getSum(v->R);
    return v;
}

ll query(int nl, int nr, int l, int r, Node* v) {
    if (!v || nl > r || nr < l) return 0;
    if (l <= nl && nr <= r) return v->sum;
    int mid = (nl + nr) >> 1;

    int leftOverlap = max(0, min(mid, r) - max(nl, l) + 1);
    int rightOverlap = max(0, min(nr, r) - max(mid + 1, l) + 1);

    ll leftRes = query(nl, mid, l, r, v->L);
    ll rightRes = query(mid + 1, nr, l, r, v->R);

    leftRes += 1LL * leftOverlap * v->lazy;
    rightRes += 1LL * rightOverlap * v->lazy;
    return leftRes + rightRes;
}
