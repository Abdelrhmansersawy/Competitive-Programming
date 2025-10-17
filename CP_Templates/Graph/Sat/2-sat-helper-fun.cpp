// Forces at most one of the given (variable,state) pairs to be true
void at_most_one(const vector<pair<int, int> > &v) {
    if (v.size() <= 1) return;
    int last_pref = -1;
    for (int i = 0; i < (int)v.size(); ++i) {
        int x = v[i].first, state = v[i].second;
        int p = add_var();
        add_imply(p, false, x, state ^ 1);
        if (last_pref != -1) {
            add_imply(p, false, last_pref, false);
            add_imply(x, state, last_pref, false);
        }
        last_pref = p;
    }
    int last_suf = -1;
    for (int i = (int)v.size() - 1; i >= 0; --i) {
        int x = v[i].first, state = v[i].second;
        int s = add_var();
        add_imply(s, false, x, state ^ 1);
        if (last_suf != -1) {
            add_imply(s, false, last_suf, false);
            add_imply(x, state, last_suf, false);
        }
        last_suf = s;
    }
}
