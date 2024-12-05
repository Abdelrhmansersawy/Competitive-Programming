// Z-Function: Returns array z where z[i] is length of longest common prefix 
// between s[0..n-1] and s[i..n-1]
// Time: O(n), Memory: O(n)
vector<int> zFunction(string s) {
   int n = s.size();
   vector<int> z(n);
   int left = 0, right = 0;
   for(int i = 1; i < n; i++) {
       if(i <= right) {
           z[i] = min(right - i + 1, z[i - left]);
       }
       while(i + z[i] < n && s[z[i]] == s[z[i] + i]) {
           z[i]++;
       }
       if(i + z[i] - 1 > right) {
           left = i;
           right = i + z[i] - 1;
       }
   }
   return z;
}
