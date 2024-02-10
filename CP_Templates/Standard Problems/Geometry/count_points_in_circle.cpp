/*
Problem link: https://atcoder.jp/contests/abc191/tasks/abc191_d 
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
int EPS = 10000 , Precision = 4;
long long read(){
    // 1.2345 --> 12345
    string s;
    cin >> s;
    int x=s.find('.');
    if(x==-1) return stoll(s+"0000");
    string one=s.substr(0,x);
    string two=s.substr(x+1);
    while(two.size()< Precision) two+="0";
    return stoll(one+two);
}
ll ceil(ll a, ll b){
    if(b < 0) a *= -1, b *= -1;
    if(a < 0) return a / b;
    else return (a + b - 1) / b;
}

ll floor(ll a, ll b){
    if(b < 0) a *= -1, b *= -1;
    if(a > 0) return a / b;
    else return (a - b + 1) / b;
}
ll BS(ll x , ll z){
    // find maximum y : y ^ 2 <= z ^ 2 - x ^ 2
    ll l = 0 , r = z , mid;
    while(l < r){
        mid = l + (r - l + 1) / 2;
        if(mid * mid <= z * z - x * x) l = mid;
        else r = mid - 1;
    }
    return l;
}
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
    ll x = read(), y = read() , r = read();
    ll l_x = floor(x - r , EPS) * EPS;
    ll r_x = ceil(x + r , EPS) * EPS;
    ll cnt = 0;
    for(ll i = l_x; i <= r_x; i += EPS){
        if(abs(i - x) > r) continue;
        ll len = BS(abs(x - i) , r);
        ll l_y = ceil(y - len , EPS);
        ll r_y = floor(y + len , EPS);\
        if(r_y >= l_y) cnt += r_y - l_y + 1;
    }
    cout << cnt;
}
