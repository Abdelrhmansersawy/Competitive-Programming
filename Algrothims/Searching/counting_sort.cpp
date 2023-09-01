/*
    --Counting Sorting--
    use:- It's an algrothim to sort the array using bookkeeping array aka(frequency array)
    Time Complexity:- O(max(a_1 , a_2 ,.. , n));
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
const int N = 1e5 + 9;
int fre[N];
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    int n; cin >> n;
    int a[n] , b[n];
    for(int i = 0; i < n; ++i) cin >> a[i] , fre[a[i]]++;
    // counting-sorting
    int idx = 0;
    for(int i = 0; i < N; ++i) for(int j = 0; j < fre[i]; j++)
        b[idx++] = i;
    // b >> contains array a after sorting
}
