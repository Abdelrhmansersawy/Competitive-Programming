struct Basis {
    static const int LOG = 30;
    int b[LOG], lt[LOG], n;

    Basis() {
        memset(b, 0, sizeof b);
        memset(lt, -1, sizeof lt);
        n = 0;
    }
    void clear() {
        memset(b, 0, sizeof b);
        memset(lt, -1, sizeof lt);
        n = 0;
    }


    // Insert value with timestamp/index. Complexity: O(log A)
    void insert(int x, int id) {
        n++;
        for (int i = LOG - 1; i >= 0; --i) {
            if (!(x >> i & 1)) continue;
            if (lt[i] == -1) {
                lt[i] = id; b[i] = x; return;
            }
            if (lt[i] < id) swap(lt[i], id), swap(b[i], x);
            x ^= b[i];
        }
    }

    // Merge another basis. Complexity: O(log^2 A)
    void merge(const Basis &other) {
        n += other.n;
        for (int i = LOG - 1; i >= 0; --i) 
            if (other.lt[i] != -1) insert(other.b[i], other.lt[i]);
    }

    // Max XOR subset using indices >= L. Complexity: O(log A)
    int max_xor(int L = 0) {
        int ans = 0;
        for (int i = LOG - 1; i >= 0; --i)
            if (lt[i] >= L && (ans ^ b[i]) > ans) ans ^= b[i];
        return ans;
    }

    bool check(int x, int L = 0) {
        for (int i = LOG - 1; i >= 0; --i) {
            if (!(x >> i & 1)) continue;
            if (lt[i] < L) return false;
            x ^= b[i];
        }
        return true;
    }

    // k-th smallest XOR sum (1-based) using indices >= L. Complexity: O(log A)
    int k_th(long long k, int L = 0) {
        return kth_min(0, k, L);
    }
    
    // Get k-th minimum value of (mask ^ subset) using indices >= L. Complexity: O(log A)
    int kth_min(int mask, long long k, int L = 0) {
        int cnt = 0;
        for (int i = 0; i < LOG; ++i) if (lt[i] >= L) cnt++;
        if (k > (1LL << cnt)) return -1;

        for (int i = LOG - 1; i >= 0; --i) {
            if (lt[i] < L) continue;
            long long mid = 1LL << (--cnt);
            if (k <= mid) mask = min(mask, mask ^ b[i]);
            else mask = max(mask, mask ^ b[i]), k -= mid;
        }
        return mask;
    }

    // Count of XOR sums strictly smaller than x using indices >= L. Complexity: O(log A)
    long long rank(int x, int L = 0) {
        int cnt = 0;
        for (int i = 0; i < LOG; ++i) if (lt[i] >= L) cnt++;
        
        long long ans = 0;
        int cur = 0;
        for (int i = LOG - 1; i >= 0; --i) {
            if (lt[i] < L) continue;
            cnt--;
            if (x >> i & 1) {
                ans += (1LL << cnt);
                if (!(cur >> i & 1)) cur ^= b[i];
            } else {
                if (cur >> i & 1) cur ^= b[i];
            }
        }
        return ans;
    }
};
