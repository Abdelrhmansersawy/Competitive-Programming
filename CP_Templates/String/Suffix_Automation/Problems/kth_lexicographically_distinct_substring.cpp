// Problem Link: https://cses.fi/problemset/task/2108/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
#define all(v) v.begin() , v.end()
 
struct state {
    int len, link, first_pos;
    int nxt[26];
};
 
const int MAXN = 1e5+9;
state st[2 * MAXN];
ll dp[2 * MAXN];
int sz, last;
 
void sa_init() {
    st[0].len = 0;
    st[0].link = -1;
    fill(st[0].nxt, st[0].nxt + 26, -1);
    sz = 1;
    last = 0;
}
 
void sa_extend(char c, int pos) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    st[cur].first_pos = pos;
    fill(st[cur].nxt, st[cur].nxt + 26, -1);
 
 
    int p = last, letter = c - 'a';
    while (p != -1 && st[p].nxt[letter] == -1) {
        st[p].nxt[letter] = cur;
        p = st[p].link;
    }
 
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].nxt[letter];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            copy(st[q].nxt, st[q].nxt + 26, st[clone].nxt);
            st[clone].link = st[q].link;
            st[clone].first_pos = st[q].first_pos;
 
            while (p != -1 && st[p].nxt[letter] == q) {
                st[p].nxt[letter] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}
 
void build(const string &s) {
    sa_init();
    for (int i = 0; i < (int)s.size(); i++) {
        sa_extend(s[i], i);
    }
}
 
ll solve(int i){
    if(i == -1) return 0;
    ll &res = dp[i];
    if(~res) return res;
    res = 1;
    for(int j = 0; j < 26; ++j){
        res += solve(st[i].nxt[j]);
    }
    return res;
}
 
void printKth(int node , ll k){
    if(k == 0) return;
    cerr << k << endl;
    for(char ch = 'a'; ch <= 'z'; ++ch){
        int nxt = st[node].nxt[ch-'a'];
        if(nxt == -1) continue;
        if(solve(nxt) >= k){
            cout << ch;
            printKth(nxt , k - 1);
            return;
        }else k -= solve(nxt);
    }
}
 
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif
    string text; cin >> text;
    build(text);
    memset(dp,-1,sizeof dp);
 
    ll k; cin >> k;
    printKth(0, k);
}
