#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#define int long long
//#define double long double
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace __gnu_pbds;
using namespace std;
template<typename T>
using ordered_set=tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
bool valid(long long i,long long j,long long n,long long m){return i>=0&&i<n&&j>=0&&j<m;}
long long mul(long long x,long long y,const long long&mod){return ((x%mod)*(y%mod))%mod;}
long long add(long long x,long long y,const long long&mod){return (((x%mod)+(y%mod))%mod+mod)%mod;}
int SafeMul(int a,int b,int m){if(b==0)return 0;int res = SafeMul(a,b/2,m);res = add(res,res,m);if(b&1)return add(res,a,m);else return res;}
long long fast_power(long long base,long long power,const long long &m=INT64_MAX){if (power == 1 || power == 0)return base * power + (!power);long long res = (fast_power(base, power / 2, m) % m) % m;if (power & 1)return mul(base,mul(res,res,m),m);else return mul(res,res,m);}
int log2_floor(long long i) {return i ? __builtin_clzll(1) - __builtin_clzll(i) : 0;}
int power_of_2(int n){ return __builtin_popcountll(n)==1;}
bool line_checking(int a1,int b1,int a2,int b2,int a3,int b3) { return (b2-b1)*(a2-a3)==(b2-b3)*(a2-a1); }
pair<int,int> rotate(int i,int j,int n){ return make_pair(j,n-1-i); }
const int N = 5e5+5;
const int mod=1e9+7;
//const int mod = 998244353;
const long long inf=2e18;
int dx[]{1,-1,0,0,1,1,-1,-1};
int dy[]{0,0,1,-1,1,-1,1,-1};
const double pi=3.14159265350979323846,eps=1e-8;
/*==============================================  KHALWSH  ==============================================*/
bool probablyPrimeFermat(int n, int iter=500) {
    if (n < 4)
        return n == 2 || n == 3 ;

    for (int i = 0; i < iter; i++) {
        int a = 2 + rand() % (n - 3);
        if (fast_power(a, n - 1, n) != 1)
            return false;
    }
    return true;
}
int handle(int n,int g){
    return g/__gcd(n,g);
}
int arr[N];
const int k = 20;
int sp[k][N];
int n;
int gcd(int a,int b){
    if(b==0)return a;
    return gcd(b,a%b);
}
void build() {
    for (int i = 0; i < n; i++) {
        sp[0][i] = arr[i];
    }
    for (int i = 1; i < k; i++) {
        for (int j = 0; j + (1 << i) <= n; j++) {
            sp[i][j] = __gcd(sp[i - 1][j], sp[i - 1][j + (1 << (i - 1))]);
        }
    }
}

int query(int l,int r) {
    int lg = log2_floor(r - l + 1);
    return __gcd(sp[lg][l], sp[lg][r - (1 << (lg)) + 1]);
}

signed main() {
    khaled
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        build();
        int res = query(0, n - 1);
        for (int i = 0; i < n; i++) {
            if (!i) {
                int g = query(1, n - 1);
                if(probablyPrimeFermat(g/arr[i]) && g % arr[i] == 0|arr[i] % g == 0)
                    res = max(res,g);
            } else if (i == n - 1) {
                int g = query(0, n - 2);
                if(probablyPrimeFermat(g/arr[i]) && g % arr[i] == 0|arr[i] % g == 0)
                    res = max(res,g);
            } else {
                int g = __gcd(query(0, i - 1), query(i + 1, n - 1));
                if(probablyPrimeFermat(g/arr[i]) && g % arr[i] == 0|arr[i] % g == 0)
                    res = max(res,g);
            }
        }
        cout << res << line;
    }
}
