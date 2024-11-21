void KMP(string str, string pat)
{
    int n = str.length();
    int m = pat.length();
    vector<int> longestPrefix = fail_fun(pat);

    for(int i = 0, k = 0; i < n; i++) {
        // as long as we can't add one more character in k, get best next prefix
        while (k > 0 && pat[k] != str[i])
            k = longestPrefix[k - 1];

        // if we match character in the pattern, move in pattern
        if (pat[k] == str[i])
            k++;

        // if we matched, print it and let's find one more matching
        if (k == m) {
            cout<<i - m + 1<<"\n";
            k = longestPrefix[k - 1];    // fail to next best suffix
        }
    }
}

vector<int> fail_fun(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}
