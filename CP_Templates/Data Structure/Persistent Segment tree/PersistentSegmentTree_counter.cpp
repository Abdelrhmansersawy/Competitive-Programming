const int N = 1e6+9;
int n , m , id;
struct Node{
    int l , r , s;
}tree[20*N];
int newLeaf(int v){
    tree[id] = Node{-1,-1,v};
    return id++;
}
int newPar(int l , int r){
    tree[id] = Node{l,r,0};
    tree[id].s += tree[l].s;
    tree[id].s += tree[r].s;
    return id++;
}
int build(int l = 0 , int r = m){
    if(r - l == 1) return newLeaf(0);
    int mid = (l+r)/2;
    return newPar( build(l,mid) , build(mid,r) );
}
int copy(int i , int v , int x , int l = 0 , int r = m){
    if(r - l == 1) return newLeaf(tree[x].s + v);
    int mid = (l+r)/2;
    if(i < mid) return newPar( copy(i,v , tree[x].l , l , mid) , tree[x].r);
    return newPar( tree[x].l , copy(i,v, tree[x].r , mid , r) );
}
int qry(int lx , int rx , int prv , int cur , int l = 0 , int r = m){
    if(l >= lx && r <= rx) return tree[cur].s - tree[prv].s;
    if(r <= lx || l >= rx) return 0;
    int mid = (l+r)/2;
    return qry(lx,rx, tree[prv].l , tree[cur].l ,l,mid) + qry(lx,rx, tree[prv].r , tree[cur].r,mid,r);
}
