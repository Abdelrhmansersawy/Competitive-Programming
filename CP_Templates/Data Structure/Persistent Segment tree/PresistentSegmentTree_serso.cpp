const int N = 1e6+9;
int n , m , id;
struct Node{
    int l , r , s;
}tree[20*N];
int getL(int x){ return ~x ? tree[x].l : -1; }
int getR(int x){ return ~x ? tree[x].r : -1; }
int getS(int x){ return ~x ? tree[x].s : 0; }
 
int newLeaf(int v){
    tree[id] = Node{-1,-1,v};
    return id++;
}
int newPar(int l , int r){
    tree[id] = Node{l,r, getS(l) + getS(r)};
    return id++;
}
int copy(int i , int v , int x , int l = 0 , int r = m){
    if(r - l == 1) return newLeaf( getS(x) + v);
    int mid = (l+r)/2;
    if(i < mid) return newPar( copy(i,v , getL(x) , l , mid) , getR(x));
    return newPar( getL(x) , copy(i,v, getR(x) , mid , r) );
}
int qry(int lx , int rx , int prv , int cur , int l = 0 , int r = m){
    if(l >= lx && r <= rx) return getS(cur) - getS(prv);
    if(r <= lx || l >= rx) return 0;
    int mid = (l+r)/2;
    return qry(lx,rx, getL(prv) , getL(cur) ,l,mid) + qry(lx,rx, getR(prv) , getR(cur) , mid , r);
}
