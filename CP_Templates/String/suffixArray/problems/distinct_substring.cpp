int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    string s; cin >> s;
    int n = s.size();
    auto p = buildSuffixArray(s);
    auto lcp = Kasai(s , p);
    ll distinct = 1LL*n*(n+1)/2 - accumulate(lcp.begin(),lcp.end() , 0LL);
    cout << distinct << '\n';
}
