/*
   Standard Problem: https://codeforces.com/gym/104968/problem/H
   Given a convex polygon
   Given a n point check if this point inside a polygon or not in O(log n)
   by pre-proccessing O(n)
*/
#include <bits/stdc++.h>
using namespace std;
#define double long double
#define int long long
#define vec(a,b) {b.x-a.x,b.y-a.y}
long long const N  = 1e5;
struct Point { int x, y; };
double const eps = 1e-7;
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
double cross(Point a, Point b){ return a.x*b.y - b.x*a.y; }
int cross(Point a, Point b, Point c){
    Point d = vec(b,a), e = vec(c,a);
    return cross(d,e);
}
double dot(Point a, Point b){
    return a.x*b.x + a.y*b.y;
}
bool pointOnLine(Point a, Point b, Point p){
    return fabs(cross(vec(a,b),vec(a,p))) < eps;
}
bool pointOnRay(Point a, Point b, Point p){
    return dot(vec(a,p),vec(a,b)) > -eps;
}
bool pointOnsegment(Point a, Point b, Point p){
    if(!pointOnLine(a,b,p)) return 0;
    return pointOnRay(a,b,p) && pointOnRay(b,a,p);
}
vector<Point> v(N);
void prepare(int n) {
    int pos = 0;
    for (int i = 0; i < n; i++) {
        if (make_pair(v[i].x, v[i].y) < make_pair(v[pos].x, v[pos].y))
            pos = i;
    }
    rotate(v.begin(), v.begin() + pos, v.end());
}
void print(Point p){
    cerr << p.x << " " << p.y << "\n";
}
bool fun(Point p,int n)
{
    int idx = 1;
    if(pointOnsegment(v[0],v[n-1],p)) return 1;
    if(cross(v[0],v[n-1],p) < 0) return 0;
    if(cross(v[0],v[1],p) > 0) return 0;
    int l = 1, r= n - 2;
    int ans = -1;
    while(r >= l)
    {
        int mid = l + (r-l)/2;
        if(cross(v[0],v[mid],p) <= 0) l = mid+1, ans = mid;
        else r=mid-1;
    }
    if(ans == -1) return 0;
    return (cross(v[ans],v[(ans+1)%n],p) <= 0);
}
double area(Point a, Point b, Point c)
{
    return 0.5*abs(a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y));
}
void solve()
{
    int n,m; cin >> n >> m;
    vector<Point> vans(n);
    for(int i=0; i < n; ++i)
    {
        cin >> vans[i].x >> vans[i].y;
    }
    for(int i=0; i < m; ++i) cin >> v[i].x >> v[i].y;
    convex_hull(v);
    prepare(v.size());
    m = v.size();
    int ans = 0;
    for(int i=0; i < n; ++i) ans += fun(vans[i],m);
    cout << ans << "\n";
}
int32_t main()
{
    int t=1; //cin >> t;
    while(t--)
    {
        solve();
    }
}

