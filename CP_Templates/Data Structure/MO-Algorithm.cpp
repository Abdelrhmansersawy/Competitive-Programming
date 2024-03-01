const int blockSize = 555 , N = 2e5 + 9;
struct Query {
    int l, r, idx;
    Query(int l , int r , int idx):l(l) , r(r) , idx(idx){};
    bool operator<(Query other) const
    {
        return make_pair(l / blockSize, r) <
               make_pair(other.l / blockSize, other.r);
    }
};
vector<Query> Qlist;
void add(int p) {
}

void remv(int p) {

}
void calc_answer(int idx){

}
void MO(){
    sort(all(Qlist));
    int cur_l = 0;
    int cur_r = -1;
    for (Query q : Qlist) {
            while (cur_l > q.l) {
                cur_l--;
                add(cur_l);
            }
            while (cur_r < q.r) {
                cur_r++;
                add(cur_r);
            }
            while (cur_l < q.l) {
                remv(cur_l);
                cur_l++;
            }
            while (cur_r > q.r) {
                remv(cur_r);
                cur_r--;
            }
            // calculate ans of Query of q.idx
            calc_answer(q.idx);
        }
}
