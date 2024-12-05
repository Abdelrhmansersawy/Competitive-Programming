// Helper function to transform string for Manacher's algorithm
string transform(string &s) {
    string t;
    for(auto &val : s) {
        t += '#';
        t += val;
    }
    t += '#';
    return t;
}

// Main Manacher's algorithm implementation
vector<int> build(string &s) {
    string t = transform(s);
    int n = t.size();
    vector<int> p(n, 0);
    int l = 0, r = 0;
    
    for(int i = 0; i < n; i++) {
        p[i] = (i < r) ? min(r - i, p[l + r - i]) : 1;
        while(i - p[i] >= 0 && i + p[i] < n && t[i + p[i]] == t[i - p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            r = i + p[i];
            l = i - p[i];
        }
    }
    return p;
}

// Check if substring [l,r] is palindrome using p array
bool IsPalindrome(int l, int r, vector<int>& p) {
    int center = (l + r) / 2;
    bool odd = (l % 2 == r % 2);
    int newCenter = 2 * center + !odd + 1;
    return (r - l + 1) <= (p[newCenter] - 1);
}

// Returns {start_index, end_index} of longest palindrome substring using p array
pair<int,int> LongestPalindromeSubStr(vector<int>& p) {
   int maxLength = 0;
   int start = 0, end = 0;
   int n = p.size() / 2;  // Original string length
   
   for(int i = 0; i < n; i++) {
       // Even length palindromes
       int newCenter = 2 * i + 2;
       int len = p[newCenter] - 1;
       if(len > maxLength) {
           maxLength = len;
           start = i - len/2 + 1;
           end = i + len/2;
       }
       
       // Odd length palindromes
       newCenter = 2 * i + 1;
       len = p[newCenter] - 1;
       if(len > maxLength) {
           maxLength = len;
           start = i - len/2;
           end = i + len/2;
       }
   }
   
   return {start, end};
}
