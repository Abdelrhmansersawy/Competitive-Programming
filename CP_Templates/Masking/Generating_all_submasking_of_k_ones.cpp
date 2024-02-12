/*
	Gosper’s Hack (Bankers sequence)
	Time Complexity: nCk
*/
void f(int mask){
	// proccess the current mask with k 1's
}
void GospersHack(int n,int k){
    int sets=(1ll<<k)-1;
    int limit=(1ll<<n);
    while(sets<limit){
        f(sets);
        int c= sets & -sets;
        int r= sets + c;
        sets=( ( (r^sets) >>2 ) /c ) | r;
    }
}