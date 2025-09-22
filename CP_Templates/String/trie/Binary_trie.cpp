const int N = 2e5 * 30 + 9;
int nxt[N][2], isEnd[N], cntNode, frq[N];

void clear() {
    for (int i = 0; i <= cntNode; i++) {
        nxt[i][0] = nxt[i][1] = 0;
        isEnd[i] = 0;
        frq[i] = 0;
    }
    cntNode = 0;
}

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
        if(nxt[node][cur] == 0) return; // x not found
        node = nxt[node][cur];
        frq[node]--;
    }
    if(frq[node] == 0) isEnd[node] = false;
}

int max_xor(int x){
    int node = 0, ans = 0;
    for(int i = 30; i >= 0; --i){
        int cur = (x >> i) & 1;
        int want = cur ^ 1; // opposite bit gives higher XOR
        if(nxt[node][want] && frq[nxt[node][want]] > 0) {
            ans |= (1 << i);
            node = nxt[node][want];
        } else if(nxt[node][cur] && frq[nxt[node][cur]] > 0) {
            node = nxt[node][cur];
        } else break; // no valid path
    }
    return ans;
}

int min_xor(int x){
    int node = 0, ans = 0;
    for(int i = 30; i >= 0; --i){
        int cur = (x >> i) & 1;
        if(nxt[node][cur] && frq[nxt[node][cur]] > 0) {
            node = nxt[node][cur];
        } else if(nxt[node][cur ^ 1] && frq[nxt[node][cur ^ 1]] > 0) {
            ans |= (1 << i); // different bit contributes to XOR
            node = nxt[node][cur ^ 1];
        } else break; // no valid path
    }
    return ans;
}
