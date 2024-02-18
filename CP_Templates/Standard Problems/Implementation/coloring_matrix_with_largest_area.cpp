/*
	Given a matrix n x m, each cell (i, j) can be
	1. g(i,j) = '.' -> empty cell
	2. g(i , j) = 'A' king , "There is exactly one letter 'A'"
	3. g(i , j) = child represented as charachter between 'z' -> 'z' , it's proved that letters are distinct.
	Output the same matrix, replacing each character '.' with the lowercase letter,
	corresponding to the owner of the  containing this cell
	"where e area of the king that belongs to his favorite child is as large as possible."
	Test Cases:
	Input:
		6 8
		......X.
		.F......
		...A....
		........
		.....P..
		..L.....
	Output:
		xxxxxxXx
		fFaaaaaa
		ffaAaaaa
		ffaaaaaa
		lllllPpp
		llLllppp
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
const int N = 1001;
int n , m , curI , curJ;
pair<int, int> L, R; // Diamtions of Maxiumum area
bool islower(char ch){ return ch >= 'a' && ch <= 'z';   }
bool validX(int x) { return x >= 0 && x < n; }
bool validY(int y) { return y >= 0 && y < m; }
void solveRange(int x1, int y1, int x2, int y2, vector<vector<char>> &g) {
    if (!validX(x1) || !validX(x2) || !validY(y1) || !validY(y2))
        return;
    for (int i = x1; i <= x2; i++) {
        int last = y1 - 1;
        char lastC = ' ';
        for (int j = y1; j <= y2; j++) {
            if (g[i][j] != '.') {
                char cur = g[i][j] - 'A' + 'a';
                for (int temp = j - 1; temp > last; temp--) {
                    g[i][temp] = cur;
                }
                last = j;
                lastC = cur;
            }
        }
        if (lastC != ' ') {
            for (int j = y2; j > last; j--) {
                g[i][j] = lastC;
            }
        } else {
            if (i - 1 >= x1 && g[i - 1][y1] != '.') {
                for (int j = y1; j <= y2; j++) {
                    g[i][j] = tolower(g[i - 1][j]);
                }
            }
        }
    }
    for (int i = x2; i >= x1; i--) {
        if (g[i][y1] == '.') {
            assert(i != x2);
            for (int j = y1; j <= y2; j++) {
                g[i][j] = tolower(g[i + 1][j]);
            }
        }
    }
}
void paint(int x1, int y1, int x2, int y2, char c , vector<vector<char>> &g) {
    for (int i = x1; i <= x2; i++) {
        for (int j = y1; j <= y2; j++) {
            g[i][j] = c;
        }
    }
}
void zero_matrix(vector<vector<char>> a) {
    n = a.size();
    m = a[0].size();
    vector<int> d(m, -1), d1(m), d2(m);
    stack<int> st;
    int mx = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] != '.') {
                d[j] = i;
            }
        }
        for (int j = 0; j < m; j++) {
            while (!st.empty() && d[st.top()] <= d[j]) {
                st.pop();
            }
            d1[j] = st.empty() ? -1 : st.top();
            st.push(j);
        }
        while (!st.empty()) {
            st.pop();
        }
        for (int j = m - 1; j >= 0; j--) {
            while (!st.empty() && d[st.top()] <= d[j]) {
                st.pop();
            }
            d2[j] = st.empty() ? m : st.top();
            st.push(j);
        }
        while (!st.empty()) {
            st.pop();
        }
        for (int j = 0; j < m; j++) {
            pair<int, int> tempL = {d[j] + 1, d1[j] + 1};
            pair<int, int> tempR = {i, d2[j] - 1};
            int area = (tempR.first - tempL.first + 1) * (tempR.second - tempL.second + 1);
            if (curI >= tempL.first && curI <= tempR.first && curJ >= tempL.second && curJ <= tempR.second &&
                area >= mx) {
                L = tempL;
                R = tempR;
                mx = area;
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
    cin >> n >> m;
    vector<vector<char>> g(n , vector<char>(m));
    int st_x, st_y;
    rep(i , 0 , n) rep(j ,0,m){
      cin >> g[i][j];
      if(g[i][j] == 'A') curI = i, curJ = j , g[i][j] = '.';
    }

    g[curI][curJ] = '.';
    zero_matrix(g);
    paint(L.first, L.second, R.first, R.second, char('a'), g);
    g[curI][curJ] = char('A');


    int x1 = L.first, y1 = L.second, x2 = R.first, y2 = R.second;
    solveRange(0, 0, x1 - 1, m - 1,g);
    solveRange(x1, 0, x2, y1 - 1,g);
    solveRange(x2 + 1, 0, n - 1, m - 1,g);
    solveRange(x1, y2 + 1, x2, m - 1,g);
 
    rep(i , 0 , n){
        rep(j , 0 , m){
            cout << g[i][j];
        }
        cout << '\n';
    }
}
