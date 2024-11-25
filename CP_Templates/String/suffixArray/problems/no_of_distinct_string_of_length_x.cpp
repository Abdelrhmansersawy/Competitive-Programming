/*
Problem link: https://cses.fi/problemset/task/2110/
You are given a string of length n.
For every integer between 1, n you need to print the number of distinct substrings of that length.

*/
string s; cin >> s;
int n = s.size();
auto p = buildSuffixArray(s);
auto lcp = Kasai(s,p);

ll cnt[n+2]{};

auto upd = [&](int l , int r, int v){
if(l > r)return;
    cnt[l] += v; cnt[r+1] -= v;
};

for(int i = 0; i < lcp.size(); ++i)upd(1,lcp[i] , -1);

for(int i = 1; i <= n; ++i) cnt[i] += cnt[i-1];
for(int i = 1; i <= n; ++i) cnt[i] += n - i + 1;
for(int i = 1; i <= n; ++i) cout << cnt[i] << ' ';
