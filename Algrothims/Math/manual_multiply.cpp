#include <bits/stdc++.h>
typedef long long ll;
#define s second
#define f first
#define rep(i , st , ed) for(int i = st ; i < ed ; i++)
using namespace std;
void burn(){
ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
  #endif
}
//\//\//\/\//\//\//\//\//\//

int main(){
  burn();
  string s1 , s2; cin>> s1 >> s2;
  reverse(s1.begin(), s1.end());
  reverse(s2.begin(), s2.end());
  int MXN = 2 * max(s1.size() , s2.size())+ 9;
  int a[MXN];
  memset(a, 0, sizeof(a));
  for (int i=0; i<s1.length(); i++) {
    for (int j=0; j<s2.length(); j++) {
      a[i + j] += (s1[i]-'0') * (s2[j] - '0');
    }
  }
  for (int i=0; i<MXN - 1; i++) {
    a[i + 1] += a[i] / 10;
    a[i] %= 10;
  }
  int i = MXN - 1;
  while (i > 0 && a[i] == 0) i--;
  for (; i>=0; i--) cout<<a[i];
  cout<<endl;
}
