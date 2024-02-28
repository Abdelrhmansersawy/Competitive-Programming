//point location


#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 2e5 + 9, M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
struct Point {
    double x, y;
};
 
int orientation(Point a, Point b, Point c) {
    double v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
    if (v < 0) return -1; // clockwise
    if (v > 0) return +1; // counter-clockwise
    return 0;
}
 
bool cw(Point a, Point b, Point c, bool include_collinear) {
    int o = orientation(a, b, c);
    return o < 0 || (include_collinear && o == 0);
}
bool collinear(Point a, Point b, Point c) { return orientation(a, b, c) == 0; }
 
void convex_hull(vector<Point>& a, bool include_collinear = false) {
    Point p0 = *min_element(a.begin(), a.end(), [](Point a, Point b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });
    sort(a.begin(), a.end(), [&p0](const Point& a, const Point& b) {
        int o = orientation(p0, a, b);
        if (o == 0)
            return (p0.x-a.x)*(p0.x-a.x) + (p0.y-a.y)*(p0.y-a.y)
                < (p0.x-b.x)*(p0.x-b.x) + (p0.y-b.y)*(p0.y-b.y);
        return o < 0;
    });
    if (include_collinear) {
        int i = (int)a.size()-1;
        while (i >= 0 && collinear(p0, a[i], a.back())) i--;
        reverse(a.begin()+i+1, a.end());
    }
 
    vector<Point> st;
    for (int i = 0; i < (int)a.size(); i++) {
        while (st.size() > 1 && !cw(st[st.size()-2], st.back(), a[i], include_collinear))
            st.pop_back();
        st.push_back(a[i]);
    }
 
    a = st;
}
double area(Point a, Point b, Point c)
{
    return 0.5*abs(a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y));
}
long double cross(Point a, Point b, Point c)
{
    Point v1 = {b.x-a.x,b.y-a.y};
    Point v2 = {c.x-a.x,c.y-a.y};
    return (long double) (v1.x*v2.y - v1.y*v2.x);
}
void solve()
{
    Point a,b,c;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
    if(cross(a,b,c) > 0) cout << "LEFT\n";
    else if(cross(a,b,c) == 0) cout << "TOUCH\n";
    else cout << "RIGHT\n";
 
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; cin >> T;
     while(T--)
     {
        solve();
     }
}


//segment intersection
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 2e5 + 9, M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
long double eps = 1e-4;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
struct Point {
    double x, y;
};
 
int orientation(Point a, Point b, Point c) {
    double v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
    if (v < 0) return -1; // clockwise
    if (v > 0) return +1; // counter-clockwise
    return 0;
}
 
bool cw(Point a, Point b, Point c, bool include_collinear) {
    int o = orientation(a, b, c);
    return o < 0 || (include_collinear && o == 0);
}
bool collinear(Point a, Point b, Point c) { return orientation(a, b, c) == 0; }
 
void convex_hull(vector<Point>& a, bool include_collinear = false) {
    Point p0 = *min_element(a.begin(), a.end(), [](Point a, Point b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });
    sort(a.begin(), a.end(), [&p0](const Point& a, const Point& b) {
        int o = orientation(p0, a, b);
        if (o == 0)
            return (p0.x-a.x)*(p0.x-a.x) + (p0.y-a.y)*(p0.y-a.y)
                < (p0.x-b.x)*(p0.x-b.x) + (p0.y-b.y)*(p0.y-b.y);
        return o < 0;
    });
    if (include_collinear) {
        int i = (int)a.size()-1;
        while (i >= 0 && collinear(p0, a[i], a.back())) i--;
        reverse(a.begin()+i+1, a.end());
    }
 
    vector<Point> st;
    for (int i = 0; i < (int)a.size(); i++) {
        while (st.size() > 1 && !cw(st[st.size()-2], st.back(), a[i], include_collinear))
            st.pop_back();
        st.push_back(a[i]);
    }
 
    a = st;
}
double area(Point a, Point b, Point c)
{
    return 0.5*abs(a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y));
}
bool onSegment(Point p, Point q, Point r) 
{ 
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && 
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) 
       return true; 
  
    return false; 
} 
  
// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are collinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
  
// The main function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 
bool doIntersect(Point p1, Point q1, Point p2, Point q2) 
{ 
    // Find the four orientations needed for general and 
    // special cases 
    int o1 = orientation(p1, q1, p2); 
    int o2 = orientation(p1, q1, q2); 
    int o3 = orientation(p2, q2, p1); 
    int o4 = orientation(p2, q2, q1); 
  
    // General case 
    if (o1 != o2 && o3 != o4) 
        return true; 
  
    // Special Cases 
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1 
    if (o1 == 0 && onSegment(p1, p2, q1)) return true; 
  
    // p1, q1 and q2 are collinear and q2 lies on segment p1q1 
    if (o2 == 0 && onSegment(p1, q2, q1)) return true; 
  
    // p2, q2 and p1 are collinear and p1 lies on segment p2q2 
    if (o3 == 0 && onSegment(p2, p1, q2)) return true; 
  
     // p2, q2 and q1 are collinear and q1 lies on segment p2q2 
    if (o4 == 0 && onSegment(p2, q1, q2)) return true; 
  
    return false; // Doesn't fall in any of the above cases 
} 
  
void solve()
{
    Point a,b,c,d,ret;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
    if(doIntersect(a,b,c,d)) cout << "YES\n";
    else cout << "NO\n";
 
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; cin >> T;
     while(T--)
     {
        solve();
     }
}



