// Forces at most one of the given (variable,state) pairs to be true
void at_most_one(const vector<pair<int, int> > &v) {
    if (v.size() <= 1) return;
    int last_pref = -1;
    for (int i = 0; i < (int)v.size(); ++i) {
        int x = v[i].first, state = v[i].second;
        int p = add_var();
        add_imply(p, false, x, state ^ 1);
        if (last_pref != -1) {
            add_imply(p, false, last_pref, false);
            add_imply(x, state, last_pref, false);
        }
        last_pref = p;
    }
    int last_suf = -1;
    for (int i = (int)v.size() - 1; i >= 0; --i) {
        int x = v[i].first, state = v[i].second;
        int s = add_var();
        add_imply(s, false, x, state ^ 1);
        if (last_suf != -1) {
            add_imply(s, false, last_suf, false);
            add_imply(x, state, last_suf, false);
        }
        last_suf = s;
    }
}


// Purpose: efficiently express “variable is OR of a range of vars” in 2-SAT using a segment tree.
// build(): create SAT vars for tree nodes, link children → parent (builds the OR hierarchy) — O(n)
// qry(): connect a single var to all segments overlapping [lx, rx) — O(log n)
const int N = 1e5+9;
int tree[4*N] ;
void build(TwoSAT &s, int x, int l, int r){
    if(r-l==1){
        tree[x] = l; 
        return;
    }
    int mid = (l+r)/2;
    build(s , 2 * x + 1 , l , mid); 
    build(s , 2 * x + 2 , mid , r);

    tree[x] = s.add_var();
    s.add_imply(tree[2*x+1] , true , tree[x] , true);
    s.add_imply(tree[2*x+2] , true , tree[x] , true);
}
void qry(TwoSAT &s , int ind , int lx , int rx , int x , int l, int r){
    if(l >= lx && r <= rx){
        // TODO: add the actual constraint for this range segment
        // Example: s.add_at_most_one(ind, tree[x]);  // link variable 'ind' with this segment node
        // (called for every node fully covered by [lx, rx))
        return;
    }
    if(r <= lx || l >= rx) return;
    int mid = (l+r)/2;
    qry(TwoSAT s , ind , lx ,rx , 2 * x + 1 , l , mid);
    qry(TwoSAT s , ind, lx, rx , 2 * x + 2 , mid , r);
}
