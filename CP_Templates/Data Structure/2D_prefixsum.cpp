/*
Problem Link: https://cses.fi/problemset/task/1652
*/
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
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif
    int n , q; cin >> n >> q;
    int pre[n + 1][n + 1];
    memset(pre , 0 ,sizeof pre);
    rep(i ,  1,  n + 1) rep(j , 1 , n + 1){
        char x; cin >> x;
        if(x == '*') pre[i][j]++;
        pre[i][j] += pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
    }
    for(int i = 0; i < q; ++i){
        int from_x , to_x , from_y , to_y;
        cin >> from_x >> from_y;
        cin >> to_x >> to_y;
        int ans = pre[to_x][to_y] - pre[from_x - 1][to_y] - pre[to_x][from_y - 1] + pre[from_x - 1][from_y - 1];
        cout << ans << '\n';
    }
}
