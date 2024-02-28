#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
#define all(v) v.begin() , v.end()
#ifndef ONLINE_JUDGE 
#define debug(x) cerr << #x << ": " << x << '\n';
#else
#define debug(x)
#endif
template<class T, int SZ> struct RangeQuery {
    int n;
    T stor[SZ][32-__builtin_clz(SZ)], id = 1;
    vector<T> a;
    T comb (T a, T b) { 
        return mul(a,b);  // associative operation
    } 
    void fill(int l, int r, int ind) {
        if (ind < 0) return;
        int m = (l+r)/2;
        T prod = id; for(int i = l; i < m; ++i) stor[i][ind] = prod = comb(a[i],prod);
        prod = id; for(int i = m; i < r; ++i) stor[i][ind] = prod = comb(prod,a[i]);
        fill(l,m,ind-1); fill(m,r,ind-1);
    }
    void init() {
        n = 1; while ((1<<n) < int(a.size())) ++n;
        a.resize(1 << n);
        fill(0,(1<<n),n-1);
    }
    T query(int l, int r) {
        if (l == r) return a[l];
        int t = 31-__builtin_clz(r^l);
        return comb(stor[l][t],stor[r][t]);
    }
};

int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif

}
