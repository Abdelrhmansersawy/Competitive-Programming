#include <bits/stdc++.h>
typedef long long ll;
#define s second
#define f first
const int N = 1e6; 
using namespace std;
ll D[N]
int main(){
  /*
   ----------- Derangements----------------
   derangement is a permutation of n elements with no fixed point
   there is no i such that p_i == i
   recursive Formula:
   1.
    D(n)=n*D(n−1)+(−1)^n
   2.
    D(n)=(n−1)(D(n−1)+D(n−2))
   Find more information : https://brilliant.org/wiki/derangements/
  */
  D[2] = 1; // Base-case
  for(int i = 3 ; i < N ; i++){
    D[i] = i * D[i - 1] + pow(-1 , i);
  }
}
