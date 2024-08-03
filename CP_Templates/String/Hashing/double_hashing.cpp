#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
const int N = 1e6 + 9;
const int mod[] = { (int)1e9 + 7, 998244353 };
ll p[2] , pw[2][N];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int gen(int l, int r) { return rng() % (r - l + 1) + l; }
ll get(ll x , ll y){ return (x + 1) * 1e9 + y; } // return Double hashing = get(hash[0] , hash[1])
void init(){
    for(int o = 0; o < 2; o++){
        p[o] = gen(31 , 39); // Generate Base randomly
        pw[o][0] = 1;
        for(int i = 1; i < N; ++i)
            pw[o][i] = pw[o][i - 1] * p[o] % mod[o];
    }
}
vector<ll> gen_prefix(string &s){
    int n = (int) s.size();
    vector<ll> ans(n);
    ll pre[2][n];
    pre[0][0] = pre[1][0] = (s[0] - 'a' + 1);
    for(int i = 1; i < n; ++i) {
        for(int o = 0; o < 2; o++){
            pre[o][i] = (pre[o][i - 1] + (s[i] - 'a' + 1) * pw[o][i]) % mod[o];
        }
    }
    for(int i = 0; i < n; ++i)
        ans[i] = get(pre[i][0] , pre[i][1]);
    return ans;
}
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
    init();
}
