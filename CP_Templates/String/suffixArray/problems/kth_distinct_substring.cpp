/*
Problem link: https://cses.fi/problemset/task/2108/
You are given a string of length n.
If all of its distinct substrings are ordered lexicographically, what is the kth smallest of them?
*/
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    string s; cin >> s;
    int n = s.size();
    auto p = buildSuffixArray(s);
    auto lcp = Kasai(s,p);
    ll k; cin >> k;
    if(k <= n - p[0]){ cout << s.substr(p[0], k); return 0; }
    k -= n - p[0];
    for(int i = 0; i < lcp.size(); ++i){
        int len = n - p[i+1] - lcp[i];
        if(k <= len){ cout << s.substr(p[i+1],k+lcp[i]); return 0; }
        k -= len;
    }
}
