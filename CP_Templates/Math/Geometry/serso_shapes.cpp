struct circle{
    pt c; T r;
    void get(){ getPt(c); cin >> r; }
};
struct square{
    pt a , b;
    void get(){ getPt(a) ;getPt(b); }
};
struct traingle{
    pt a , b , c;
    void get(){ getPt(a); getPt(b); getPt(c); }
};
 
inline int sgn(T x){ return (x > EPS) - (x < -EPS); }
inline T dot(pt a, pt b){ return (a * conj(b)).real(); }
inline T cross(pt a, pt b){ return (a * conj(b)).imag(); }
inline bool on_seg(pt a, pt b, pt p){
    if(sgn(cross(b-a, p-a)) != 0) return false;
    return (min(a.X,b.X)-EPS <= p.X && p.X <= max(a.X,b.X)+EPS
         && min(a.Y,b.Y)-EPS <= p.Y && p.Y <= max(a.Y,b.Y)+EPS);
}
inline T dist_ps(pt a, pt b, pt p){
    pt v = b - a;
    if(abs(v) < EPS) return abs(p - a);
    T t = dot(p-a, v) / (T)std::norm(v);
    if(t < 0) return abs(p - a);
    if(t > 1) return abs(p - b);
    return abs(p - (a + v * t));
}
inline bool seg_inter(pt a, pt b, pt c, pt d){
    T c1 = cross(b-a, c-a), c2 = cross(b-a, d-a);
    T c3 = cross(d-c, a-c), c4 = cross(d-c, b-c);
    int s1 = sgn(c1), s2 = sgn(c2), s3 = sgn(c3), s4 = sgn(c4);
    if(s1*s2 < 0 && s3*s4 < 0) return true;
    if(s1==0 && on_seg(a,b,c)) return true;
    if(s2==0 && on_seg(a,b,d)) return true;
    if(s3==0 && on_seg(c,d,a)) return true;
    if(s4==0 && on_seg(c,d,b)) return true;
    return false;
}
inline void make_ccw(vector<pt>& P){
    if(P.size()==3){
        if(cross(P[1]-P[0], P[2]-P[0]) < 0) swap(P[1], P[2]);
    }else{
        pt m = (P[0]+P[1]+P[2]+P[3])/ (T)4;
        sort(P.begin(), P.end(), [&](const pt& u, const pt& v){
            return atan2((u-m).Y, (u-m).X) < atan2((v-m).Y, (v-m).X);
        });
    }
}
inline vector<pt> square_pts(const square& s){
    pt a = s.a, b = s.b;
    pt m = (a + b) / (T)2;
    pt p = (a - b) / (T)2;
    pt r = p * pt(0,1);
    vector<pt> P = { m + p, m + r, m - p, m - r };
    make_ccw(P);
    return P;
}
inline vector<pt> tri_pts(const traingle& t){
    vector<pt> P = { t.a, t.b, t.c };
    make_ccw(P);
    return P;
}
inline T point_poly_dist(const vector<pt>& P, pt q){
    int n = (int)P.size();
    bool ok = true;
    for(int i=0;i<n;i++){
        if(cross(P[(i+1)%n]-P[i], q-P[i]) < -EPS){ ok = false; break; }
    }
    if(ok) return 0;
    T d = 1e30L;
    for(int i=0;i<n;i++){
        d = min(d, dist_ps(P[i], P[(i+1)%n], q));
    }
    return d;
}
inline bool poly_intersect(const vector<pt>& A, const vector<pt>& B){
    int n = (int)A.size(), m = (int)B.size();
    for(int i=0;i<n;i++){
        pt a = A[i], b = A[(i+1)%n];
        for(int j=0;j<m;j++){
            pt c = B[j], d = B[(j+1)%m];
            if(seg_inter(a,b,c,d)) return true;
        }
    }
    auto inside = [&](const vector<pt>& P, pt q){
        int k = (int)P.size();
        for(int i=0;i<k;i++){
            if(cross(P[(i+1)%k]-P[i], q-P[i]) < -EPS) return false;
        }
        return true;
    };
    if(inside(A, B[0])) return true;
    if(inside(B, A[0])) return true;
    return false;
}
inline T poly_poly_dist(const vector<pt>& A, const vector<pt>& B){
    if(poly_intersect(A,B)) return 0;
    T d = 1e30L;
    int n=(int)A.size(), m=(int)B.size();
    for(int i=0;i<n;i++) d = min(d, point_poly_dist(B, A[i]));
    for(int j=0;j<m;j++) d = min(d, point_poly_dist(A, B[j]));
    return d;
}
 
T dis(circle a , circle b){
    T d = abs(a.c-b.c);
    return max((T)0 , d - (a.r + b.r));
}
T dis(traingle a , circle b){
    auto P = tri_pts(a);
    T d = point_poly_dist(P, b.c);
    return max((T)0, d - b.r);
}
T dis(square a , circle b){
    auto P = square_pts(a);
    T d = point_poly_dist(P, b.c);
    return max((T)0, d - b.r);
}
T dis(square a , traingle b){
    auto A = square_pts(a);
    auto B = tri_pts(b);
    return poly_poly_dist(A, B);
}
