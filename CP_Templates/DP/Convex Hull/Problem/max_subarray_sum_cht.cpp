// Given array A[1..N], process Q queries:
// STRENGTH X → add X to all elements; ASSESS L R → print max(0, max subarray sum in A[L..R]).
// N, Q ≤ 3e5, |A[i]|, |X| ≤ 1e9 → use segment tree with lazy propagation.

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(i , st , ed) for(int i = st; i < ed; i++)
#define f first
#define s second
#define all(v) v.begin() , v.end()

typedef ll ftype;
typedef complex<ftype> point;


#define x real
#define y imag

ftype dot(point a, point b) { return (conj(a) * b).x(); }
ftype cross(point a, point b) { return (conj(a) * b).y(); }


struct CHT {
    vector<point> hull, vecs;
    size_t mono_ptr = 0;
    bool is_min = false;

    CHT(bool is_min_mode = false) : is_min(is_min_mode) {}

    void add_line(ftype k, ftype b) {
        if (is_min) k = -k, b = -b;
        point nw = {k, b};
        while (hull.size() >= 2 &&
               cross(hull.back() - hull[hull.size()-2], nw - hull.back()) >= 0)
            hull.pop_back(), vecs.pop_back();
        if (!hull.empty()) vecs.push_back(point(0,1)*(nw - hull.back()));
        hull.push_back(nw);
    }

    ftype get(ftype x) {
        if (hull.empty()) return is_min ? (ftype)1e18 : (ftype)-1e18;
        point q = {x,1};
        int lo = 0, hi = (int)hull.size() - 1;
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            ftype v1 = dot(q, hull[mid]);
            ftype v2 = dot(q, hull[mid+1]);
            if (v1 <= v2) lo = mid + 1;
            else hi = mid;
        }
        ftype res = dot(q, hull[lo]);
        return is_min ? -res : res;
    }

    ftype get_mono(ftype x) {
       if (hull.empty()) return is_min ? (ftype)1e18 : (ftype)-1e18;
        while (mono_ptr + 1 < hull.size() &&
               dot({x,1}, hull[mono_ptr]) <= dot({x,1}, hull[mono_ptr+1])) mono_ptr++;
        while (mono_ptr > 0 &&
               dot({x,1}, hull[mono_ptr]) <= dot({x,1}, hull[mono_ptr-1])) mono_ptr--;
        ftype res = dot({x,1}, hull[mono_ptr]);
        return is_min ? -res : res;
    }

    void clear() {
        hull.clear(); vecs.clear(); mono_ptr = 0;
    }
};

// + : union/merge 
CHT operator+(const CHT &A, const CHT &B){
    vector<pair<ftype,ftype>> L; L.reserve(A.hull.size()+B.hull.size());
    for(auto &p: A.hull) L.emplace_back(p.x(), p.y());
    for(auto &p: B.hull) L.emplace_back(A.is_min==B.is_min ? p.x() : -p.x(),
                                         A.is_min==B.is_min ? p.y() : -p.y());
    sort(L.begin(), L.end(), [](auto &a, auto &b){
        if (a.first != b.first) return a.first < b.first;
        return a.second > b.second;
    });
    CHT R(A.is_min);
    int n = L.size();
    for(int i=0;i<n;++i) if(i==0 || L[i].first!=L[i-1].first) R.add_line(L[i].first, L[i].second);
    return R;
}


// * : Minkowski (convolution)
CHT operator*(const CHT &A_in, const CHT &B_in){
    if(A_in.hull.empty()) return B_in;
    if(B_in.hull.empty()) return A_in;

    auto ha = A_in.hull; auto va = A_in.vecs;
    auto hb = B_in.hull; auto vb = B_in.vecs;
    point cur = ha[0] + hb[0];
    vector<point> merged; merged.reserve(va.size()+vb.size());
    int ia=0, ib=0, na=va.size(), nb=vb.size();
    while(ia<na || ib<nb){
        if(ia<na && ib<nb){
            ftype c = cross(va[ia], vb[ib]);
            if(c < 0) merged.push_back(va[ia++]);
            else if(c > 0) merged.push_back(vb[ib++]); 
            else { merged.push_back(va[ia]+vb[ib]); ++ia; ++ib; } 
        } else if(ia<na) merged.push_back(va[ia++]);
        else merged.push_back(vb[ib++]);
    }
    CHT R(A_in.is_min);
    R.hull.clear(); R.vecs.clear();
    R.hull.push_back(cur);
    point rot_back = point(0,-1);
    for(auto &v: merged){
        point diff = rot_back * v;
        R.vecs.push_back(v);
        R.hull.push_back(R.hull.back() + diff);
    }
    return R;
}


struct cht_node{
    CHT pref, suf, best, sum;
    cht_node() = default;

    cht_node(long long x){
        pref.add_line(0, 0);
        pref.add_line(1, x);
        
        suf.add_line(0, 0);
        suf.add_line(1, x);
        
        best.add_line(0, 0);
        best.add_line(1, x);
        
        sum.add_line(1, x); 
    }

    cht_node operator+(const cht_node &o) const {
        cht_node r;
        r.sum  = sum * o.sum;
        r.pref = pref + (sum * o.pref);
        r.suf  = o.suf + (suf * o.sum);
        r.best = best + o.best + (suf * o.pref);
        return r;
    }
};


struct Node{
    ftype pref , suf , best , sum;

    Node operator+(const Node &o) const{
        Node res;
        res.pref = max(pref , o.pref + sum);
        res.suf = max(o.suf , o.sum + suf);
        res.best = max({best , o.best , suf + o.pref});
        res.sum = sum + o.sum;
        return res;
    }
};

Node build_from_cht(cht_node &cur , ftype x){
    Node res;
    res.pref = cur.pref.get(x);
    res.suf = cur.suf.get(x);
    res.sum = cur.sum.get(x);
    res.best = cur.best.get(x);
    return res;
}


const int N = 3e5+9;
cht_node tree[4*N];
int n;
void build(vector<ll>&a , int x = 0 ,int l = 0, int r = n){
    if(r-l==1){ tree[x] = cht_node(a[l]); return; }
    int mid = (l+r)/2;
    build(a,2*x+1,l,mid);
    build(a,2*x+2,mid,r);
    tree[x] = tree[2*x+1] + tree[2*x+2];
}


Node query(int lx  , int rx , ftype slp , int x = 0 , int l = 0 , int r = n){
    if(l >= lx && r <= rx) return build_from_cht(tree[x] , slp);
    int mid = (l+r)/2;
    if(rx <= mid) return query(lx,rx,slp,2*x+1,l,mid);
    if(lx >= mid) return query(lx,rx,slp,2*x+2,mid,r);
    return query(lx,rx,slp,2*x+1,l,mid) + query(lx,rx,slp,2*x+2,mid,r);
}


int main(){
    ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif

    cin >> n;
    int q; cin >> q;
    vector<ll> a(n);
    for(auto &x : a) cin >> x;
    
    build(a);

    ftype slp = 0; 
    while(q--){
        string type; cin >> type;
        if(type == "STRENGTH"){
            ll x; cin >> x;
            slp += x;
        }else{
            int l , r; cin >> l >> r;
            --l; 
            cout << query(l,r,slp).best << '\n';
        }
    }
}
