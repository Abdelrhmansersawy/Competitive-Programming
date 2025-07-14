// ============================ Presistent segment tree ====================== 
const int N = 1e5+9;
struct Node{
    Node* l, *r;
    int s;
    Node(ll s = 0, Node* l = NULL, Node* r = NULL):
        s(s) , l(l) , r(r){} 
};
Node* getL(Node* x){ return x == NULL ? x : x->l; }
Node* getR(Node* x){ return x == NULL ? x : x->r; }
int   getS(Node* x){ return x == NULL ? 0 : x->s; }
Node* newLeaf(int val){ return new Node(val); }

Node* newPar(Node* l, Node* r){
    Node* res = new Node();
    res->l = l; res->r = r;
    res->s = getS(l) + getS(r);
    return res;
} 

Node* upd(int i , int v , Node* x , int l = 0 , int r = N){
    if(r - l == 1) return newLeaf( v + getS(x) );
    int m = (l+r)/2;
    if(i < m){
        return newPar(upd(i,v,getL(x),l,m), getR(x));
    }else{
        return newPar(getL(x) , upd(i,v,getR(x),m,r));
    }
}

int sumSeg(Node*u , Node*v , Node* lca, Node* par_lca){
    return getS(u) + getS(v) - getS(lca) - getS(par_lca);
}

int kth(int k , Node*u , Node*v, Node* lca, Node* par_lca, int l = 0 , int r = N){
    if(r-l==1) return l;
    int m = (l+r)/2;

    int sumL = sumSeg( getL(u)  , getL(v)  , getL(lca) , getL(par_lca) );

    if(sumL >= k) 
        return kth(k  , getL(u)  , getL(v), getL(lca), getL(par_lca) , l , m);
    else
        return kth(k-sumL , getR(u) , getR(v) , getR(lca) , getR(par_lca) , m , r);
}

// ================================= LCA ====================================
const int LOG = 19;
vector<int> adj[N];
int dep[N] , up[N][LOG], a[N];
Node* versions[N];

void build_lca(int u , int p = N-1){
    up[u][0] = p;
    dep[u] = dep[p] + 1;
    for(int x = 1; x < LOG; ++x){
        up[u][x] = up[ up[u][x-1] ][x-1];
    }
    for(auto &v : adj[u]) if(v != p) build_lca(v,u);
}
int getLca(int u , int v){
    if(dep[v] > dep[u]) swap(u,v);
    int k = dep[u] - dep[v];
    for(int x = 0; x < LOG; ++x) if(k>>x&1) u = up[u][x];
    
    if(u == v) return u;

    for(int x = LOG-1; x >= 0; --x) if( up[u][x] != up[v][x] ){
        u = up[u][x];
        v = up[v][x];
    }

    assert(up[u][0] == up[v][0]);

    return up[u][0];
}

void build_presistent(int u, int p = N-1){
    versions[u] = upd(a[u], +1 , versions[p]); 
    for(auto &v : adj[u]) if(v != p) build_presistent(v, u);
}

int solve(int u , int v, int k){
    int lca = getLca(u,v);
    int par_lca = up[lca][0];
    return kth(k, versions[u] , versions[v] , versions[lca] , versions[par_lca]);
}
