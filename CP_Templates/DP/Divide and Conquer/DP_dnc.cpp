const int N = 5002;
int n,k;
ll dp[2][N] , p[N] , c[N][N];
int cost(int l , int r){ return; } // cost function
void dnc(int ind , int l , int r , int optl , int optr){
    if(l > r) return;
    pair<ll,int> bst{LLONG_MAX,-1};
    int m = (l+r)/2;
    for(int opt = optl; opt <= optr; ++opt){
        /*
            In case 0-base
            bst = min(bst , { (opt ? dp[ind^1][opt-1] : 0) + c(opt,m) , opt });
        */
        bst = min(bst , {dp[ind^1][opt-1] + c(opt,m) , opt} );
    }
    dp[ind][m] = bst.f;
    int opt = bst.s;
    dnc(ind,l,m-1,optl,opt);
    dnc(ind,m+1,r,opt,optr);
}
void run(){
    for(int i = 1; i <= n;++i) dp[0][i] = c[1][i];
    for(int x = 1; x < k; ++x){
        dnc(x&1,1,n,1,n);
    }
}
