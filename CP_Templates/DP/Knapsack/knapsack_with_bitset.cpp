/*
   optimized Knapsack problem work if
   n <= 2e5
   a1 + a2 + ... + an <= 1e6
   Time complexity: O(n * sqrt(n))
*/
template<int len = 1>
int solve(const vector<int> &v , int all){
    if(v.empty()) return 0;
    if(len < all)
        return solve<min(2 * len , N)>(v, all);
    map<int,int> frq;
    int Max = 0;
    for(auto &i : v) frq[i]++ , Max = max(Max , i);
    // specific for a problem, think of something that can optimize the code.
    vector<int> cur;
    for(auto &[x , f] : frq){
        int need = 1;
        while(f){
            need = min(need , f);
            f -= need;
            cur.emplace_back(need * x);
            need *= 2;
        }
    }
    bitset<len> dp;
    dp[0] = 1;
    for(auto &i : cur) dp |= (dp << i);
    // specific for a problem.
}

