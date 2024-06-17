template<class T = int>
struct BIT{
    vector<T> tree , v;
    int n;
    void init(vector<T> vv){
        this->v = vv;
        sort(all(v));
        v.erase(unique(v.begin() , v.end()) , v.end());
        this->n = v.size();
        tree.assign(n , 0);
    }
    void add(T idx , T val){
        int pos = lower_bound(v.begin(), v.end() , idx) - v.begin();
        for(pos++; pos <= n ; pos += (pos & (-pos)))
            tree[pos - 1] += val;
    }
    T sum(int pos){
        pos = lower_bound(v.begin(), v.end() , pos) - v.begin();
        T ret = 0;
        for(pos++; pos ; pos -= (pos & (-pos)))
            ret += tree[pos - 1];
        return ret;
    }
    T qry(int l, int r){ return sum(r) - sum(l - 1); }
    T get_idx(int i){ return qry(i , i); }
};
