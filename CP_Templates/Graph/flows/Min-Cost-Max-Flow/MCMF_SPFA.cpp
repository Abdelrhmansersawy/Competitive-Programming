template<class T>
struct MCMF {
    struct edge {
        int u, v;
        T cap, cost;

        edge(int _u, int _v, T _cap, T _cost) : u(_u), v(_v), cap(_cap), cost(_cost) {
        }
    };

    int n, s, t;
    T flow, cost;
    vector<vector<int> > g;
    vector<edge> e;
    vector<T> d, potential;
    vector<int> par;
    bool neg;

    MCMF(int _n = 0) {
        n = _n + 5;
        g.assign(n, {});
        neg = false;
    }

    void add_edge(int u, int v, T cap, T cost) {
        if (cost < 0) neg = true;
        g[u].push_back((int) e.size());
        e.emplace_back(u, v, cap, cost);
        g[v].push_back((int) e.size());
        e.emplace_back(v, u, 0, -cost);
    }

    bool dijkstra() {
        T INF = numeric_limits<T>::max() / 4;
        par.assign(n, -1);
        d.assign(n, INF);
        priority_queue<pair<T, int>, vector<pair<T, int> >, greater<> > pq;
        d[s] = 0;
        pq.emplace(0, s);
        while (!pq.empty()) {
            auto [dist, u] = pq.top();
            pq.pop();
            if (dist != d[u]) continue;
            for (int id: g[u]) {
                int v = e[id].v;
                T cap = e[id].cap;
                T w = e[id].cost + potential[u] - potential[v];
                if (cap > 0 && d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    par[v] = id;
                    pq.emplace(d[v], v);
                }
            }
        }
        for (int i = 0; i < n; ++i) if (d[i] < numeric_limits<T>::max() / 4) d[i] += (potential[i] - potential[s]);
        for (int i = 0; i < n; ++i) if (d[i] < numeric_limits<T>::max() / 4) potential[i] = d[i];
        return d[t] < numeric_limits<T>::max() / 4;
    }

    T send_flow(int v, T cur) {
        if (par[v] == -1) return cur;
        int id = par[v];
        int u = e[id].u;
        T f = send_flow(u, min(cur, e[id].cap));
        cost += f * e[id].cost;
        e[id].cap -= f;
        e[id ^ 1].cap += f;
        return f;
    }

    pair<T, T> solve(int _s, int _t, T goal = numeric_limits<T>::max() / 4) {
        s = _s;
        t = _t;
        flow = 0;
        cost = 0;
        potential.assign(n, 0);
        if (neg) {
            T INF = numeric_limits<T>::max() / 4;
            d.assign(n, INF);
            deque<int> q;
            vector<char> inq(n, 0);
            d[s] = 0;
            q.push_back(s);
            inq[s] = 1;
            while (!q.empty()) {
                int u = q.front();
                q.pop_front();
                inq[u] = 0;
                for (int id: g[u]) {
                    int v = e[id].v;
                    T cap = e[id].cap;
                    T w = e[id].cost;
                    if (cap > 0 && d[u] < INF && d[v] > d[u] + w) {
                        d[v] = d[u] + w;
                        if (!inq[v]) {
                            inq[v] = 1;
                            q.push_back(v);
                        }
                    }
                }
            }
            for (int i = 0; i < n; ++i) if (d[i] < numeric_limits<T>::max() / 4) potential[i] = d[i];
        }
        while (flow < goal && dijkstra()) flow += send_flow(t, goal - flow);
        return {flow, cost};
    }
};
