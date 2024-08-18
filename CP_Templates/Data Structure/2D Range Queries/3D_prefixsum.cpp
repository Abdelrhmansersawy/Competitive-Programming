const int N = 500, M = 500 , K = 500;
int P[N][M][K]; // 1-base
int n , m , k;
int qry(int from_x , int from_y , int from_z , int to_x , int to_y , int to_z){
    int result = P[to_x][to_y][to_z]
                   - P[from_x-1][to_y][to_z] 
                   - P[to_x][from_y-1][to_z]
                   - P[to_x][to_y][from_z-1]
                   + P[from_x-1][from_y-1][to_z]
                   + P[from_x-1][to_y][from_z-1] 
                   + P[to_x][from_y-1][from_z-1]
                   - P[from_x-1][from_y-1][from_z-1];
}
void upd(int from_x , int from_y, int from_z, int to_x , int to_y, int to_z , int val){
    P[from_x][from_y][from_z] += val;
    P[to_x + 1][from_y][from_z] -= val;
    P[from_x][to_y + 1][from_z] -= val;
    P[to_x][from_y][to_z + 1] -= val;
    P[to_x + 1][to_y + 1][from_z] += val;
    P[to_x + 1][from_y][to_z + 1] += val;
    P[from_x][to_y + 1][to_z + 1] += val;
    P[to_x + 1][to_y + 1][to_z + 1] -= val;
}
void build(vector<vector<vector<int>>> &A){
    for (int x = 1; x <= N; ++x) {
        for (int y = 1; y <= N; ++y) {
            for (int z = 1; z <= N; ++z) {
                P[x][y][z] = A[x][y][z]
                           + P[x-1][y][z]
                           + P[x][y-1][z]
                           + P[x][y][z-1]
                           - P[x-1][y-1][z]
                           - P[x-1][y][z-1]
                           - P[x][y-1][z-1]
                           + P[x-1][y-1][z-1];
            }
        }
    }
}
void init(){
    for(int i = 1; i <= n; ++i) for(int j = 1; j <= m; ++j) for(int k = 1; k <= K; ++k){
        P[i][j][k] = 0;
    }
}
