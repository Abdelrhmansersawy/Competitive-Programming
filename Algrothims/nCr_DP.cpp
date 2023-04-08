#include <bits/stdc++.h>
typedef long long ll;
#define s second
#define f first
using namespace std;
int main(){
  ll n; cin >> n;
  ll nCr[n][n];
  nCr[0][0] = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(j == 0) nCr[i][j] = 1;
            nCr[i][j] = (nCr[i-1][j] + nCr[i-1][j-1]);
        }
    }
}
