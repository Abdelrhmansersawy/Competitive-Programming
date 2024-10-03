const int N = 20;
int dp[1<<N];
int comb(int x , int y){
    // depend on the problem
    return x+y;
}
void mask_to_supermask(){
    // Combing every msk to all its supermask
    for(int x = 0; x < N; ++x){
        for(int msk = 0; msk < (1<<N); msk++){
            if(msk>>x&1) dp[msk] = comb(dp[msk] , dp[msk^(1<<x)]);
        }
    }
}
void mask_to_submask(){
    //Combing every msk to all its submask
    for(int x = 0; x < N; ++x){
        for(int msk = (1<<N)-1 ; msk >= 0; msk--){
            if(msk>>x&1) dp[msk^(1<<x)] = comb(dp[msk^(1<<x)] , dp[msk]);
        }
    }
}
void supermask_to_mask(){
    // Combing every supermask to mask
    for(int x = 0; x < N; ++x){
        for(int msk = (1<<N) - 1; msk >= 0; --msk){
            if(!(msk>>x&1)) dp[msk] = comb(dp[msk] , dp[msk|(1<<x)]);
        }
    }
}
void submask_to_mask(){
    // combing every submask to mask
    for(int x = 0; x < N; ++x){
        for(int msk = 0; msk < N; ++msk){
            if(!(msk>>x&1)) dp[msk | (1<<x)] = comb(dp[msk | (1<<x)] , dp[ms]);
        }
    }
}
