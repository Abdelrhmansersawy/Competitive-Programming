/*
	BIT with LAZY MODIFICATION
	use : So far we have presented BIT as a structure which is entirely allocated in memory during the initialization.
        An advantage of this approach is that accessing tree[idx] requires a constant time. On the other hand, we might need to access only tree[idx] for a couple of different values of idx, e.g. log n different values, while we allocate much larger memory. This is especially aparent in the cases when we work with multidimensional BIT.
*/
// 1-base
const int inf = 1e9 + 9;
map<int,long long> tree; // LAZY MODIFICATION
struct BIT {
    void add(int x, int val) {
    	for(; x < inf; x += (x & -x))  tree[x] += val;
    }
    long long sum(int x){
    	long long res = 0;
    	for(;x > 0; x -= (x & -x)) res += tree[x];
    	return res;
    }
    long long sum(int l , int r){ return sum(r) - sum(l - 1); }
};
