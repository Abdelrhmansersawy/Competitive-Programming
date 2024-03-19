// you can't insert zeros and you can't insert negative make shift or compression

struct Bit{
    int N=1<<20;
    vector<int>tree;
    void init(){
        tree.resize(this->N);
    }
    void add(int pos,int value){
        for(int i=pos+1;i<=N;i+=i&-i)tree[i-1]+=value;
    }
    int get(int pos) {
        int sum = 0;
        for (int i = pos + 1; i; i -= i & -i)sum += tree[i - 1];
        return sum;
    }
    int find(int t){
        int st=0;
        for(int sz=N>>1;sz;sz>>=1){
            if(tree[st+sz-1]<t){
                t-=tree[(st+=sz)-1];
            }
        }
        return st;
    }
};
struct MultiSet{
    Bit bit;
    MultiSet(){
        bit.init();
        bit.add(0,-1);
    }
    void insert(int value){
        bit.add(value,1);
    }
    void erase(int value){
        bit.add(value,-1);
    }
    int count(int value){
        return bit.get(value)-bit.get(value-1);
    }
    int size(){
        return bit.get(bit.N-1)+1;
    }
    int at(int index){
        return bit.find(index);//return the value which at index (index)
    }
    int order_of_key(int key){
        int left = 0 , right = size()-1;
        int res = right + 1;
        while(left<=right){
            int mid = left+(right-left)/2;
            if(at(mid)>=key){
                res = mid;
                right = mid-1;
            }else{
                left = mid+1;
            }
        }
        return res;
    }
};
