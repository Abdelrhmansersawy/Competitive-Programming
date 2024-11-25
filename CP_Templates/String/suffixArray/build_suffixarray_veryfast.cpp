vector<int> buildSuffixArray(string s) {
    int n = s.size();
    vector<int> suf, group, newGroup, tempSuf;
    int curLen = 0;
    
    tempSuf.resize(n);
    newGroup.resize(n + 1);

    auto countingSort = [&](int maxGroup) {
        vector<int> count(maxGroup + 1, 0);
        for (int i = 0; i < n; i++) 
            count[group[min(n - 1, suf[i] + curLen)]]++;
        for (int i = 1; i <= maxGroup; i++) 
            count[i] += count[i - 1];
        for (int i = n - 1; i >= 0; i--) 
            tempSuf[--count[group[min(n - 1, suf[i] + curLen)]]] = suf[i];
        for (int i = 0; i < n; i++) 
            suf[i] = tempSuf[i];
    };

    auto radixSort = [&]() {
        int maxGroup = max(n, 256);
        countingSort(maxGroup);
        curLen = 0;
        countingSort(maxGroup);
    };

    n++;
    for (int i = 0; i < n; i++) {
        suf.emplace_back(i);
        group.emplace_back(s[i]);
    }
    
    for (int len = 1;; len *= 2) {
        curLen = len;
        radixSort();
        for (int i = 1; i < n; i++) {
            newGroup[i] = newGroup[i - 1] + 
                (group[suf[i - 1]] != group[suf[i]] || 
                 group[suf[i - 1] + len] != group[suf[i] + len]);
        }
        for (int i = 0; i < n; i++)
            group[suf[i]] = newGroup[i];
        if (newGroup[n - 1] == n - 1) break;
    }
    
    return suf;
}
