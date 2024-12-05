struct Node{
    Node* l , *r;
    int s;
    Node(int s): s(s) , l(NULL) , r(NULL){}; 
    Node(Node *l , Node *r): l(l) , r(r){
        this->s = 0;
        if(l != NULL) this->s += l->s;
        if(r != NULL) this->s += r->s;
    }
};
Node* newLeaf(int v){ return new Node{v}; }
Node* newPar(Node *l , Node *r){ return new Node(l,r); }
Node* build(int l = 0 , int r = m){
    if(r - l == 1) return newLeaf(0);
    int mid = (l+r)/2;
    return newPar( build(l,mid) , build(mid,r) );
}
Node* copy(int i , int v , Node* x , int l = 0 , int r = m){
    if(r-l== 1) return newLeaf(x->s + v);
    int mid = (r+l) / 2;
    if(i < mid) return newPar( copy(i,v, x->l , l , mid) , x->r );
    return newPar( x->l , copy(i,v , x->r , mid , r) );
}
int qry(int lx , int rx , Node* prv , Node* cur , int l = 0 , int r = m){
    if(l >= lx && r <= rx) return cur->s - prv->s;
    if(r <= lx || l >= rx) return 0;
    int mid = (l+r)/2;
    return qry(lx,rx,prv->l , cur->l,l,mid) + qry(lx,rx,prv->r , cur->r,mid,r);
}
