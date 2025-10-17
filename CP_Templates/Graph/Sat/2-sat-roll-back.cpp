// Global 2-SAT solver used inside binary search.
// build(): create base vars & seg-tree links once — O(n)
// can(mid): add edges for current mid, solve, then rollback — O(V+E)
// Rollback with s.E.resize(tmp_edges);  // no new vars inside can()
// Example:
//    tmp = s.E.size()
//    add edges for this mid
//    ok = s.solve()
//    s.E.resize(tmp)

// Why faster: reuse vars & base edges, rollback cheaply, avoid rebuilding graph each probe.
