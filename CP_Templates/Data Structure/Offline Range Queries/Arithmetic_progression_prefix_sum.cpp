const int N = 1e6 + 5;
ll d[N] , P[N];
void inc(int l , int r , int k , int b){
    // add for each x : [l , r] , v_x += k * (x - l) + b
    if(l > r) return;
    d[l + 1] += k;
    d[r + 1] -= k;

    P[l] += b;
    P[r + 1] -= b + 1LL * k * (r - l);
}
void build(){
    for(int i = 1; i < N; ++i){
        d[i] += d[i - 1];
        P[i] += P[i - 1] + d[i];
    }
}

\\ --------------------------------------------- 
const ixt N = 1e6 + 5;
ll d[N] , P[N];
void inc(int l , int r , int k , int b){
    // add for each x : [l , r] , v_x += k * (x - l + 1) + b
    if(l > r) return;
    d[l] += k;
    d[r + 1] -= k;

    P[l] += b;
    P[r + 1] -= b + 1LL * k * (r - l + 1);
}
void build(){
    for(int i = 1; i < N; ++i){
        d[i] += d[i - 1];
        P[i] += P[i - 1] + d[i];
    }
}
