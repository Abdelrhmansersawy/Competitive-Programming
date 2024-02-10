/*
    --Merge sort--
    Use: sorting the array
    Time Complexity: O(n log n)
    Space Complexity: O(n)
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
const int N = 1e5 + 1;
int a[N] , v1[N] , v2[N];
void mergeSort(int l , int r){
    int mid = (l + r) / 2;
    int n = mid - l , m = r - mid;
    for(int i = l; i < mid; ++i) v1[i - l] = a[i];
    for(int i = mid; i < r; ++i) v2[i - mid] = a[i];
    int i = l , idx1 = 0 , idx2 = 0;
    while(idx1 < n && idx2 < m){
        if(v1[idx1] <= v2[idx2]) a[i++] = v1[idx1++];
        else a[i++] = v2[idx2++];
    }
    while(idx1 < n) a[i++] = v1[idx1++];
    while(idx2 < m) a[i++] = v2[idx2++];
}
void merge(int l , int r){
    if(r - l == 1) return; // interval of length 1
    int mid = (l + r) / 2; // [l , mid[ , [mid , r[
    merge(l , mid);
    merge(mid , r);
    mergeSort(l , r);
}
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
    int n; cin >> n;
    for(int i = 0; i < n; ++i) cin >> a[i];
    merge(0 , n);
    for(int i = 0; i < n; ++i) cout << a[i] << " "; // array after sorted
}
