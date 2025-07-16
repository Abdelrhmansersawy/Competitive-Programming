const ll DEFAULT = LLONG_MAX;
const int N = 1e9+9;

struct Line {
    ll m, c;
    Line(ll m = 0, ll c = DEFAULT) : m(m), c(c) {}
    ll operator()(ll x) const { return m * x + c; }
};

struct Node {
    Line line;
    Node *left = nullptr, *right = nullptr;
    Node(Line line = Line()) : line(line) {}
};

void insert(Line newLine, Node*& root, ll l = -N, ll r = N) {
    if (!root) {
        root = new Node(newLine);
        return;
    }

    ll m = (l + r) / 2;
    // (<) -> min f(x) , (>) -> max f(x)
    bool lef = newLine(l) < root->line(l);
    bool mid = newLine(m) < root->line(m);

    if (mid)
        swap(root->line, newLine);

    if (r - l == 1)
        return;

    if (lef != mid)
        insert(newLine, root->left, l, m);
    else
        insert(newLine, root->right, m, r);
}

ll query(ll x, Node* cur, ll l = -N, ll r = N) {
    if (!cur)
        return DEFAULT;
    ll m = (l + r) / 2;
    if (r - l == 1)
        return cur->line(x);
    if (x < m)
        return min(cur->line(x), query(x, cur->left, l, m));
    else
        return min(cur->line(x), query(x, cur->right, m, r));
}
