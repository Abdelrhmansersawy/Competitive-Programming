/*
Given a string S and several frequencies Fi.
For each Fi output the number of substrings of S (the characters of substring should be contiguous)
that occur at least Fi times in S. Note, that we consider two substrings distinct
if they have distinct length, or they have distinct starting indices.
problem link: https://www.codechef.com/problems/ANUSAR


*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> buildSuffixArray(string s) {
    const int ALPHA = 256;
    s += '$';
    int n = s.size();
    vector<int> p(n), c(n);
    {
        // Optimize first phase with counting sort
        vector<int> cnt(ALPHA);
        for(auto ch : s) cnt[ch]++;
        for(int i = 1; i < ALPHA; i++) cnt[i] += cnt[i-1];
        for(int i = n-1; i >= 0; i--) p[--cnt[s[i]]] = i;
        
        c[p[0]] = 0;
        int classes = 1;
        for(int i = 1; i < n; i++) {
            if(s[p[i]] != s[p[i-1]]) classes++;
            c[p[i]] = classes - 1;
        }
    }
    
    vector<int> pn(n), cn(n);
    for(int h = 0; (1 << h) < n; ++h) {
        int len = 1 << h;
        for(int i = 0; i < n; i++) {
            pn[i] = p[i] - len;
            if(pn[i] < 0) pn[i] += n;
        }
        
        // Optimize counting sort for each phase
        vector<int> cnt(n);
        for(int i = 0; i < n; i++) cnt[c[pn[i]]]++;
        for(int i = 1; i < n; i++) cnt[i] += cnt[i-1];
        for(int i = n-1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
        
        cn[p[0]] = 0;
        int classes = 1;
        for(int i = 1; i < n; i++) {
            pair<int,int> cur = {c[p[i]], c[(p[i] + len) % n]};
            pair<int,int> prev = {c[p[i-1]], c[(p[i-1] + len) % n]};
            if(cur != prev) ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    p.erase(p.begin());
    return p;
}

vector<int> buildLCP(const string& s, const vector<int>& p) {
    int n = s.size();
    vector<int> rank(n), lcp(n-1);
    for(int i = 0; i < n; i++) rank[p[i]] = i;
    
    for(int i = 0, k = 0; i < n; i++) {
        if(rank[i] == n-1) {
            k = 0;
            continue;
        }
        int j = p[rank[i] + 1];
        while(i + k < n && j + k < n && s[i+k] == s[j+k]) k++;
        lcp[rank[i]] = k;
        if(k) k--;
    }
    return lcp;
}

// Optimized stack-based nearest smaller element
pair<vector<int>, vector<int>> getMinBounds(const vector<int>& arr) {
    int n = arr.size();
    vector<int> left(n), right(n);
    vector<int> st;
    st.reserve(n);
    
    // Get left bounds
    for(int i = 0; i < n; i++) {
        while(!st.empty() && arr[st.back()] > arr[i]) st.pop_back();
        left[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }
    
    // Clear stack for right bounds
    st.clear();
    
    // Get right bounds
    for(int i = n-1; i >= 0; i--) {
        while(!st.empty() && arr[st.back()] >= arr[i]) st.pop_back();
        right[i] = st.empty() ? n : st.back();
        st.push_back(i);
    }
    
    return {left, right};
}

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    
    auto p = buildSuffixArray(s);
    auto lcp = buildLCP(s, p);
    auto [L, R] = getMinBounds(lcp);
    
    // Pre-allocate vectors to avoid resizing
    vector<ll> frq(n+9);
    vector<vector<int>> group(n+1);
    for(int i = 0; i < n+1; i++) group[i].reserve(n/2);
    
    // Group LCP values
    for(int i = 0; i < (int)lcp.size(); ++i) {
        group[lcp[i]].push_back(i);
    }
    
    // Calculate frequencies
    for(int len = n; len > 0; --len) {
        for(size_t j = 0; j < group[len].size();) {
            int x = group[len][j];
            int l = L[x], r = R[x];
            int f = r - l;
            int minh = len;
            
            if(l >= 0) minh = min(minh, len - lcp[l]);
            if(r < (int)lcp.size()) minh = min(minh, len - lcp[r]);
            
            frq[f] += 1LL * f * minh;
            
            // Skip processed indices
            while(j < group[len].size() && group[len][j] <= r) ++j;
        }
    }
    
    // Calculate cumulative frequencies
    for(int i = n-1; i > 1; --i) frq[i] += frq[i+1];
    frq[1] = 1LL * n * (n + 1) / 2;
    
    // Process queries
    int q;
    cin >> q;
    while(q--) {
        int x;
        cin >> x;
        cout << (x > s.size() ? 0 : frq[x]) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int tc;
    cin >> tc;
    while(tc--) solve();
    
    return 0;
}