//polygon area
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 2e5 + 9, M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
long double eps = 1e-4;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
struct Point {
    int x, y;
};
int cross(Point a, Point b)
{
    return a.x*b.y - a.y*b.x;
}
 
void solve()
{
    int n; cin >> n;
    vector<Point> p(n);
    for(auto &i : p) cin >> i.x >> i.y;
    int area = 0;
    for (int i = 0; i < n; ++i)
    {
       int j = (i + 1)%n;
       area +=  (p[i].x*p[j].y -  p[j].x*p[i].y);
    }
    cout << abs(area) << '\n';
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }
}

// point in polygon 
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxN = 1001;

struct Point {
    int x, y;
    void read(){ scanf("%d %d", &x, &y); }
    Point operator +(const Point& b) const { return Point{x+b.x, y+b.y}; }
    Point operator -(const Point& b) const { return Point{x-b.x, y-b.y}; }
    ll operator *(const Point& b) const { return (ll) x * b.y - (ll) y * b.x; }
    void operator +=(const Point& b) { x += b.x; y += b.y; }
    void operator -=(const Point& b) { x -= b.x; y -= b.y; }
    void operator *=(const int k) { x *= k; y *= k; }

    ll cross(const Point& b, const Point& c) const {
        return (b - *this) * (c - *this);
    }
};

int N, M;
Point P[maxN];

bool pointlineintersect(Point P1, Point P2, Point P3){
    if(P2.cross(P1, P3) != 0)   return false;
    return (min(P2.x, P3.x) <= P1.x && P1.x <= max(P2.x, P3.x))
        && (min(P2.y, P3.y) <= P1.y && P1.y <= max(P2.y, P3.y));
}

void pointinpolygon(){
    int cnt = 0;
    bool boundary = false;
    for(int i = 1; i <= N; i++){
        int j = (i == N ? 1 : i+1);
        if(pointlineintersect(P[0], P[i], P[j]))
            boundary = true;

        if(P[i].x <= P[0].x && P[0].x < P[j].x && P[0].cross(P[i], P[j]) < 0)       cnt++;
        else if(P[j].x <= P[0].x && P[0].x < P[i].x && P[0].cross(P[j], P[i]) < 0)  cnt++;
    }

    if(boundary)    cout << "BOUNDARY\n";
    else if(cnt&1)  cout << "INSIDE\n";
    else            cout << "OUTSIDE\n";
}

int main(){
    cin >>  N >> M;
    for(int i = 1; i <= N; i++)
        P[i].read();
    for(int i = 0; i < M; i++){
        P[0].read();
        pointinpolygon();
    }
}

//polygon lattice points 
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long ll;
#define FAST ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
#define rep(x , st , ed) for(int x = st ; x < ed ; x++)
const ll N = 2e5 + 9, M = 100 , mod = 1e9 + 7 , OO = 2 * 1e9 , OOLL = 1 * 1e18;
long double eps = 1e-4;
int dx[] = {-1, 0, 0, 1};
int dy[] = { 0,-1, 1, 0};
ll mul(ll a , ll b){ return a * b % mod; }
ll add(ll a , ll b){ return (a + b) % mod; }
ll sub(ll a , ll b){ return (a - b + mod) % mod; }
#define vec(a,b)  ((b) - (a))
struct Point {
    typedef Point P;
    int x, y;
    explicit Point(int x=0, int y=0) : x(x), y(y) {}
    P operator-(P p) const { return P(x-p.x, y-p.y); }
};
int picksTheorem(int a, int b) {
   // a: area of polygon, b: no. lattice Points in the boundaries
   return a - b / 2 + 1;
}
int cross(const Point &a, const Point &b){
    return a.x * b.y - b.x * a.y;
}
pair<int,int> picksTheorem(vector<Point>& p) {
   // Point sorted in counter clock-wise;
   int area = 0;
   int bound = 0;
   int sz = (int) p.size();
   for(int i = 0; i < sz; i++) {
      int j = (i + 1) % sz;
      area += cross(p[i], p[j]);
      Point v = vec(p[i], p[j]);
      bound += abs(__gcd((int) v.x, (int) v.y));
   }
   area = abs(area);
   return {(area - bound + 2)/2 , bound};
}
void solve()
{
    int n; cin >> n;
    vector<Point> p(n);
    for(auto &i : p) cin >> i.x >> i.y;
    pair<int,int> ans = picksTheorem(p);
    cout << ans.first  << " " << ans.second << "\n";
}
int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif 
     ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
     int T=1; //cin >> T;
     while(T--)
     {
        solve();
     }
}
//minimum eclidiun distance
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define P pair<int, int>
#define X first
#define Y second
signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    int n; cin>>n;
    vector<P> v(n);
    int d = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        v[i] = {x, y};
    }
    sort(v.begin(), v.end());
    set<P> s = {{v[0].Y, v[0].X}};
    int j = 0;
    for (int i = 1; i < n; i++) {
        auto it = s.begin();
        int dd = ceil(sqrt(d));
        while (j < i && v[j].X < v[i].X - dd) {
            s.erase({v[j].Y, v[j].X});
            j++;
        }

        auto l = s.lower_bound({v[i].Y - dd, 0});
        auto r = s.upper_bound({v[i].Y + dd, 0});
        for (auto it = l; it != r; it++) {
            d = min(d, norm({it->Y, it->X}, v[i]));
        } 
        s.insert({v[i].Y, v[i].X});
    }
    cout << d;
}