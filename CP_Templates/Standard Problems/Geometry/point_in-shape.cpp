/*
    Problem Link: https://codeforces.com/gym/104447/problem/H
    You are given a polygon of n, vertices and q queries.

    Each query consists of a point (x,y)
    and you have to check if it is inside (including the borders) or outside the polygon.

    The points of the polygon are given in clockwise order with the property that either xi=xi−1
    or yi=yi−1
    (but not both), indicating that the edges are parallel to either the x- or y-axis, Also no two edges intersect
    (endpoints are not considered into the intersections).
    
    The first line of the input contains an integer n 4≤n≤1e5),representing the number of vertices in the polygon.

    The next n lines each contain two integers xi and yi (0≤xi,yi≤106), representing the x- and y-coordinates, respectively, of the i
    -th vertex of the polygon in clockwise order.
    The next q lines each contain two integers x and y (0≤x,y≤1e6), representing the x- and y-coordinates,
    respectively, of a point to be checked whether it is inside or outside the polygon.
*/
#include<iostream>
#include <bits/stdc++.h>

#define ll long long
#define IO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;
const int N = 1e6 + 5, mod = 1e9 + 7, M = 17, inf = 2e9, sq = 632;
vector<vector<int> > x[N], y[N], queries[N];

bool inside(vector<vector<int> > &v, int val) {
    int low = 0, high = v.size() - 1;
    while (low <= high) {
        int mid = low + high >> 1;
        if (v[mid][1] < val) {
            low = mid + 1;
        } else if (v[mid][0] > val) {
            high = mid - 1;
        } else {
            return true;
        }
    }
    return false;
}

int bit[N];

void add(int idx, int val) {
    for (; idx < N; idx += idx & -idx) {
        bit[idx] += val;
    }
}

void add_range(int l, int r) {
    if (l > r)return;
    add(l, 1);
    add(r + 1, -1);
}

int query(int idx) {
    int ans = 0;
    for (; idx; idx -= idx & -idx) {
        ans += bit[idx];
    }
    return ans;
}

map<int, int> freq[2];

void doWork() {
    int n;
    cin >> n;
    vector<pair<int, int> > v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first >> v[i].second;
        v[i].second++;
    }
    for (int i = 0; i < n; i++) {
        if (v[i].first == v[(i + 1) % n].first) {
            int y1 = v[i].second, y2 = v[(i + 1) % n].second;
            x[v[i].first].push_back({min(y1, y2), max(y1, y2), y1 < y2});
        } else {
            int x1 = v[i].first, x2 = v[(i + 1) % n].first;
            y[v[i].second].push_back({min(x1, x2), max(x1, x2)});
        }
    }
    for (int i = 0; i < N; i++) {
        sort(x[i].begin(), x[i].end());
        sort(y[i].begin(), y[i].end());
    }
    int q;
    cin >> q;
    vector<int> ans(q, 0);
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        b++;
        if (inside(x[a], b) || inside(y[b], a)) {
            ans[i] = true;
        } else {
            queries[a].push_back({b, i});
        }
    }
    for (int i = 0; i < N; i++) {
        for (auto j: x[i]) {
            add_range(j[0] + 1, j[1] - 1);
            freq[j[2]][j[0]]++;
            freq[j[2]][j[1]]++;
        }
        for (auto j: queries[i]) {
            int cnt = query(j[0]);
            int cntUP = freq[1][j[0]];
            int cntDown = freq[0][j[0]];
            cnt += (max(cntDown, cntUP) - min(cntDown, cntUP)) / 2;
            ans[j[1]] = cnt % 2;
        }
    }
    for (auto i: ans) {
        cout << (i ? "YES\n" : "NO\n");
    }
}


int main() {
    IO
    int t = 1;
  //  cin >> t;
    for (int i = 1; i <= t; i++) {
        //    cout << "Case #" << i << ": ";
        doWork();
    }
}
