#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 9 , lg = 18;
int n , q , a[N];
int prec[lg][N] , msk[N];
int comb(int x , int y){ return min(x , y); }; // associative operator (eg. sum, prod, xor,or, and)
void dc(int l, int r, int lvl){
    if(l == r) return; 
    int m = (l + r) / 2;
    prec[lvl][m] = a[m]; 
    prec[lvl][m + 1] = a[m + 1];
    for(int i = m - 1; i >= l; --i) prec[lvl][i] = comb(a[i] , prec[lvl][i + 1]);
    for(int i = m + 2; i <= r; ++i) prec[lvl][i] = comb(a[i] , prec[lvl][i - 1]);
    for(int i = m + 1; i <= r; ++i) msk[i] |= (1 << lvl);
    dc(l , m , lvl + 1); dc(m + 1 , r , lvl + 1);
};
int qry(int l , int r){
    int k = __builtin_ctz(msk[l] ^ msk[r]);
    return comb(prec[k][l] , prec[k][r]);
};
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif
    cin >> n >> q;
    for(int i = 0; i < n; ++i) cin >> a[i];
    dc(0 , n , 0);
    for(int i = 0; i < q; ++i){
        int l , r; cin >> l >> r;
        --l; --r;
        if(l == r) cout << a[l] << '\n';
        else cout << qry(l , r) << '\n';
    }
}
