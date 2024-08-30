#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first
#define s second
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    int n  , q; cin >> n >> q;
    int a[n];
    for(int i = 0; i < n; ++i) cin >> a[i];
    int lt[n] , rg[n] , ans[q];
    vector<array<int,3>> Queries;
    for(int i = 0; i < q; ++i){
        int l , r; cin >> l >> r;
        --l; --r;
        Queries.push_back({l , r , i});
    }
    auto comb = [&](int x , int y){ return min(x , y); };
    function<void(int,int,vector<array<int,3>>)> solve = [&]( int l , int r , vector<array<int,3>> Queries){
        if(Queries.empty()) return; // just optimization
        if(l == r){
            for(auto &[L , R , ind] : Queries) ans[ind] = a[l];
            return;
        }
        int m = (l + r) / 2;
        lt[m] = a[m];  rg[m + 1] = a[m + 1];
        for(int i = m - 1; i >= l; --i) lt[i] = comb(a[i] , lt[i + 1]);
        for(int i = m + 2; i <= r; ++i) rg[i] = comb(a[i] , rg[i - 1]);
        vector<array<int,3>> tmp[2];
 
        for(auto &[L , R , ind] : Queries){
            if(L <= m && m < R){
                ans[ind] = comb(lt[L] , rg[R]);
            }else{
                tmp[L > m].push_back({L , R , ind});
            }
        }
        solve(l , m , tmp[0]); solve(m + 1 , r , tmp[1]);
    };
    solve(0 , n - 1 , Queries);
    for(int i = 0; i < q; ++i){
        cout << ans[i] << '\n';
    }
