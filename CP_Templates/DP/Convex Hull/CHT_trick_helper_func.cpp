// + : union/merge 
CHT operator+(const CHT &A, const CHT &B){
    vector<pair<ftype,ftype>> L; L.reserve(A.hull.size()+B.hull.size());
    for(auto &p: A.hull) L.emplace_back(p.x(), p.y());
    for(auto &p: B.hull) L.emplace_back(A.is_min==B.is_min ? p.x() : -p.x(),
                                         A.is_min==B.is_min ? p.y() : -p.y());
    sort(L.begin(), L.end(), [](auto &a, auto &b){
        if (a.first!=b.first) return a.first<b.first; return a.second>b.second;
    });
    CHT R(A.is_min);
    int n = L.size();
    for(int i=0;i<n;++i) if(i==0 || L[i].first!=L[i-1].first) R.add_line(L[i].first, L[i].second);
    return R;
}

// * : Minkowski (convolution)
// If each CHT represents f(x) = max_i (a_i * x + b_i),
// and g(x) = max_j (c_j * x + d_j),
// then (f * g)(x) = max_{i,j}((a_i + c_j) * x + (b_i + d_j)
CHT operator*(const CHT &A_in, const CHT &B_in){
    if(A_in.hull.empty()||B_in.hull.empty()) return CHT(A_in.is_min);
    auto ha = A_in.hull; auto va = A_in.vecs;
    auto hb = B_in.hull; auto vb = B_in.vecs;
    // if(A_in.is_min!=B_in.is_min){
    //     for(auto &p: hb) p = point(-p.x(), -p.y());
    //     for(auto &v: vb) v = point(-v.x(), -v.y());
    // }
    point cur = ha[0] + hb[0];
    vector<point> merged; merged.reserve(va.size()+vb.size());
    int ia=0, ib=0, na=va.size(), nb=vb.size();
    while(ia<na || ib<nb){
        if(ia<na && ib<nb){
            ftype c = cross(va[ia], vb[ib]);
            if(c>0) merged.push_back(va[ia++]);
            else if(c<0) merged.push_back(vb[ib++]);
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
