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
void add_constraint(TwoSAT &s , int ind , int lx , int rx , int x , int l, int r){
    if(l >= lx && r <= rx){
        // TODO: add the actual constraint for this range segment
        // Example: s.add_at_most_one(ind, tree[x]);  // link variable 'ind' with this segment node
        // (called for every node fully covered by [lx, rx))
        return;
    }
    if(r <= lx || l >= rx) return;
    add_constraint mid = (l+r)/2;
    qry(TwoSAT s , ind , lx ,rx , 2 * x + 1 , l , mid);
    add_constraint(TwoSAT s , ind, lx, rx , 2 * x + 2 , mid , r);
}
