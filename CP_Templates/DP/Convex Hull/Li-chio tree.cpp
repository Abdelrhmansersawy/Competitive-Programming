// LLONG_MAX -> min f(x) , -LLONG_MAX -> max f(x)
const ll DEFAULT = LLONG_MAX;
 
struct Line {
    ll m, c;
    Line(ll m = 0, ll c = DEFAULT) : m(m), c(c) {}
    ll operator()(ll x) const { return m * x + c; }
};
 
struct Node {
    Node *left, *right;
    Line line;
    Node(Line line = Line(), Node *left = nullptr, Node *right = nullptr)
        : line(line), left(left), right(right) {}
    Node *getLeft() { return left; }
    Node *getRight() { return right; }
};
 
Node *insert(Line newLine, Node *root, ll l, ll r) {
    if (root == nullptr) {
        return new Node(newLine, nullptr, nullptr);
    }
    Node *cur = new Node(root->line, root->left, root->right);
    ll m = (l + r) / 2;
    // (<) -> min f(x) , (>) -> max f(x)
    bool lef = newLine(l) < cur->line(l);
    bool mid = newLine(m) < cur->line(m);
 
    if (mid)
        swap(cur->line, newLine);
    if (r - l == 1)
        return cur;
 
    if (lef != mid)
        cur->left = insert(newLine, cur->left, l, m);
    else
        cur->right = insert(newLine, cur->right, m, r);
    return cur;
}
 
ll query(ll x, Node *cur, ll l, ll r) {
    if (cur == nullptr)
        return DEFAULT;
    ll m = (l + r) / 2;
    if (r - l == 1)
        return cur->line(x);
    // min -> min f(x) , max -> max f(x)
    else if (x < m)
        return min(cur->line(x), query(x, cur->left, l, m));
    else
        return min(cur->line(x), query(x, cur->right, m, r));
}
