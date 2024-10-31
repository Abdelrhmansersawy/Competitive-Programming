auto cost = [&](int l , int opt , int r){
    // Degenerated case: opt+1 > r
    // dp[l][opt] , dp[opt+1][r] + [optinal] cost(l,r) 
};

for(int l = 0; l < n; ++l){
    int opt = l;
    // Initialize dp[l][l]
    for(int r = l+1; r < n; ++r){
        while(opt < r && cost(l,opt,r) >= cost(l,opt+1,r)) ++opt; // change >= to <=, if u need to find maximum
        dp[l][r] = cost(l,opt,r);
    }
}
