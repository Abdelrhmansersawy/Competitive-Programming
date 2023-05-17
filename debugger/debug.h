#include <bits/stdc++.h>
using namespace std;
#ifndef LOCAL
#define LOCAL
// Start Your Clock
clock_t START_TIME = clock();
// new Line
void debug(){cerr << "\n";};
// variables
template<typename T , typename ...Arg> void debug(T a , Arg...arg){cerr << a << " "; debug(arg...);};
// array
template<typename T , size_t n> void debug(T (&a)[n]){for(int i = 0 ; i < n ; i++) cerr << a[i] << " "; debug();};
template<typename T , size_t n , size_t m> void debug(T (&a)[n][m]){for(int i = 0 ; i < n ; i++){ for(int j = 0 ; j < m ; j++){ cerr << a[i][j] << " ";} cerr << '\n';}};
template<typename T, typename S,size_t n> void debug(pair<T,S>(&a)[n]){for(int i = 0 ; i < n ; i++)cerr << i << " = " << a[i].first << " " << a[i].second << '\n';};
template<typename T , size_t n> void debug(vector<T> (&v)[n]) {for(int i = 0; i< n; i++){ cerr << i << " = ";	for(auto &j : v[i]) cerr << j << " ";	cerr << '\n';}};
// vector
template<typename T> void debug(vector<T> &v) {for(auto &i : v) cerr << i << " "; cerr << '\n';};
template<typename T> void debug(vector<vector<T>> &v){for(auto &i : v){ for(auto &j : i)cerr << j << " "; cerr << '\n';}};
template<typename T , typename S> void debug(vector<pair<T , S>> &p){for(auto i : p) cerr << p.first << " " << p.second << '\n';};
template<typename T , typename S> void debug(vector< pair<T , vector<S> > > &v);
0template<typename T ,typename S> void debug(vector<map<T , S>> &v);
// set
template<class T>void debug(set<T> &a){for(auto &i : a) cerr << i << " "; cerr << '\n';};
template<class T>void debug(multiset<T> &a){for(auto &i : a) cerr << i << " "; cerr << '\n';};
template<class T>void debug(unordered_set<T> &a){for(auto &i : a) cerr << i << " "; cerr << '\n';};
// pair
template<typename T , typename S> void debug(pair<T , S> &p){cerr << p.first << " " << p.second << '\n';}
// map
template<typename T , typename S> void debug(map<T,S> &mp){for(auto &i : mp) cerr << i.first << " " << i.second << '\n';};
// Read or Write from File
void Sersawy(){
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif
}
// Clock
void end_clock(){
    clock_t START_TIME = clock();
    cout << '\n' << "// Time taken = " << fixed << setprecision(5) << (clock( ) - START_TIME) * 1e3 / CLOCKS_PER_SEC;
}
#endif
