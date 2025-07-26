*
 * ======================== Longest Increasing Subsequence of Pairs ========================
 *
 * Given a sequence of N pairs of integers, find the length of the longest increasing
 * subsequence (LIS) of these pairs.
 *
 * Definitions:
 * - An increasing sequence A1, A2, ..., Ak is one where for every i < j, Ai < Aj.
 * - A subsequence is a sequence that appears in the same relative order, but not necessarily contiguous.
 * - A pair (x1, y1) is less than another pair (x2, y2) if and only if x1 < x2 and y1 < y2.
 *
 * Input:
 * - The first line contains an integer N (2 ≤ N ≤ 100000) — the number of pairs.
 * - The next N lines each contain two integers xi and yi (−10^9 ≤ xi, yi ≤ 10^9) — the elements of each pair.
 *
 * Output:
 * - Output a single integer — the length of the longest increasing subsequence of these pairs.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first
#define s second

const int N = 1e5+9;
int dp[N] , x[N] , y[N];
bool comp(int i , int j){ return y[i] < y[j]; }
int tree[4*N];
void upd(int i , int v , int x = 0, int l =0 , int r = N){
    if(r-l==1){ tree[x] = max(tree[x] , v); return;}
    int m = (l+r)/2;
    if(i < m) upd(i,v,2*x+1,l,m);
    else upd(i,v,2*x+2,m,r);
    tree[x] = max(tree[2*x+1] , tree[2*x+2]);
}
void clear(int i , int x = 0, int l =0 , int r = N){
    if(r-l==1){ tree[x] = 0; return;}
    int m = (l+r)/2;
    if(i < m) clear(i,2*x+1,l,m);
    else clear(i,2*x+2,m,r);
    tree[x] = max(tree[2*x+1] , tree[2*x+2]);
}
int qry(int lx , int rx , int x = 0 , int l = 0, int r = N){
    if(l >= lx && r <= rx) return tree[x];
    if(r <= lx || l >= rx) return 0;
    int m = (l+r)/2;
    return max(qry(lx,rx,2*x+1,l,m), qry(lx,rx,2*x+2,m,r));
}


void dc(int l , int r){
    if(l == r){ return; }
    int m = (l+r) / 2;
    dc(l,m);

    vector<int> left(m-l+1);
    iota(left.begin(),left.end(),l);
    sort(left.begin(),left.end(),comp);

    vector<int> right(r-m);
    iota(right.begin(),right.end(),m+1);
    sort(right.begin(),right.end(),comp);

    int i = 0;
    int mx = 0;
    
    for(int j = 0; j < right.size(); ++j){
        while(i < left.size() && y[left[i]] < y[right[j]]){
            int ind = left[i];
            upd(x[ind] , dp[ind]);
            ++i;
        }

        int ind = right[j];
        dp[ind] = max(dp[ind] , qry(0,x[ind]) + 1);
    }

    while(i > 0){ --i; clear(x[left[i]]); }

    dc(m+1,r);
}
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);

    int n; cin >> n;
    vector<int> all;
    for(int i = 0; i < n; ++i){
        cin >> x[i] >> y[i];
        all.emplace_back(x[i]);
        dp[i] = 1; // base-case
    }

    sort(all.begin(),all.end());
    all.erase(unique(all.begin(),all.end()),all.end());

    for(int i = 0; i < n; ++i){
        x[i] = lower_bound(all.begin(),all.end(),x[i]) - all.begin();
    }

    dc(0,n-1);

    int bst = 0;
    for(int i = 0; i < n; ++i){
        bst = max(bst , dp[i]);
    }
    cout << bst;
}
