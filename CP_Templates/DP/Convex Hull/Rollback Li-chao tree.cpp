const ll DEFAULT = LLONG_MAX;  // Use -LLONG_MAX for max version

// A line: y = m * x + c
struct Line {
    ll m, c;
    Line(ll m = 0, ll c = DEFAULT) : m(m), c(c) {}
    ll operator()(ll x) const { return m * x + c; }
};

// Node of the Li Chao Tree
struct Node {
    Line line;
    Node *left = nullptr, *right = nullptr;
    Node(Line l = Line()) : line(l) {}
};

// Change record for rollback
struct Change {
    Node** pointer;  // Address of the pointer we modified
    Node* oldValue;  // What it was before
};

vector<Change> changeLog;        // All changes
vector<int> insertCheckpoints;   // Checkpoints before each insert()

// Record a change (before applying it)
void record(Node*& ptr) {
    changeLog.push_back({&ptr, ptr});
}

// Rollback to a specific checkpoint
void rollbackTo(int checkpoint) {
    while ((int)changeLog.size() > checkpoint) {
        auto [ptr, oldVal] = changeLog.back();
        *ptr = oldVal;
        changeLog.pop_back();
    }
}



// Public API to rollback the last insert operation
void rollbackLastInsert() {
    if (!insertCheckpoints.empty()) {
        rollbackTo(insertCheckpoints.back());
        insertCheckpoints.pop_back();
    }
}

// Insert a new line into the tree
void insert_impl(Line newLine, Node*& root, ll l, ll r) {
    if (!root) {
        record(root);
        root = new Node(newLine);
        return;
    }

    ll m = (l + r) / 2;
    bool lef = newLine(l) < root->line(l);
    bool mid = newLine(m) < root->line(m);

    if (mid)
        swap(root->line, newLine);

    if (r - l == 1)
        return;

    if (lef != mid) {
        record(root->left);
        insert_impl(newLine, root->left, l, m);
    } else {
        record(root->right);
        insert_impl(newLine, root->right, m, r);
    }
}

// Public API to start a tracked insertion
void insert(Line newLine, Node*& root, ll l, ll r) {
    insertCheckpoints.push_back(changeLog.size());
    insert_impl(newLine , root , l , r);
}

// Query the minimum value at point x
ll query(ll x, Node* root, ll l, ll r) {
    if (!root) return DEFAULT;
    ll m = (l + r) / 2;
    if (r - l == 1)
        return root->line(x);
    if (x < m)
        return min(root->line(x), query(x, root->left, l, m));
    else
        return min(root->line(x), query(x, root->right, m, r));
}
