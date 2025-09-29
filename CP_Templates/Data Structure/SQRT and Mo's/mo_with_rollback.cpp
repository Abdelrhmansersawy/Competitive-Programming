/*
  Mo with Rollback — Complexity Note
  - Queries: vector<array<int,3>> {l, r, id}, 0-based inclusive

  Let M = items, Q = queries, B = block size, c = cost per apply_item.
  Work ≈ (M^2 / B + Q * B) * c + Q log Q + snapshots_cost.
  - If B = √M:
        Work ≈ (M^(3/2) + Q√M) * c + Q log Q + snapshots_cost
  - Optimal (balance terms): B ≈ M / √Q
  - Default: B = √M (simple and good in practice)

*/


vector<pair<int,int>> items;
vector<int> answers_global;

int dsa_get_snapshot() {
    // Return the current snapshot id from your DSA.
    // Must be usable later in rollback.
    // e.g., return dsa.snapshot();
    return -1;
}

int get_answer() {

    return 0;
}

void reset_state() {
    // Reset or re-init your DSA / problem state before processing a new bucket.
    // Called once per bucket. Example: dsa.reset(n);
    // IMPORTANT: this must put the DSA in a clean state 
}

void insert(int idx) {
   
}

void roll_back(int no_snapshot) {
    // dsa_rollback_to(no_snapshot);
}

void run_Mo(vector<array<int,3>> &queries) {
    int M = (int)items.size(); 
    int Q = (int)queries.size();
    answers_global.assign(Q, 0);
    if (M == 0) {
        for (auto &q : queries) answers_global[q[2]] = get_answer();
        return;
    }

    int BLOCK = max(1, (int)(sqrt(M) + 1));
    int buckets_cnt = (M + BLOCK - 1) / BLOCK;
    vector<vector<array<int,3>>> buckets(buckets_cnt);
    for (auto &qu : queries) {
        int l = qu[0];
        int b = l / BLOCK;
        if (b < 0) b = 0;
        if (b >= buckets_cnt) b = buckets_cnt - 1;
        buckets[b].push_back(qu);
    }

    for (int b = 0; b < buckets_cnt; ++b) {
        if (buckets[b].empty()) continue;
        sort(buckets[b].begin(), buckets[b].end(), [](const array<int,3>& a, const array<int,3>& bb){
            return a[1] < bb[1];
        });

        reset_state();

        int base = (b + 1) * BLOCK;
        int r = base;

        for (auto qu : buckets[b]) {
            int L = qu[0], R = qu[1], id = qu[2];

            while (r <= R && r < M) {
                insert(r);
                ++r;
            }

            int snap = dsa_get_snapshot();
            int left_end = min(base - 1, R);
            for (int pos = L; pos <= left_end; ++pos) insert(pos);

            answers_global[id] = get_answer();
            roll_back(snap);
        }
    }
}
