/* HLD
 - Operates on vertices (node values), 0-based, root = 0.
 - Segment-tree ranges are inclusive [l..r].
 - API: update_point(u,val), update_range_pos(l,r,val), query_path(u,v) -> Node
 - Assumes SegTree, Node and any automaton globals exist.
*/

struct HLD {
    int N, cur=0;
    vector<int> par, depth, head, pos, sz;
    // r is inclusive in the segment-tree / HLD
    SegTree down, up;
    HLD(vector<vector<int>>& adj, vector<int>& init)
        : N(adj.size()), par(N), depth(N), head(N), pos(N), sz(N), down(N), up(N)
    {
        dfs_sz(0,0,adj);
        dfs_hld(0,0,adj);
        for (int i = 0; i < N; ++i) update_point(i, init[i]);
    }
    void dfs_sz(int u,int p, vector<vector<int>>& a){
        sz[u]=1; par[u]=p; depth[u] = (u==p ? 0 : depth[p]+1);
        for (size_t i=0;i<a[u].size();++i){
            int v=a[u][i]; if(v==p) continue;
            dfs_sz(v,u,a); sz[u]+=sz[v];
            if(a[u].size() && (a[u][0]==p || sz[v] > sz[a[u][0]])) swap(a[u][i], a[u][0]);
        }
    }
    void dfs_hld(int u,int h, vector<vector<int>>& a){
        head[u]=h; pos[u]=cur++;
        for(int v: a[u]) if(v!=par[u]) dfs_hld(v, v==a[u][0]?h:v, a);
    }

    // update a single vertex or a range of vertices (by position)
    void update_point(int u, int c){
        down.update_point(pos[u], c);
        up.update_point(N-1-pos[u], c);
    }

    void update_range_pos(int lpos, int rpos, int c){ 
        down.update_range(lpos, rpos, c);
        // update mirrored positions for up
        int L = N-1-rpos, R = N-1-lpos;
        up.update_range(L, R, c);
    }

    // query returns composed Node 
    Node query_path(int u,int v){
        Node left, right; int x=u,y=v;
        while(head[x] != head[y]){
            if(depth[head[x]] > depth[head[y]]){
                int l=N-1-pos[x], r=N-1-pos[head[x]];
                left = left + up.query(l,r);
                x = par[head[x]];
            } else {
                int l=pos[head[y]], r=pos[y];
                right = down.query(l,r) + right;
                y = par[head[y]];
            }
        }
        if(depth[x] > depth[y]){
            int l=N-1-pos[x], r=N-1-pos[y];
            left = left + up.query(l,r);
        } else {
            int l=pos[x], r=pos[y];
            right = down.query(l,r) + right;
        }
        return left + right;
    }
};
