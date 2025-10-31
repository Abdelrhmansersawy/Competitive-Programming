// + : union/merge 
CHT operator+(const CHT &A, const CHT &B){
    assert(A.is_min == B.is_min);

    vector<pair<ftype,ftype>> L;
    L.reserve(A.hull.size() + B.hull.size());

    for (auto &p : A.hull) L.emplace_back(p.x(), p.y());
    for (auto &p : B.hull) L.emplace_back(p.x(), p.y());

    sort(L.begin(), L.end(), [](auto &a, auto &b){
        if (a.first != b.first) return a.first < b.first;
        return a.second > b.second;
    });

    CHT R(A.is_min);
    for (size_t i = 0; i < L.size(); ++i)
        if (i == 0 || L[i].first != L[i-1].first)
            R.add_line(L[i].first, L[i].second);

    return R;
}



// * : Minkowski (convolution)
// If each CHT represents f(x) = max_i (a_i * x + b_i),
// and g(x) = max_j (c_j * x + d_j),
// then (f * g)(x) = max_{i,j}((a_i + c_j) * x + (b_i + d_j)
CHT operator*(const CHT &A_in, const CHT &B_in){
    assert(A_in.is_min == B_in.is_min);

    if (A_in.hull.empty()) return B_in;
    if (B_in.hull.empty()) return A_in;

    const auto &ha = A_in.hull;
    const auto &va = A_in.vecs;
    const auto &hb = B_in.hull;
    const auto &vb = B_in.vecs;

    point cur = ha[0] + hb[0];

    vector<point> merged;
    merged.reserve(va.size() + vb.size());

    int ia = 0, ib = 0, na = (int)va.size(), nb = (int)vb.size();
    while (ia < na && ib < nb) {
        ftype c = cross(va[ia], vb[ib]);
        if (c < 0) merged.push_back(va[ia++]);
        else if (c > 0) merged.push_back(vb[ib++]);
        else { merged.push_back(va[ia] + vb[ib]); ++ia; ++ib; }
    }
    while (ia < na) merged.push_back(va[ia++]);
    while (ib < nb) merged.push_back(vb[ib++]);

    CHT R(A_in.is_min);
    R.hull.reserve(merged.size() + 1);
    R.vecs.reserve(merged.size());

    R.hull.push_back(cur);
    for (auto &v : merged) {
        // rot_back * v  ==  point(v.y, -v.x)
        point diff{ v.y, -v.x };
        R.vecs.push_back(v);
        R.hull.push_back(R.hull.back() + diff);
    }

    return R;
}
