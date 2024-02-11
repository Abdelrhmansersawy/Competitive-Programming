const int N = 1e6 + 9;
int nxt[N][27] , cntNode, isEnd[N], frq[N], n;
int get(char ch){ return  ch - 'a'; }
void add(string &s){
    int node = 0;
    for(auto &ch : s){
        if(nxt[node][get(ch)] == 0)
            nxt[node][get(ch)] = ++cntNode;
        node = nxt[node][get(ch)];
        frq[node]++;
    }
    isEnd[node] = true;
}
void remove(string &s){
    int node = 0;
    for(auto &ch : s){
        if(nxt[node][get(ch)] == 0) return; // this word "s" doesn't exist, (handle it manual)
        node = nxt[node][get(ch)];
        frq[node]--;
    }
    if(frq[node] == 0) isEnd[node] = false;
}
