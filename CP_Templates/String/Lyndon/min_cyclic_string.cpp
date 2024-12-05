// Minimum cyclic shift of string using Duval algorithm
// Returns number of positions to shift right to get lexicographically minimum string
// Example: "cba" -> 2 (shift right 2 to get "abc")
// Time: O(n), Space: O(1)
int min_cyclic_shift(string s) {
   s += s;
   int n = s.size();
   int i = 0, shift = 0;
   
   while(i < n/2) {
       shift = i;
       int j = i + 1, k = i;
       while(j < n && s[k] <= s[j]) {
           if(s[k] < s[j]) k = i;
           else k++;
           j++;
       }
       while(i <= k) i += j - k;
   }
   
   return shift; 
}

// Usage:
/*
string s = "cba" 
int shift = min_cyclic_shift(s); // returns 2
rotate(s.begin(), s.begin() + shift, s.end()); // gets "abc"

s = "aaaa"
shift = min_cyclic_shift(s); // returns 0 (already minimum)
*/
