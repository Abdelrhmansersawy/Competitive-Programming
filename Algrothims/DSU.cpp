struct DSU{
  vector<int> par , size;
  DSU(int n){
    par.resize(n); size.resize(n , 1);
    for(int i = 0; i < n; i++) par[i] = i;
  }
  int get(int a){return par[a] = (par[a] == a) ? a : get(par[a]);}
  void Union(int a , int b){
    a = get(a); b = get(b);
    if(size[a] > size[b]) swap(a , b);
    size[b] += size[a];
    par[a] = b;
  }
  int same_Group(int a , int b){return get(a) == get(b);}
};
