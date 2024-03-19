const int N = 1e5 + 9;
struct BIT{
    vector<int> tree;
    int n;
    void init(int n){
        this->n = n;
        tree.assign(n , 0);
    }
    void add(int pos , int val){
        for(pos++; pos <= n ; pos += (pos & (-pos)))
            tree[pos - 1] += val;
    }
    int sum(int pos){
        int ret = 0;
        for(pos++; pos ; pos -= (pos & (-pos)))
            ret += tree[pos - 1];
        return ret;
    }
    int sum(int l , int r){ return sum(r) - sum(l - 1); }
    int getidx(int i){ return sum(i , i); }
};
struct MultiSet{
    BIT B;
    MultiSet(){ B.init(N); }
    void insert(int val){ B.add(val,1); }
    void erase(int val){ B.add(val,-1); }
    int count(int val){ return B.sum(val - 1 , val); }
    int size(){ return B.sum(N-1); }
    int order_of_key(int key){
        int l = 0 , r = N - 1, mid;
        while(l < r){
            mid = l + (r - l) / 2;
            if(B.sum(mid) > key) r = mid;
            else l = mid + 1;
        }
        return l;
    }
}s;
