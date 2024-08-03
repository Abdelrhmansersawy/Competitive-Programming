vector<vector<int>> buildRMQSuffixArray(string s) {
    // Build a suffix Array in O(nlog(n))
    const int ALPHA = 256;
    s += '$';
    int n = s.size();

    vector<int> p(n), c(n), cnt( max(n , ALPHA), 0);
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++) cnt[s[i]]++;
    for (int i = 1; i < ALPHA; i++) cnt[i] += cnt[i-1];
    for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
    
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if(s[p[i]] != s[p[i-1]]) classes++;
        c[p[i]] = classes - 1;
    }
    ans.emplace_back(c);
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if(pn[i] < 0) pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        
        for (int i = 0; i < n; i++) cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++) cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
        
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = { c[p[i]] , c[(p[i] + (1 << h)) % n] };
            pair<int, int> prev = { c[p[i-1]] , c[(p[i-1] + (1 << h)) % n] };
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
        ans.emplace_back(c);
    }
    p.erase(p.begin());
    return ans;
}
int LCP(int i, int j , vector<vector<int>> &c) {
    /*
        Find LCP between two suffix starts at i and j in O(log2(n))
    */
    int ans = 0;
    int n = c[0].size();
    int lg_n = c.size();
    for (int k = lg_n - 1; k >= 0; k--) {
        if (c[k][i % n] == c[k][j % n]) {
            ans += 1 << k;
            i += 1 << k;
            j += 1 << k;
        }
    }
    return ans;
}
int compare(int i, int j, int l, vector<vector<int>> &c) {
    /*
        Compare between two suffix of same starts at i and j in O(1)
    */
    int n = c[0].size();
    int k = 31 - __builtin_clz(l);
    pair<int, int> a = {c[k][i], c[k][(i+l-(1 << k))%n]};
    pair<int, int> b = {c[k][j], c[k][(j+l-(1 << k))%n]};
    return a == b ? 0 : a < b ? -1 : 1;
}
int compare(int l1 , int r1 , int l2 , int r2 , string &s , vector<vector<int>> &c){
    /*
        Compare two substring s1: [l1..r1] , s2:[l2..r2] in O(log(n))
    */
    int lcp = LCP(l1 , l2 , c);
    int len1 = r1 - l1 + 1;
    int len2 = r2 - l2 + 1;
    lcp = min({lcp , len1 , len2});
    if(lcp == len1 && lcp == len2) return 0; // s[l1..r1] == s[l2..r2]
    if(lcp == len1) return -1; // s[l1..r1] < s[l2..r2]
    if(lcp == len2) return 1; // s[l1..r1] > s[l2..r2]
    return s[l1 + lcp] < s[l2 + lcp] ? -1 : 1;
}
