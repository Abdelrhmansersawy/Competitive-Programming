// Problem link: https://cses.fi/problemset/task/2103/
pair<int,int> findPattern(const string &text, const string& pat, vector<int> &sa) {
    /*
        Count the no. of occurence of pattern "pat" into "text" into O(2log(n))
        sa: Suffix order
    */
    int n = sa.size();
    auto compare = [&](int pos) {
        return text.compare(sa[pos], pat.length(), pat);
    };
    
    // Find leftmost occurrence
    int left = 0, right = n-1;
    while(left < right) {
        int mid = left + (right - left) / 2;
        if(compare(mid) >= 0) right = mid;
        else left = mid + 1;
    }
    if(compare(left) != 0) return {-1, -1};
    int start = left;
    
    // Find rightmost occurrence
    right = n-1;
    while(left < right) {
        int mid = left + (right - left + 1) / 2;
        if(compare(mid) <= 0) left = mid;
        else right = mid - 1;
    }
    
    return {start, left};
}

\\-------------------------------------------
  auto find_string = [&](const string &pat)->pair<int,int> {
    int st = 0, ed = n;
    auto cmp = [&](int a, int b) {
        if (a == -1)
            return pat[i] < text[b + i];
        return text[a + i] < pat[i];
    };
    for (int i = 0; i < pat.size() && st < ed; i++) {
        st = lower_bound(p.begin() + st, p.begin() + ed, -1, cmp)
             - p.begin();
        ed = upper_bound(p.begin() + st, p.begin() + ed, -1, cmp)
             - p.begin();
    }
    if(st >= ed) return {-1,-1};
    return {st, ed - 1};
};
