const int N = 2e5 + 9;
class BITrange {
private:
    long long m[N], c[N];
    void add(int pos, long long mVal, long long cVal) {
        for (++pos; pos <= N; pos += (pos & (-pos))) {
            m[pos - 1] += mVal;
            c[pos - 1] += cVal;
        }
    }
    long long get(int pos) {
        long long ret = 0;
        int x = pos;
        for (++pos; pos; pos -= (pos & (-pos))) {
            ret += m[pos - 1] * x + c[pos - 1];
        }
        return ret;
    }
    
public:
    void init(int n) {
        memset(m, 0, n * sizeof(m[0]));
        memset(c, 0, n * sizeof(m[0]));
    }
    void add(int st, int en, long long val) {
        if(st > en) return;
        add(st, val, -val * (st - 1));
        add(en + 1, -val, val * en);
    }
    void add(int i, ll val){ addRange(i,i,val); }
    ll getIndex(int i){ return get(i) - get(i - 1); }
};
