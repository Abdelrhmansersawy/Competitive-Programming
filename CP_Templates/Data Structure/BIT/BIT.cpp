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
    void init(int n){
        this->n = n;
        tree.assign(n , 0);
    }
    void add(int pos , T val){
        for(pos++; pos <= n ; pos += (pos & (-pos)))
            tree[pos - 1] += val;
    }
    T sum(int pos){
        T ret = 0;
        for(pos++; pos ; pos -= (pos & (-pos)))
            ret += tree[pos - 1];
        return ret;
    }
    T qry(int l , int r){ return sum(r) - sum(l - 1); }
    T qry(int i){ return sum(i , i); }
};
