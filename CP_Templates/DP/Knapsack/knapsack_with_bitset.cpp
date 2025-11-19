// set compile-time maximum possible sum (user said <= 1e6)
constexpr int N = 1'000'001;

template<int len = 1>
int solve(const vector<int> &v , int all){
    if(v.empty()) return 0;
    // If current bitset size `len` is too small for requested `all`, call a larger instantiation.
    if(len < all)
        return solve< ( (2 * len <= N) ? 2 * len : N ) >(v, all);

    // frequency of values
    map<int,int> frq;
    for(auto &i : v) frq[i]++;

    // binary-split the multiplicities into powers of two items
    vector<int> cur;
    for(auto &[x , f0] : frq){
        int f = f0;
        int need = 1;
        while(f > 0){
            int take = min(need, f);
            f -= take;
            cur.emplace_back(take * x);
            need <<= 1;
        }
    }

    // dp bitset of size `len`
    bitset<len> dp;
    dp.reset();
    dp[0] = 1;
    for(auto &w : cur) {
        dp |= (dp << w);
    }

    // find best achievable sum <= all
    for(int s = all; s >= 0; --s) if(dp[s]) return s;
    return 0;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Example usage:
    // Input: n then n non-negative integers (values). We try to reach sum `all` = total_sum / 2
    // (classic partition / knapsack example). You can change `all` to any target <= N-1.
    int n;
    if(!(cin >> n)) return 0;
    vector<int> a(n);
    long long total = 0;
    for(int i = 0; i < n; ++i){
        cin >> a[i];
        total += a[i];
    }
    if(total >= N){
        cerr << "Error: total sum >= N. Increase constexpr N.\n";
        return 0;
    }

    int all = int(total / 2); // e.g. partition: best <= half
    // call template: starting with default len=1 (recursively grows until >= all)
    int best = solve<>(a, all);

    cout << "best achievable sum <= " << all << " is: " << best << "\n";
    cout << "other partition sum: " << (total - best) << "\n";
    return 0;
}
Quick notes

