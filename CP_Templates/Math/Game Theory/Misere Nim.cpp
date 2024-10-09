/**
    In misere nim who gives last move win.
    When all the pile have 1 stone then xor sum doesn't work (where you need to handle as a special case)
**/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first
#define s second
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);

    int tc; cin >> tc;
    while(tc--){
        int n; cin >> n;
        int xor_sum = 0 , ones = 0;
        for(int i = 0; i < n; ++i){
            int x; cin >> x;
            ones += (x==1);
            xor_sum ^= x;
        }
        if(ones == n) cout << (n&1 ? "Second\n" : "First\n");
        else cout << (xor_sum ? "First\n" : "Second\n"); 
    }
}   
