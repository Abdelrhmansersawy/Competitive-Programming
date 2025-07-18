/*
    ----------- BIT for Range Updates & Point/Range Queries -----------
    Supports:
    1. Add a value to a range [l, r]
    2. Query a point or range sum

    Uses two BITs:
    - `m` and `c` maintain coefficients for efficient range updates.
    - All operations are 0-indexed.

    Time Complexity:
    - addRange(), qry() -> O(log n)
*/

class BITrange {
private:
    vector<long long> m, c;
    int n;

    // Internal: Add mVal and cVal at position `pos`
    // Time Complexity: O(log n)
    void add(int pos, long long mVal, long long cVal) {
        for (++pos; pos <= n; pos += (pos & -pos)) {
            m[pos - 1] += mVal;
            c[pos - 1] += cVal;
        }
    }

    // Internal: Compute prefix sum up to position `pos`
    // Time Complexity: O(log n)
    long long get(int pos) {
        long long ret = 0;
        int x = pos;
        for (++pos; pos; pos -= (pos & -pos)) {
            ret += m[pos - 1] * x + c[pos - 1];
        }
        return ret;
    }

public:
    // Initialize BIT with `n` elements
    // Time Complexity: O(n)
    void init(int n) {
        this->n = n + 2; // to avoid boundary issues during updates
        m.assign(this->n, 0);
        c.assign(this->n, 0);
    }

    // Add `val` to the entire range [st, en]
    // Time Complexity: O(log n)
    void addRange(int st, int en, long long val) {
        if (st > en) return;
        add(st, val, -val * (st - 1));
        add(en + 1, -val, val * en);
    }

    // Add `val` to a single index `i`
    // Time Complexity: O(log n)
    void addIndex(int i, long long val) {
        addRange(i, i, val);
    }

    // Query sum in the range [l, r]
    // Time Complexity: O(log n)
    long long qry(int l, int r) {
        return get(r) - get(l - 1);
    }

    // Query value at index `i`
    // Time Complexity: O(log n)
    long long qry(int i) {
        return get(i) - get(i - 1);
    }
};
