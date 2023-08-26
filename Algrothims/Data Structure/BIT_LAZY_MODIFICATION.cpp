/*
	BIT with LAZY MODIFICATION
	use : So far we have presented BIT as a structure which is entirely allocated in memory during the initialization.
        An advantage of this approach is that accessing tree[idx] requires a constant time. On the other hand, we might need to access only tree[idx] for a couple of different values of idx, e.g. log n different values, while we allocate much larger memory. This is especially aparent in the cases when we work with multidimensional BIT.
*/
const int inf = 1e9 + 9;
map<int,int> tree; // LAZY MODIFICATION
struct BIT {
    void add(int x, int val) {
    	for(; x < inf; x += (x & -x))  tree[x] += val;
    }
    int sum(int x){
    	int res = 0;
    	for(;x; x -= (x & -x)) res += tree[x];
    	return res;
    }
};
