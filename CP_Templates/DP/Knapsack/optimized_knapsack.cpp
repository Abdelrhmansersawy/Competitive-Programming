/*
  Problem: For every possible sum , find the minimum number of elements that can form this sum.
  Time complexity: O(n sqrt(n))
*/
map<int,int> frq; // store the frq of every element in the array.
int dp[n + 1];
memset(dp , '?' , sizeof dp);
dp[0] = 0;
for(auto &[sz , f] : frq){
    int cost = 1;
    while(f){
        cost = min(cost , f);
        f -= cost;
        for(int sum = n; sum >= cost * sz; sum--)
            dp[sum] = min(dp[sum] , dp[sum - cost * sz] + cost);
        cost *= 2;
    }
}
