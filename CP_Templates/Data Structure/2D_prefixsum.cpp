const int N = 500, M = 500;
int pref[N][M]; // 1-base
int n , m;
int qry(int from_x , int from_y , int to_x , int to_y){
    return  pref[to_x][to_y] - pref[from_x - 1][to_y] - pref[to_x][from_y - 1] + pref[from_x - 1][from_y - 1];
}
void upd(int from_x , int from_y, int to_x , int to_y, int val){
    pref[from_x][from_y] += val;
    pref[to_x + 1][from_y] -= val;
    pref[from_x][to_y + 1] -= val;
    pref[to_x + 1][to_y + 1] += val;
}
void build(){
    for(int i = 1; i <= n; ++i) for(int j = 1; j <= m; ++j){
        pref[i][j] += pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
    }
}
void init(){
    for(int i = 1; i <= n; ++i) for(int j = 1; j <= m; ++j){
        pref[i][j] = 0;
    }
}
