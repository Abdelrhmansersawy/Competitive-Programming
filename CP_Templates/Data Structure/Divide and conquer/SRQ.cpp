#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 9 , lg = 20;
int n , q , a[N];
ll prec[lg][N] , msk[N];
ll comb(ll x , ll y){ return x+y; }; // associative operator (eg. sum, prod, xor,or, and)
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
ll qry(int l , int r){
    if(l == r) return a[l];
    int k = __builtin_ctz(msk[l] ^ msk[r]);
    return comb(prec[k][l] , prec[k][r]);
};

int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);

    cin >> n >> q;
    for(int i = 0; i < n; ++i) cin >> a[i];
    dc(0 , n-1 , 0);
    for(int i = 0; i < q; ++i){
        int l , r; cin >> l >> r;
        --r;
        cout << qry(l , r) << '\n';
    }
}
