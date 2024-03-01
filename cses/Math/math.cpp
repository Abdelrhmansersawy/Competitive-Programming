//CSES MATH

//problem 1
#include <iostream>
using namespace std;
int main(){
     int T=1; cin >> T;
     while(T--)
     {
        int n,k; cin >> n >> k;
        int b = 0, a = 1, N = 0, odd = 0;
        while(n = N = n - N)
        {
            N = (N+odd)/2;
            if(k <= N) {cout << a*(2*k - odd)-b << "\n"; break;} 
            b+=a * (odd^1);
            odd^=n%2;
            a*=2;
            k-=N;
        }
     }
}

//problem 2
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 2e5 + 9, M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
ll power(int a, int b, int mod)
{
    int res = 1;
    a%=mod;
    while(b)
    {
        if(b%2) res*=a,res%=mod;
        b/=2;
        a=a*a%mod;
    }
    return res;
}
void solve()
{
    int a,b,c; cin >> a >> b ;
    cout << power(a,b,mod) << "\n";
 
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 3
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 2e5 + 9, M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
ll power(int a, int b, int mod)
{
    int res = 1;
    a%=mod;
    while(b)
    {
        if(b%2) res*=a,res%=mod;
        b/=2;
        a=a*a%mod;
    }
    return res;
}
void solve()
{
    int a,b,c; cin >> a >> b>> c ;
    cout << power(a,power(b,c,mod-1),mod) << "\n";
 
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 4
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 1e6+5 , M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
int d[N];
void seive()
{
    for(int i=1; i < N; ++i)
    {
        for(int j=i; j < N; j+=i) d[j]++;
    }
}
ll power(int a, int b, int mod)
{
    int res = 1;
    a%=mod;
    while(b)
    {
        if(b%2) res*=a,res%=mod;
        b/=2;
        a=a*a%mod;
    }
    return res;
}
void solve()
{
    int x; cin >> x ;cout << d[x] << "\n";
 
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; cin >> T;
     seive();
     while(T--)
     {
        solve();
     }
 }

 //problem 5
 #include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 1e6+1 , M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
vector<vector<int>> d(N);
vector<int> v(N);
int mp[N+1],exist[N+1];
int ans = 1;
void seive()
{
    for(int i=1; i < N; ++i)
    {
        for(int j=i; j < N; j+=i){
            if(exist[j]){
                if(exist[j] > 1 || mp[i]) ans = max(ans,i);
                else mp[i] = 1;
            }
        }
    }
}
ll power(int a, int b, int mod)
{
    int res = 1;
    a%=mod;
    while(b)
    {
        if(b%2) res*=a,res%=mod;
        b/=2;
        a=a*a%mod;
    }
    return res;
}
void solve()
{
    int n; cin >> n;
    v.resize(n);
    for(auto &i : v) {cin >> i; exist[i]++;}
    sort(v.begin(),v.end());
    seive();
    cout << ans << "\n";
    
 
 
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 6
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 1e6+1 , M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
vector<vector<int>> d(N);
vector<int> v(N);
int mp[N+1],exist[N+1];
int ans = 0;
void seive()
{
    for(int i=1; i < N; ++i)
    {
        for(int j=i; j < N; j+=i){
            if(exist[j]){
                if(exist[j] > 1 || mp[i]) ans = max(ans,i);
                else mp[i] = 1;
            }
        }
    }
}
ll power(int a, int b, int mod)
{
    int res = 1;
    a%=mod;
    while(b)
    {
        if(b%2) res*=a,res%=mod;
        b/=2;
        a=a*a%mod;
    }
    return res;
}
ll inv(ll x) {return power(x,mod-2,mod);}
void solve()
{
    int n; cin >> n;
    int idx = 2;
    for(int i=1; i*i <= n; ++i)
    {
        int u = n/i ,v = n/(i+1) % mod;
        if(u > sqrt(n)) ans += u%mod*i%mod,ans%=mod;
        u%=mod;
        ans += i*(u*(u+1) % mod  - v*(v+1)% mod)%mod * inv(2) %mod;
        ans%=mod;
        ans = (ans+mod)%mod;
    }
    cout << ans << "\n";
    
 
 
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 7
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 1e6+1 , M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
vector<vector<int>> d(N);
vector<int> v(N);
int mp[N+1],exist[N+1];
int ans = 0;
void seive()
{
    for(int i=1; i < N; ++i)
    {
        for(int j=i; j < N; j+=i){
            if(exist[j]){
                if(exist[j] > 1 || mp[i]) ans = max(ans,i);
                else mp[i] = 1;
            }
        }
    }
}
ll power(int a, int b, int mod)
{
    int res = 1;
    a%=mod;
    while(b)
    {
        if(b%2) res*=a,res%=mod;
        b/=2;
        a=a*a%mod;
    }
    return res;
}
ll inv(ll x, ll M) {return power(x,mod-2,M);}
void solve()
{
    int n; cin >> n;
    int number = 1, pprod = 1, prod = 1, sum = 1;
    for(int i=0; i < n; ++i)
    {
        int x,k; cin >> x >> k;
        prod=power(prod,k+1,mod)*power(x,pprod*(k*(k+1)/2 % (mod-1)) % (mod-1) ,mod)%mod;
        prod%=mod;
        number *= (k+1); number %= mod;
        pprod *= (k+1); pprod%=(mod-1);
        sum *= sub(power(x,k+1,mod) , 1) * inv(sub(x,1),mod)%mod; sum%=mod;
    }
    cout << number << " " << sum << " " << prod << "\n";
    
 
 
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 8
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 1e6+1 , M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
vector<vector<int>> d(N);
vector<int> v(N);
int mp[N+1],exist[N+1];
int ans = 0;
void seive()
{
    for(int i=1; i < N; ++i)
    {
        for(int j=i; j < N; j+=i){
            if(exist[j]){
                if(exist[j] > 1 || mp[i]) ans = max(ans,i);
                else mp[i] = 1;
            }
        }
    }
}
ll power(int a, int b, int mod)
{
    int res = 1;
    a%=mod;
    while(b)
    {
        if(b%2) res*=a,res%=mod;
        b/=2;
        a=a*a%mod;
    }
    return res;
}
ll inv(ll x, ll M) {return power(x,mod-2,M);}
void solve()
{
    int n,k; cin >> n >> k;
    vector<int> v(k);
    for(int i=0; i < k; ++i) cin >> v[i];
    vector<int> one(101);
    one[0] = -1;
    for(int i=1; i <= 100; ++i) one[i] = -one[i-1];  
    int ans = 0;
    for(int i=1; i < (1 << k); ++i)
    {
        int prod = 1;
        int idx = one[__builtin_popcount(i)];
        for(int j=0; j < k; ++j)
        {
            if(i & (1 << j))
            {
                if(log10(prod) + log10(v[j]) > log10(n)) {idx = 0;break;}
                prod*=v[j];
            }
        }
        ans+= n/prod*idx;
    }
    cout << ans << "\n";
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 9
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 1e6+1 , M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
int d[N];
vector<int> v(N);
int mp[N+1],exist[N+1];
int ans = 0;
vector<int> primes(N,1);
ll lpf[N],mobius[N];
 
void least_prime_factor()
{
    for(int i=2;i<N;i++)
    {
        if(!lpf[i])
        {
            for(int j=i;j<N;j+=i)
            {
                if(!lpf[j]) lpf[j]=i;
            }
        }
    }
}
 
void Mobius()
{
    for(int i=1;i<N;i++) 
    {
        if(i==1) mobius[i]=1;
        else 
        {
            if(lpf[i/lpf[i]]==lpf[i]) mobius[i]=0;
            else mobius[i]=-1*mobius[i/lpf[i]];
        }
    }
}
 
void seive()
{
    for(int i=1; i < N; ++i)
    {
        for(int j=i; j < N; j+=i) if(exist[j]) d[i]+=exist[j];
    }
}
ll power(int a, int b, int mod)
{
    int res = 1;
    a%=mod;
    while(b)
    {
        if(b%2) res*=a,res%=mod;
        b/=2;
        a=a*a%mod;
    }
    return res;
}
ll inv(ll x, ll M) {return power(x,mod-2,M);}
void solve()
{
    int n; cin >> n;
    vector<int> v(n);
    for(int i=0; i < n; ++i)
    {
        cin >> v[i];
        exist[v[i]]++;
    }
    least_prime_factor();
    Mobius();
    seive();
    int ans = 0;
    for(int i=1; i <= N; ++i)
    {
        ans+=mobius[i] * d[i]*(d[i]-1)/2;
    }
    cout << ans << "\n";
 
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 10
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 1e6+1 , M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
int d[N];
vector<int> v(N);
int mp[N+1],exist[N+1];
int ans = 0;
vector<int> primes(N,1);
ll lpf[N],mobius[N];
 
void least_prime_factor()
{
    for(int i=2;i<N;i++)
    {
        if(!lpf[i])
        {
            for(int j=i;j<N;j+=i)
            {
                if(!lpf[j]) lpf[j]=i;
            }
        }
    }
}
 
void Mobius()
{
    for(int i=1;i<N;i++) 
    {
        if(i==1) mobius[i]=1;
        else 
        {
            if(lpf[i/lpf[i]]==lpf[i]) mobius[i]=0;
            else mobius[i]=-1*mobius[i/lpf[i]];
        }
    }
}
 
void seive()
{
    for(int i=1; i < N; ++i)
    {
        for(int j=i; j < N; j+=i) if(exist[j]) d[i]+=exist[j];
    }
}
ll power(int a, int b, int mod)
{
    int res = 1;
    a%=mod;
    while(b)
    {
        if(b%2) res*=a,res%=mod;
        b/=2;
        a=a*a%mod;
    }
    return res;
}
ll inv(ll x, ll M) {return power(x,mod-2,M);}
int fac[N+1];
void solve()
{
    int n; cin >> n;
    fac[0] = 1;
    for(int i=1; i <= N; ++i) fac[i] = fac[i-1]*i%mod;
    for(int i=0; i < n; ++i)
    {
        int a,b; cin >> a >> b;
        cout << fac[a]*inv(fac[b],mod)%mod*inv(fac[a-b],mod)%mod << "\n";
    }
 
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 11
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 1e6+1 , M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
int d[N];
vector<int> v(N);
int mp[N+1],exist[N+1];
int ans = 0;
vector<int> primes(N,1);
ll lpf[N],mobius[N];
 
void least_prime_factor()
{
    for(int i=2;i<N;i++)
    {
        if(!lpf[i])
        {
            for(int j=i;j<N;j+=i)
            {
                if(!lpf[j]) lpf[j]=i;
            }
        }
    }
}
 
void Mobius()
{
    for(int i=1;i<N;i++) 
    {
        if(i==1) mobius[i]=1;
        else 
        {
            if(lpf[i/lpf[i]]==lpf[i]) mobius[i]=0;
            else mobius[i]=-1*mobius[i/lpf[i]];
        }
    }
}
 
void seive()
{
    for(int i=1; i < N; ++i)
    {
        for(int j=i; j < N; j+=i) if(exist[j]) d[i]+=exist[j];
    }
}
ll power(int a, int b, int mod)
{
    int res = 1;
    a%=mod;
    while(b)
    {
        if(b%2) res*=a,res%=mod;
        b/=2;
        a=a*a%mod;
    }
    return res;
}
ll inv(ll x, ll M) {return power(x,mod-2,M);}
int fac[N+1];
int freq[1000];
void solve()
{
    int n; string s; cin >> s; 
    n=s.length();
    fac[0] = 1;
    for(int i=1; i <= N; ++i) fac[i] = fac[i-1]*i%mod;
    for(int i=0; i < n; ++i) freq[s[i]]++;
    int div = 1;
    for(int i='a'; i <= 'z'; ++i) div = div * fac[freq[i]]%mod;
    cout << fac[n]*inv(div,mod)%mod << "\n";
 
    
 
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 12
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 2e6+1 , M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
int d[N];
vector<int> v(N);
int mp[N+1],exist[N+1];
int ans = 0;
vector<int> primes(N,1);
ll lpf[N],mobius[N];
 
void least_prime_factor()
{
    for(int i=2;i<N;i++)
    {
        if(!lpf[i])
        {
            for(int j=i;j<N;j+=i)
            {
                if(!lpf[j]) lpf[j]=i;
            }
        }
    }
}
 
void Mobius()
{
    for(int i=1;i<N;i++) 
    {
        if(i==1) mobius[i]=1;
        else 
        {
            if(lpf[i/lpf[i]]==lpf[i]) mobius[i]=0;
            else mobius[i]=-1*mobius[i/lpf[i]];
        }
    }
}
 
void seive()
{
    for(int i=1; i < N; ++i)
    {
        for(int j=i; j < N; j+=i) if(exist[j]) d[i]+=exist[j];
    }
}
ll power(int a, int b, int mod)
{
    int res = 1;
    a%=mod;
    while(b)
    {
        if(b%2) res*=a,res%=mod;
        b/=2;
        a=a*a%mod;
    }
    return res;
}
ll inv(ll x, ll M) {return power(x,mod-2,M);}
int fac[N+1];
int freq[1000];
void solve()
{
    int n,m; cin >> n >> m;
    fac[0] = 1;
    for(int i=1; i <= N; ++i) fac[i] = fac[i-1]*i%mod;
    cout << fac[n+m-1] * inv(fac[m],mod)%mod * inv(fac[n-1],mod)%mod << "\n";
 
 
    
 
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 13
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 2e6+1 , M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
int d[N];
vector<int> v(N);
int mp[N+1],exist[N+1];
int ans = 0;
vector<int> primes(N,1);
ll lpf[N],mobius[N];
 
void least_prime_factor()
{
    for(int i=2;i<N;i++)
    {
        if(!lpf[i])
        {
            for(int j=i;j<N;j+=i)
            {
                if(!lpf[j]) lpf[j]=i;
            }
        }
    }
}
 
void Mobius()
{
    for(int i=1;i<N;i++) 
    {
        if(i==1) mobius[i]=1;
        else 
        {
            if(lpf[i/lpf[i]]==lpf[i]) mobius[i]=0;
            else mobius[i]=-1*mobius[i/lpf[i]];
        }
    }
}
 
void seive()
{
    for(int i=1; i < N; ++i)
    {
        for(int j=i; j < N; j+=i) if(exist[j]) d[i]+=exist[j];
    }
}
ll power(int a, int b, int mod)
{
    int res = 1;
    a%=mod;
    while(b)
    {
        if(b%2) res*=a,res%=mod;
        b/=2;
        a=a*a%mod;
    }
    return res;
}
ll inv(ll x, ll M) {return power(x,mod-2,M);}
int fac[N+1];
int freq[1000];
ll c(int n, int k) 
{
    return fac[n] * inv(fac[k],mod) %mod * inv(fac[n-k],mod) % mod;
}
void solve()
{
    int n,m; cin >> n;
    fac[0] = 1;
    for(int i=1; i <= N; ++i) fac[i] = fac[i-1]*i%mod;
    int ans = 0;
    int s = 1;
    d[0] = 0;
    d[1]  = 1;
    for(int i=2; i < n; ++i)
    {
        d[i] = (d[i-1] + d[i-2])%mod * i %mod;
        
    }
    cout << d[n-1] << "\n";
 
 
    
 
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 14
    #include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 2e6+1 , M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
int d[N];
vector<int> v(N);
int mp[N+1],exist[N+1];
int ans = 0;
vector<int> primes(N,1);
ll lpf[N],mobius[N];
 
void least_prime_factor()
{
    for(int i=2;i<N;i++)
    {
        if(!lpf[i])
        {
            for(int j=i;j<N;j+=i)
            {
                if(!lpf[j]) lpf[j]=i;
            }
        }
    }
}
 
void Mobius()
{
    for(int i=1;i<N;i++) 
    {
        if(i==1) mobius[i]=1;
        else 
        {
            if(lpf[i/lpf[i]]==lpf[i]) mobius[i]=0;
            else mobius[i]=-1*mobius[i/lpf[i]];
        }
    }
}
 
void seive()
{
    for(int i=1; i < N; ++i)
    {
        for(int j=i; j < N; j+=i) if(exist[j]) d[i]+=exist[j];
    }
}
ll power(int a, int b, int mod)
{
    int res = 1;
    a%=mod;
    while(b)
    {
        if(b%2) res*=a,res%=mod;
        b/=2;
        a=a*a%mod;
    }
    return res;
}
ll inv(ll x, ll M) {return power(x,mod-2,M);}
int fac[N+1];
int freq[1000];
ll c(int n, int k) 
{
    return fac[n] * inv(fac[k],mod) %mod * inv(fac[n-k],mod) % mod;
}
void solve()
{
    int n; cin >> n;
    if(n%2) return void(cout << 0 << "\n");
    fac[0] = 1;
    for(int i=1; i <= N; ++i) fac[i] = fac[i-1]*i%mod;
    cout << inv(n/2+1,mod) * c(n,n/2)%mod << "\n";
 
 
    
 
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 15
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 2e6+10 , M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
int d[N];
vector<int> v(N);
int mp[N+1],exist[N+1];
int ans = 0;
vector<int> primes(N,1);
ll lpf[N],mobius[N];
 
void least_prime_factor()
{
    for(int i=2;i<N;i++)
    {
        if(!lpf[i])
        {
            for(int j=i;j<N;j+=i)
            {
                if(!lpf[j]) lpf[j]=i;
            }
        }
    }
}
 
void Mobius()
{
    for(int i=1;i<N;i++) 
    {
        if(i==1) mobius[i]=1;
        else 
        {
            if(lpf[i/lpf[i]]==lpf[i]) mobius[i]=0;
            else mobius[i]=-1*mobius[i/lpf[i]];
        }
    }
}
 
void seive()
{
    for(int i=1; i < N; ++i)
    {
        for(int j=i; j < N; j+=i) if(exist[j]) d[i]+=exist[j];
    }
}
ll power(int a, int b, int mod)
{
    int res = 1;
    a%=mod;
    while(b)
    {
        if(b%2) res*=a,res%=mod;
        b/=2;
        a=a*a%mod;
    }
    return res;
}
ll inv(ll x, ll M) {return power(x,mod-2,M);}
int fac[N+1];
int freq[1000];
ll c(int n, int k) 
{
    return fac[n] * inv(fac[k],mod) %mod * inv(fac[n-k],mod) % mod;
}
void solve()
{
    int n; cin >> n;
    string s; cin >> s;
    int k = 0;
    fac[0] = 1;
    for(int i=1; i < N; ++i) fac[i] = i *fac[i-1] %mod; 
    for(int i=0; i < s.length(); ++i)
    {
        if(s[i] == '(') k++;
        else k--;
        if(k < 0) return void(cout << 0 << "\n");
    }
    n-=k + s.length();
    if(n%2) return void(cout << 0 << "\n");
    cout << (c(n + k, n/2)  - c(n+k,n/2 -1) + mod)%mod; 
    
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 16
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 2e6+10 , M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
int d[N];
vector<int> v(N);
int mp[N+1],exist[N+1];
int ans = 0;
vector<int> primes(N,1);
ll lpf[N],mobius[N];
 
void least_prime_factor()
{
    for(int i=2;i<N;i++)
    {
        if(!lpf[i])
        {
            for(int j=i;j<N;j+=i)
            {
                if(!lpf[j]) lpf[j]=i;
            }
        }
    }
}
 
void Mobius()
{
    for(int i=1;i<N;i++) 
    {
        if(i==1) mobius[i]=1;
        else 
        {
            if(lpf[i/lpf[i]]==lpf[i]) mobius[i]=0;
            else mobius[i]=-1*mobius[i/lpf[i]];
        }
    }
}
 
void seive()
{
    for(int i=1; i < N; ++i)
    {
        for(int j=i; j < N; j+=i) if(exist[j]) d[i]+=exist[j];
    }
}
ll power(int a, int b, int mod)
{
    int res = 1;
    a%=mod;
    while(b)
    {
        if(b%2) res*=a,res%=mod;
        b/=2;
        a=a*a%mod;
    }
    return res;
}
ll inv(ll x, ll M) {return power(x,mod-2,M);}
int fac[N+1];
int freq[1000];
ll c(int n, int k) 
{
    return fac[n] * inv(fac[k],mod) %mod * inv(fac[n-k],mod) % mod;
}
bitset<N+1> b1,b2,b,bb;
void solve()
{
    int n,m; cin >> n >> m;
    int ans = 0;
    for(int i=1; i <= n; ++i)
    {
        ans = add(ans,power(m,__gcd(i,n),mod) * inv(n,mod)%mod);
    }
    cout << ans << "\n";
    
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 17
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 2e6+10 , M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
int d[N];
vector<int> v(N);
int mp[N+1],exist[N+1];
int ans = 0;
vector<int> primes(N,1);
ll lpf[N],mobius[N];
 
void least_prime_factor()
{
    for(int i=2;i<N;i++)
    {
        if(!lpf[i])
        {
            for(int j=i;j<N;j+=i)
            {
                if(!lpf[j]) lpf[j]=i;
            }
        }
    }
}
 
void Mobius()
{
    for(int i=1;i<N;i++) 
    {
        if(i==1) mobius[i]=1;
        else 
        {
            if(lpf[i/lpf[i]]==lpf[i]) mobius[i]=0;
            else mobius[i]=-1*mobius[i/lpf[i]];
        }
    }
}
 
void seive()
{
    for(int i=1; i < N; ++i)
    {
        for(int j=i; j < N; j+=i) if(exist[j]) d[i]+=exist[j];
    }
}
ll power(int a, int b, int mod)
{
    int res = 1;
    a%=mod;
    while(b)
    {
        if(b%2) res*=a,res%=mod;
        b/=2;
        a=a*a%mod;
    }
    return res;
}
ll inv(ll x, ll M) {return power(x,mod-2,M)%mod;}
int fac[N+1];
int freq[1000];
ll c(int n, int k) 
{
    return fac[n] * inv(fac[k],mod) %mod * inv(fac[n-k],mod) % mod;
}
bitset<N+1> b1,b2,b,bb;
void solve()
{
    int n; cin >> n;
    int sq = n*n;
    int ans = power(2,sq,mod)%mod;
    ans += 2*power(2,(sq + 3)/4,mod)%mod;
    ans%=mod;
    ans+=power(2,(sq + 1)/2,mod)%mod;
    ans%=mod;
    cout << ans * inv(4,mod)%mod << "\n";
    
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 18
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 2e5 + 9, M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
struct matrix{
    ll a[2][2];
    matrix operator *(matrix other)
    {
        matrix product{{{0,0},{0,0}}};
        for(int i=0; i < 2; ++i)
        {
            for(int j=0; j < 2; ++j)
            {
                for(int k=0; k < 2; ++k)
                {
                    product.a[i][k]+=a[i][j]*other.a[j][k]%mod;
                    product.a[i][k]%=mod;
                }
            }
        }
        return product;
    }
    matrix operator %(ll other)
    {
        matrix b;
        for(int i=0; i < 2 ;++i)
            for(int j=0; j < 2; ++j) b.a[i][j]=a[i][j]%other;
        return b;
    }
};
matrix expow(matrix a, long long n)
{
    matrix res = {{{1,0},{0,1}}};
    while(n > 0)
    {
        if(n%2 == 1) res=res*a%mod;
        n/=2;
        a=a*a%mod;
    }
    return res;
}
void solve()
{
     int n;
     cin >> n;
    matrix x = {{{0,1},{1,1}}};
    matrix y = expow(x,n);
    cout << setprecision(10) << fixed << y.a[0][1] << "\n";
    
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 19
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 2e5 + 9, M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
struct matrix{
    ll a[6][6] = {};
    matrix operator *(matrix other)
    {
        matrix product;
        for(int i=0; i < 6; ++i)
        {
            for(int j=0; j < 6; ++j)
            {
                for(int k=0; k < 6; ++k)
                {
                    product.a[i][k]+=a[i][j]*other.a[j][k]%mod;
                    product.a[i][k]%=mod;
                }
            }
        }
        return product;
    }
    matrix operator %(ll other)
    {
        matrix b;
        for(int i=0; i < 6; ++i)
            for(int j=0; j < 6; ++j) b.a[i][j]=a[i][j]%other;
        return b;
    }
};
 
matrix expow(matrix a, long long n)
{
    matrix res;
    for(int i=0; i < 6; ++i) res.a[i][i] = 1;
    while(n > 0)
    {
        if(n%2) res=res*a%mod;
        n/=2;
        a=a*a%mod;
    }
    return res;
}
void solve()
{
    int n;
    cin >> n;
    matrix x;
    for(int i=0; i < 5; ++i)
         x.a[i][i+1] = 1;
    for(int i=0; i < 6; ++i)
        x.a[5][i] = 1;
    matrix y = expow(x,n);
    cout << setprecision(10) << fixed << y.a[5][5] << "\n";
    
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 20
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 2e5 + 9, M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
struct Mat{
    vector<vector<ll>>mat;
    ll row , col;
 
    Mat(ll _r , ll _c){
        row = _r;
        col = _c;
        mat.resize(row , vector<ll>(col, 0ll));
    };
 
    Mat operator *(const Mat& b){
        Mat Product(row , b.col);
        assert(col==b.row);
        for(int i=0;i<row;i++){
            for(int k=0;k<col;k++){
                if(mat[i][k]!=0){
                    for(int j=0;j<b.col;j++){
                        Product.mat[i][j] += (mat[i][k]*b.mat[k][j])%mod;
                        Product.mat[i][j] %= mod;
                    }
                }
            }
        }
        return Product;
    }
};
 
Mat power(Mat a , ll b){
    Mat res(a.row , a.col);
    for(int i=0;i<res.row;i++) res.mat[i][i] = 1;
    while(b>0){
        if(b&1){
            res = res*a;
        }
        a = a*a;
        b>>=1;
    }
    return res;
}
void solve()
{
    int n,m,k; cin >> n >> m >> k;
    Mat u = Mat(n,n);
    for(int i=0; i < m; ++i)
    {
        int a,b; cin >> a >> b;
        u.mat[a-1][b-1]++;
    }
    u = power(u,k);
    cout << u.mat[0][n-1] << "\n";
 
    
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 21
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 2e5 + 9, M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 4 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
struct Mat{
    vector<vector<ll>>mat;
    ll row , col;
 
    Mat(ll _r , ll _c){
        row = _r;
        col = _c;
        mat.resize(row , vector<ll>(col, OOLL));
    };
 
    Mat operator *(const Mat& b){
        Mat Product(row , b.col);
        assert(col==b.row);
        for(int i=0;i<row;i++){
            for(int k=0;k<col;k++){
                    for(int j=0;j<b.col;j++){
                        Product.mat[i][j] = min(Product.mat[i][j],(mat[i][k]+b.mat[k][j]));
                    }
            }
        }
        return Product;
    }
};
 
Mat power(Mat a , ll b){
    Mat res(a.row , a.col);
    for(int i=0;i<res.row;i++) 
        res.mat[i][i] = 0;
    while(b>0){
        if(b&1){
            res = res*a;
        }
        a = a*a;
        b>>=1;
    }
    return res;
}
void solve()
{
    int n,m,k; cin >> n >> m >> k;
    Mat u = Mat(n,n);
    for(int i=0; i < m; ++i)
    {
        int a,b,c; cin >> a >> b >> c;
        u.mat[a-1][b-1]=min(c,u.mat[a-1][b-1]);
    }
    u = power(u,k);
 
    (u.mat[0][n-1] < OOLL) ? cout << u.mat[0][n-1] << "\n" : cout << "-1\n";
 
    
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }
 }
 //problem 22
 #include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 2e5 + 9, M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
double dp[1000][601] = {};
void solve()
{
   int n,a,b; cin >> n >> a >> b;
   dp[0][0] = 1;
   for(int i=0; i < n; ++i)
   {
      for(int j=0; j <= 600; ++j)
      {
         for(int k=1; k <= 6; ++k) dp[i+1][j+k] += dp[i][j] *1.0/6;
      }
   }
   int sum1 = 0;
   double sum2 = 0;
   for(int i=a; i <= b; ++i) sum2+=dp[n][i];
   cout << setprecision(6) <<fixed << sum2 << "\n";
 
 
 
 
    
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 23
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 2e5 + 9, M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 4 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
struct Mat{
    vector<vector<ll>>mat;
    ll row , col;
 
    Mat(ll _r , ll _c){
        row = _r;
        col = _c;
        mat.resize(row , vector<ll>(col, OOLL));
    };
 
    Mat operator *(const Mat& b){
        Mat Product(row , b.col);
        assert(col==b.row);
        for(int i=0;i<row;i++){
            for(int k=0;k<col;k++){
                    for(int j=0;j<b.col;j++){
                        Product.mat[i][j] = min(Product.mat[i][j],(mat[i][k]+b.mat[k][j]));
                    }
            }
        }
        return Product;
    }
};
 
Mat power(Mat a , ll b){
    Mat res(a.row , a.col);
    for(int i=0;i<res.row;i++) 
        res.mat[i][i] = 0;
    while(b>0){
        if(b&1){
            res = res*a;
        }
        a = a*a;
        b>>=1;
    }
    return res;
}
bool valid(int a)
{
    if(a > 7 || a < 0) return 0;
    else return 1;
}
void solve()
{
    int n; cin >> n;
    vector<vector<double>> ans(8,vector<double>(8,1));
    for(int last_i=0; last_i < 8; ++last_i)
    {
        for(int last_j=0; last_j < 8; ++last_j)
        {
            vector<vector<vector<double>>> dp(n+1,vector<vector<double>>(9,vector<double>(9,0)));
            dp[0][last_i][last_j] = 1;
            for(int k=0; k < n; ++k)
            {
                for(int i=0; i < 8; ++i)
                {
                    for(int j=0; j < 8; ++j)
                    {
                        int cnt = 0;
                        for(int idx = 0; idx < 4; ++idx)
                        {
                            if(!(valid(i+dx[idx])) || !(valid(j+dy[idx]))) continue;
                            cnt++;
                        }
                        for(int idx = 0; idx < 4; ++idx)
                        {
                            if(!(valid(i+dx[idx])) || !(valid(j+dy[idx]))) continue;
                            int new_x = i+dx[idx];
                            int new_y = j+dy[idx];
                            dp[k+1][new_x][new_y]+= (double) dp[k][i][j]/cnt;
                        }
                    }
                }
            }
            for(int i=0; i < 8; ++i)
            {
                for(int j=0; j < 8; ++j)
                {
                    ans[i][j]*=(1-dp[n][i][j]);
                }
            }
        }
    }
    long double sum = 0;
    for(int i=0; i < 8; ++i)
    {
        for(int j=0; j < 8; ++j) sum+=ans[i][j];
    }
    cout << setprecision(6) << fixed << sum << "\n";
 
 
 
    
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 24

//inclusin and exlusion
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 2e5 + 9, M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
void solve()
{
   int n,k; cin >> n >> k;
   long double ans = 0;
   for(int i=1; i <= k; ++i)
   {
      ans+=1.0 * i * (pow(1.0 * i/k,n) - pow(1.0 * (i-1)/k, n));
   }
   cout << setprecision(6) << fixed << ans << "\n";
 
 
 
    
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }
}
//dp 
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 2e5 + 9, M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
double dp[1000][601] = {};
void solve()
{
   int n,k; cin >> n >> k;
   for(int i=0; i < k; ++i) dp[0][i+1] = 1.0/k;
   for(int i=0; i < n; ++i)
   {
      for(int cur = 1; cur <= k; ++cur)
      {
         for(int j=1; j <= k; ++j)
         {
            dp[i+1][max(cur,j)]+=dp[i][cur]/k;
         }
      }
   }
   long double ans = 0;
   for(int i=0; i < k; ++i)
   {
      ans+=dp[n-1][i+1]*(i+1);
   }
   cout << setprecision(6) << fixed << ans << "\n";
 
 
 
 
    
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 25
// the solution is correct but the precision of c++ is not enough to handle this problem
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 2e5 + 9, M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
double dp[1000][601] = {};
void solve()
{
   int n; cin >> n;
   vector<long double> v(n);
   long double ans = 0;
   for(auto &i : v) cin >> i;
   for(int i=0; i < n; ++i)
   {
      for(int j = i+1; j < n; ++j)
      {
         for(int k=1; k <= v[j] && v[i] > k; ++k)
         {
            ans += 1/v[j] * ((v[i] - k) / v[i]);
         }
      }
   }
   cout <<setprecision(6) << fixed << ans << "\n";
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }

//problem 26
    #include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 1e6 + 9, M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
bool dp[N];
void solve()
{
    int n,k; cin >> n >> k;
    vector<int> nums(k);
    for(auto &i : nums) cin >> i;
    for(int i=1; i <= n; ++i)
    {
        for(int j=0; j < k; ++j)
        {
            //if any of the prev ones losses then I can win
            if(i >= nums[j]) dp[i]|=!dp[i-nums[j]];
        }
        cout << (dp[i] ? 'W' : 'L'); 
    }

}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 27
    #include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 1e6 + 9, M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
bool dp[N];
void solve()
{
    int n; cin >> n;
    int ans = 0;
    for(int i=0; i < n; ++i)
    {
        int x; cin >> x;
        ans^=x;
    }
    cout << (ans ? "first" : "second") << "\n";
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 28
    #include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 1e6 + 9, M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
bool dp[N];
void solve()
{
    int n; cin >> n;
    int ans = 0;
    for(int i=0; i < n; ++i)
    {
        int x; cin >> x;
        //the grundy number of x is x%4 -> G(x) = mex(G(x-1),G(x-2),G(x-3));
        //a general formula is that ans ^= mex(G(x-f(1)),G(x-f(2)),G(x-f(3)).....,G(x-f(N))) such that 
        //N is the size of f and f represents the number of piles that could be removed
        ans^=x%4;
    }
    cout << (ans ? "first" : "second") << "\n";
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 29
    #include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 1e6 + 9, M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
void solve()
{
    int n; cin >> n;
    int ans = 0;
    for(int i=0; i < n; ++i)
    {
        int x; cin >> x;
        if(i%2) ans^=x;
    }
    cout << (ans ? "first" : "second") << "\n";
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 30
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 2000, M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
int dp[N];
int mex(vector<int> v)
{
    set<ll> s;
    for(int i=0;i<v.size();i++)
    {
        s.insert(v[i]);
    }
    for(int i=0;i<1000001;i++)
    {
        if(s.count(i)==0) return i;
    }
    return 0;
}
void solve()
{
        int n; cin>>n;
        if(n>=N) cout<<"first";
        else if(dp[n]==0) cout<<"second";
        else cout<<"first";
        cout<<"\n";

}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    // calculating sprague grandy for number upto 2000 for the nmbers larger than that than answer is never zero
    dp[0]=dp[1]=dp[2]=0;
    for(int i=3;i<N;i++)
    {
        vector<int> v;
        for(int j=1;2*j<i;j++)
        {
            v.emplace_back(dp[j]^dp[i-j]);
        }
        dp[i]=mex(v);
    }
     int T=1; cin >> T;
     while(T--)
     {
        solve();
     }
}
//problem 31
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 2e5 + 9, M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
void solve()
{
    int n; cin >> n;
    vector<int> v(n);
    long long ans = 0;
    for(auto &i : v) cin >> i,ans|=i%2;
    cout << (ans?"first" : "second") << "\n";

    

}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; cin >> T;
     while(T--)
     {
        solve();
     }
}



