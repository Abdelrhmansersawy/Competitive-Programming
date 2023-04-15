#include <bits/stdc++.h>
typedef long long ll;
#define s second
#define f first
#define rep(i , st , ed) for(int i = st ; i < ed ; i++)
using namespace std;
const int N = 4000;
void burn(){
ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
  #endif
}
//\//\//\/\//\//\//\//\//\//
int n;
vector<int> adj[N];
string get_subcan(int u , vector<vector<string>> &subcan){
  sort(subcan[u].begin() , subcan[u].end());
  string ans = "(";
  for(auto &s : subcan[u]) ans += s;
  ans += ")";
  return ans;
}
void tree_isophrisim(){
  vector<int> deg(n);
  queue<int> leaf;
  vector<vector<string>> subcan(n);
  rep(i , 0 , n){
    deg[i] = adj[i].size();
    if(deg[i] <= 1) leaf.push(i);
  }
  int rem = n;
  while(rem > 2){
    int sz = leaf.size();
    while(sz--){
      rem--;
      int u = leaf.front(); leaf.pop();
      string temp = get_subcan(u ,  subcan);
      for(auto &v : adj[u]){
        subcan[v].emplace_back(temp);
        deg[v]--;
        if(deg[v] == 1) leaf.push(v);
      }
    }
  }
  vector<string> ans; // contain all possible canonical 
  int c1 = leaf.front(); leaf.pop();
  if(leaf.empty()){
    // tree has one center
    ans.emplace_back(get_subcan(c1 , subcan));
  }else{
    // tree has 2 center
    int c2 = leaf.front();
    string temp1 = get_subcan(c1 , subcan),
           temp2 = get_subcan(c2 , subcan);
    subcan[c1].push_back(temp2);
    subcan[c2].push_back(temp1);
    ans.emplace_back(get_subcan(c1 , subcan));
    ans.emplace_back(get_subcan(c2 , subcan));
  }
}
int main(){
  burn();
}
