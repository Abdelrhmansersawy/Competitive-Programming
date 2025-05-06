const int N = 1e6 + 9, BLOCK_SIZE = 460;
void add(int idx){ 

}
void remove(int idx){  

}
struct Query{
    int l , r , id;
    bool operator <(const Query &other) const{
        int n1 = l / BLOCK_SIZE , n2 = other.l / BLOCK_SIZE;
        if(n1 != n2) return n1 < n2;
        return n1 % 2 ? r > other.r : r < other.r;
    }
};
void Mo(vector<Query> &query){
    sort(all(query));
    int mo_l = 0 , mo_r = -1;
    for(auto &q : query){
        while(mo_l > q.l) add(--mo_l);
        while(mo_r < q.r) add(++mo_r);
        while(mo_r > q.r) remove(mo_r--);
        while(mo_l < q.l) remove(mo_l++);
        // calculate answer of Query
    }
}
