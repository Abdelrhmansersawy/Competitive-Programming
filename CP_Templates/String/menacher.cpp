vector<int> menacher(string &s) {
    string arr;
    for (int i = 0; i < s.size(); i++) {
        arr.push_back('#');
        arr.push_back(s[i]);
    }
    arr.push_back('#');
    vector<int> dp(arr.size());
    int left = 0;
    int right = 0;
    int lg_max = 0;
    int idx = 0;
    for (int i = 0; i < arr.size();) {
        while (left > 0 && right < arr.size() - 1 &&
               arr[left - 1] == arr[right + 1]) {
            left--;
            right++;
        }
        dp[i] = right - left + 1;
        if (lg_max < dp[i]) {
            lg_max = dp[i];
            idx = i;
        }
        int new_center = right + (i % 2 == 0 ? 1 : 0);
        for (int j = i + 1; j <= right; j++) {
            dp[j] = min(dp[i - (j - i)], 2 * (right - j) + 1);
            if (lg_max < dp[i]) {lg_max = dp[i]; idx = i; }
            if (j + dp[i - (j - i)] / 2 == right) {new_center = j; break; }
        }
        i = new_center;
        right = i + dp[i] / 2;
        left = i - dp[i] / 2;
    }
    return dp;
}
bool is_palindrome(int l , int r , vector<int> &dp){
    l *= 2; r *= 2; r += 2;
    return dp[(l + r) / 2] == (r - l + 1);
}
