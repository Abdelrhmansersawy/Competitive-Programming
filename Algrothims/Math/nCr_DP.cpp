const int N = 61;
ll nCr[N][N];
void gen(){
    nCr[0][0] = 1;
    for (int i = 0; i < N; ++i) {
        nCr[i][0] = nCr[i][i] = 1;
        for (int j = 0; j < i; ++j) {
            nCr[i][j] = (nCr[i-1][j] + nCr[i-1][j-1]);
        }
    }
}
