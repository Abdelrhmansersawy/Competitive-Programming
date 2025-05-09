/*
 * Description: Container where you can add lines of the form kx+m, and query minimum values at points x.
 * Can be applied on:
    - monotonic slopes, monotonic queries
    - monotonic slopes, random queries

   Here's monotonic can be (ASCE , DESC)
 */
struct mnCHT {  // Convex Hull Trick for Minimum
    deque<long long> A; // Slopes
    deque<long long> B; // Intercepts


    bool bad(int l1, int l2, int l3) {
        return (B[l3] - B[l1]) * (long double) (A[l1] - A[l2])
                <= (B[l2] - B[l1]) * (long double) (A[l1] - A[l3]);
    }

    // Adds a line with slope `a` and intercept `b` when slopes are in ascending order
    void addASC(long long a, long long b) {
        A.push_back(a);
        B.push_back(b);
        // Remove the second last line if it's unnecessary
        while (A.size() >= 3 && bad(A.size() - 3, A.size() - 2, A.size() - 1)) {
            A.erase(A.end() - 2);
            B.erase(B.end() - 2);
        }
    }

    // Adds a line with slope `a` and intercept `b` when slopes are in descending order
    void addDESC(long long a, long long b) {
        A.push_front(a);
        B.push_front(b);
        // Remove the second line if it's unnecessary
        while (A.size() >= 3 && bad(0, 1, 2)) {
            A.erase(A.begin() + 1);
            B.erase(B.begin() + 1);
        }
    }

    // Evaluates the line at index `l` for a given `x`
    long long f(int l, long long x) {
        return A[l] * x + B[l];
    }

    // Queries the convex hull for minimum value at `x` when x-values are increasing
    long long queryASC(long long x) {
        while (A.size() >= 2 && f(0, x) > f(1, x)) {
            // Remove the front line if it's not optimal
            A.pop_front();
            B.pop_front();
        }
        if (A.empty())
            return LLONG_MAX;  // Return maximum value if no lines are left
        return f(0, x);
    }
    // Queries the convex hull for minimum value at `x` when x-values are decreasing
    long long queryDESC(long long x) {
        while (A.size() >= 2 && f(A.size() - 1, x) > f(A.size() - 2, x)) {
            // Remove the back line if it's not optimal
            A.pop_back();
            B.pop_back();
        }
        if (A.empty())
            return LLONG_MAX;  // Return maximum value if no lines are left
        return f(A.size() - 1, x);
    }

    // Optional: Query for random x-values using binary search
    long long query(long long x) {
        int lo = 0, hi = A.size() - 1;
        long long res = LLONG_MAX;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            long long val = f(mid, x);
            res = min(res, val);
            if (mid + 1 < A.size() && f(mid + 1, x) <= val) {
                lo = mid + 1;
            } else if (mid - 1 >= 0 && f(mid - 1, x) <= val) {
                hi = mid - 1;
            } else {
                break;
            }
        }
        return res;
    }
};
