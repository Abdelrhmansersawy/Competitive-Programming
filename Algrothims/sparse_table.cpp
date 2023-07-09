const int N = 1e5 , M = 18;
int mn[N][M], mx[N][M] , a[N] , n;
void gen_sparsetable(){
	for (int i = 0; i < n; i++) mn[i][0] = mx[i][0] = a[i];
    for (int j = 1; (1 << j) < n; j++){
        for (int i = 0; (i + (1 << j) - 1) < n; i++){
       		mn[i][j] = min(mn[i][j - 1] , mn[i + (1 << (j - 1))][j - 1]);
    	  	mx[i][j] = max(mx[i][j - 1] , mx[i + (1 << (j - 1))][j - 1]);
    	}
    }
}
int query(int l, int r)
{
	  int len = r - l + 1;
    int j = 31 - __builtin_clz(len);
    int MAX = max(mx[l][j] , mx[r - (1 << j) + 1][j]),
    	MIN = min(mn[l][j] , mn[r - (1 << j) + 1][j]);
    return MIN; // determine what you want to return 
}
