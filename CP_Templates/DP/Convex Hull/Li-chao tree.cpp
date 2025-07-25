/**
 * ======================== LI CHAO TREE  =================================
 *
 * Problem: Maintain a dynamic set of functions (usually lines) and support:
 *   - Add a function (globally or over a segment [l, r]).
 *   - Query the minimum y-value at a given x ∈ domain.
 *
 * Assumptions:
 *   - All functions are linear: f(x) = a * x + b.
 *     (The classical Li Chao Tree assumes linear functions.)
 *   - However, more generally, Li Chao Tree works with any family of functions
 *     such that for all pairs f and g, there exists a point p where:
 *       f(x) ≤ g(x) for x ≤ p, and f(x) ≥ g(x) for x ≥ p.
 *     This condition ensures each pair of functions intersects at most once.
 *   - As a special case, we can handle polynomial functions of the form:
 *       f(x) = a₀ + a₁·x + a₂·x² + a₃·x³ + ... + aₖ·xᵏ
 *     if all coefficients aᵢ ≥ 0.
 *     These functions are monotonic increasing and convex over ℝ⁺,
 *     and will also satisfy the single intersection condition.
 */
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
