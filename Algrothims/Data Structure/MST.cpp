struct DSU
{
  vector<int> par , size;
  DSU(int n){
    par.resize(n); size.resize(n , 1);
    rep(i , 0 , n) par[i] = i;
  }
  int get(int a){return par[a] = (par[a] == a) ? a : get(par[a]);}
  void Union(int a, int b){
    a = get(a); b = get(b);
    if(size[a] > size[b]) swap(a , b);
    size[b] += size[a];
    par[a] = b;
  }
};
void sol(){
  int n , m; cin >> n >> m;
  vector<array<int,3>> e(m); // {w , u , v}
  rep(i , 0 , m) cin >> e[i][1] >> e[i][2] >> e[i][0];
  sort(e.begin() , e.end());
  ll ans = 0;
  DSU d(n);
  for(auto &[w , u , v] : e){
    --u; --v;
    if(d.get(u) == d.get(v)) continue;
    d.Union(u , v);
    ans += w;
  }
  cout << ans;
}
