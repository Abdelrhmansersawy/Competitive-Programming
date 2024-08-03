const int N = 2e5 * 30 + 9;
int nxt[N][2], isEnd[N], cntNode, frq[N];
void add(int x){
    int node = 0;
    for(int i = 30; i >= 0; --i){
        int cur = (x >> i) & 1;
        if(nxt[node][cur] == 0)
            nxt[node][cur] = ++cntNode;
        node = nxt[node][cur];
        frq[node]++;
    }
    isEnd[node] = true;
}
void erase(int x){
    int node = 0;
    for(int i = 30; i >= 0; --i){
        int cur = (x >> i) & 1;
        if(nxt[node][cur] == 0) return; // this number "x" doesn't exist, (handle it manual)
        node = nxt[node][cur];
        frq[node]--;
    }
    if(frq[node] == 0) isEnd[node] = false;
}
