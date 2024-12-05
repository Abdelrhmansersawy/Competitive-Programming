// Duval Algorithm: Lyndon Factorization
// Returns lexicographically decreasing Lyndon words
// Time: O(n), Space: O(n)
vector<string> duval(string const& s) {
   int n = s.size();
   int i = 0;
   vector<string> fact;
   
   while(i < n) {
       int j = i + 1, k = i;
       while(j < n && s[k] <= s[j]) {
           if(s[k] < s[j]) k = i;
           else k++;
           j++;
       }
       while(i <= k) {
           fact.push_back(s.substr(i, j - k));
           i += j - k;
       }
   }
   return fact;
}

// For index only version (more efficient):
vector<int> duvalIdx(string const& s) {
   int n = s.size();
   int i = 0;
   vector<int> starts;  // Starting positions
   
   while(i < n) {
       starts.push_back(i);  // Add start of current factor
       int j = i + 1, k = i;
       while(j < n && s[k] <= s[j]) {
           if(s[k] < s[j]) k = i;
           else k++;
           j++;
       }
       while(i <= k) i += j - k;
   }
   return starts;
}

// Usage example:
/*
string s = "abcab";
auto factors = duval(s);
// factors = ["abc", "ab"]

auto idx = duvalIdx(s);
// idx = [0, 3] meaning factors start at positions 0 and 3
*/
