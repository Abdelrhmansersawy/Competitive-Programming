struct Hun {
     int n;
     vector<int> fx, fy, d, l, r, arg, trace;
     vector<vector<int>> c;
     queue<int> q;
     int st = 0, fin = 0;
 
     Hun(int _n, int _m) {
         n = max(_n, _m);
         fx.assign(n + 1, 0);
         fy.assign(n + 1, 0);
         d.assign(n + 1, 0);
         l.assign(n + 1, 0);
         r.assign(n + 1, 0);
         arg.assign(n + 1, 0);
         trace.assign(n + 1, 0);
         c.assign(n + 1, vector<int>(n + 1));
         for (int i = 1; i <= n; ++i) {
             fy[i] = l[i] = r[i] = 0;
             for (int j = 1; j <= n; ++j) {
                 c[i][j] = oo;
             }
         }
     }
 
     void add(int u, int v, int co) {
         c[u][v] = min(c[u][v], co);
     }
     int get_c(int u, int v) {
         return c[u][v] - fx[u] - fy[v];
     }
 
     void bfs() {
         while (!q.empty()) {
             q.pop();
         }
         q.push(st);
         for (int i = 0; i <= n; ++i) {
             trace[i] = 0;
         }
         for (int i = 1; i <= n; ++i) {
             d[i] = get_c(st, i), arg[i] = st;
         }
         fin = 0;
     }
 
     void find() {
         while (!q.empty()) {
             int u = q.front();
             q.pop();
             for (int v = 1; v <= n; ++v) {
                 if(!trace[v]) {
                     int w = get_c(u, v);
                     if(!w) {
                         trace[v] = u;
                         if(!r[v]) {
                             fin = v;
                             return;
                         }
                         q.push(r[v]);
                     }
                     if(d[v] > w) {
                         d[v] = w;
                         arg[v] = u;
                     }
                 }
             }
         }
     }
 
     void sub() {
         int delt = oo;
         for (int v = 1; v <= n; ++v) {
             if(trace[v] == 0 && d[v] < delt) delt = d[v];
         }
 
         fx[st] += delt;
         for (int v = 1; v <= n; ++v) {
             if(trace[v]) {
                 int u = r[v];
                 fy[v] -= delt;
                 fx[u] += delt;
             }
             else d[v] -= delt;
         }
 
         for (int v = 1; v <= n; ++v) {
             if(!trace[v] && !d[v]) {
                 trace[v] = arg[v];
                 if(!r[v]) {
                     fin = v;
                     return;
                 }
                 q.push(r[v]);
             }
         }
     }
 
     void en() {
         do {
             int u = trace[fin];
             int nxt = l[u];
             l[u] = fin;
             r[fin] = u;
             fin = nxt;
         } while (fin);
     }
 
     pair<int, int> max_mat() {
         for (int u = 1; u <= n; ++u) {
             fx[u] = c[u][1];
             for (int v = 1; v <= n; ++v) {
                 fx[u] = min(fx[u], c[u][v]);
             }
         }
 
         for (int v = 1; v <= n; ++v) {
             fy[v] = c[1][v] - fx[1];
             for (int u = 1; u <= n; ++u) {
                 fy[v] = min(fy[v], c[u][v] - fx[u]);
             }
         }
 
         for (int u = 1; u <= n; ++u) {
             st = u;
             bfs();
             while (!fin) {
                 find();
                 if(!fin) sub();
             }
             en();
         }
 
         int ans = 0, cnt = 0;
         for (int i = 1; i <= n; ++i) {
             if(c[i][l[i]] != oo) ans += c[i][l[i]], ++cnt;
             else l[i] = 0;
         }
         return {ans, cnt};
     }
};
