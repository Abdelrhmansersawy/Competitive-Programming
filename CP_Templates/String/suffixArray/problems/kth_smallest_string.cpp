/*
Problem link: https://cses.fi/problemset/task/2109/
You are given a string of length n.
If all of its substrings (not necessarily distinct) are ordered lexicographically, what is the kth smallest of them?
*/
string s; cin >> s;
    int n = s.size();
    auto p = buildSuffixArray(s);
    auto lcp = Kasai(s,p);

    auto k_th = [&](ll k)->pair<int,int>{ // {index , length}
        if(k <= n - p[0]) return {0, k}; 
        k -= n - p[0];
        for(int i = 0; i < lcp.size(); ++i){
            int len = n - p[i+1] - lcp[i];
            if(k <= len) return {i+1 , k + lcp[i]} ;
            k -= len;
        }
        assert(false);
    };
    
    ll k; cin >> k;
    ll lo = 1 , hi = 1LL * n*(n+1) / 2 - accumulate(lcp.begin(), lcp.end(), 0LL) , md;

    while(lo < hi){
        md = lo + (hi - lo) / 2;

        auto [i, len] = k_th(md);
        
        ll sum = len;
        for(int j = 0; j < i; ++j) sum += n - p[j];
        int x = len;
        for(int j = i+1; j < n; ++j){
            x = min(x , lcp[j-1]);
            sum += x;
        }

        if(sum >= k) hi = md;
        else lo = md + 1;

    }

    auto [i,len] = k_th(lo);
    cout << s.substr(p[i] , len);
