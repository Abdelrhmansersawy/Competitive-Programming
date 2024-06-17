/*
    --------------BIT-----------------
    Use: 1 - add value to element in the array
         2 - sum of range in the array
    Base: 0-index
    Time complexity : add , sum >> O(log(n))

*/
template<class T = int>
struct BIT{
    vector<T> tree;
    int n;
    void init(vector<T> &v){
        sort(all(v));
        v.erase(unique(v.begin() , v.end()) , v.end());
        this->n = v.size();
        tree.assign(n , 0);
    }
    void add(T idx , T val){
        int pos = lower_bound(v.begin(), v.end() , idx) - v.begin();
        assert(pos < n && v[pos] == idx);
        for(pos++; pos <= n ; pos += (pos & (-pos)))
            tree[pos - 1] += val;
    }
    T sum(int pos){
        pos = lower_bound(v.begin(), v.end() , idx) - v.begin();
        assert(pos < n);
        T ret = 0;
        for(pos++; pos ; pos -= (pos & (-pos)))
            ret += tree[pos - 1];
        return ret;
    }
    T qry(int l , int r){ return sum(r) - sum(l - 1); }
    T qry(int i){ return sum(i , i); }
};
