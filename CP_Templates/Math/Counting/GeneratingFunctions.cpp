#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int G   = 3;

int addmod(int a,int b){ a+=b; if(a>=MOD) a-=MOD; return a; }
int submod(int a,int b){ a-=b; if(a<0) a+=MOD; return a; }
int mulmod(long long a,long long b){ return int((a*b)%MOD); }

int fpow(int a,long long e){
    int r=1;
    while(e){
        if(e&1) r=mulmod(r,a);
        a=mulmod(a,a);
        e>>=1;
    }
    return r;
}

int invmod(int a){ return fpow(a,MOD-2); }

using poly = vector<int>;

void ntt(poly &a,bool invert){
    int n = (int)a.size();
    static vector<int> rev;
    static vector<int> roots{0,1};

    if((int)rev.size()!=n){
        int k = __builtin_ctz(n);
        rev.assign(n,0);
        for(int i=0;i<n;i++)
            rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
    }
    if((int)roots.size()<n){
        int k = __builtin_ctz(roots.size());
        roots.resize(n);
        while((1<<k)<n){
            int z = fpow(G,(MOD-1)>>(k+1));
            for(int i=1<<(k-1); i<(1<<k); i++){
                roots[2*i]   = roots[i];
                roots[2*i+1] = mulmod(roots[i],z);
            }
            k++;
        }
    }

    for(int i=0;i<n;i++)
        if(i<rev[i]) swap(a[i],a[rev[i]]);

    for(int len=1; len<n; len<<=1){
        for(int i=0;i<n; i+=2*len){
            for(int j=0;j<len;j++){
                int u=a[i+j];
                int v=mulmod(a[i+j+len], roots[len+j]);
                a[i+j]     = addmod(u,v);
                a[i+j+len] = submod(u,v);
            }
        }
    }
    if(invert){
        reverse(a.begin()+1,a.end());
        int inv_n = invmod(n);
        for(int &x:a) x=mulmod(x,inv_n);
    }
}

poly conv(poly a, poly b){
    if(a.empty() || b.empty()) return {};
    int need = (int)a.size() + (int)b.size() - 1;
    int n=1;
    while(n<need) n<<=1;
    a.resize(n); b.resize(n);
    ntt(a,false); ntt(b,false);
    for(int i=0;i<n;i++) a[i]=mulmod(a[i],b[i]);
    ntt(a,true);
    a.resize(need);
    return a;
}

poly diff(const poly &a){
    int n=(int)a.size();
    if(!n) return {};
    poly r(n-1);
    for(int i=1;i<n;i++) r[i-1]=mulmod(a[i],i);
    return r;
}

poly integ(const poly &a){
    int n=(int)a.size();
    poly r(n+1);
    static vector<int> invs{0,1};
    if((int)invs.size() < n+1){
        int cur = invs.size();
        invs.resize(n+1);
        for(int i=cur;i<=n;i++)
            invs[i]=mulmod(MOD-MOD/i, invs[MOD%i]);
    }
    for(int i=0;i<n;i++) r[i+1]=mulmod(a[i], invs[i+1]);
    return r;
}

poly invpoly(const poly &a,int n){
    poly r(1);
    r[0]=invmod(a[0]);
    int cur=1;
    while(cur<n){
        cur<<=1;
        poly f(min((int)a.size(),cur));
        for(int i=0;i<(int)f.size();i++) f[i]=a[i];
        poly g = r;
        f = conv(f,g);
        if((int)f.size()>cur) f.resize(cur);
        for(int i=0;i<cur;i++) f[i]=submod(0,f[i]);
        f[0]=addmod(f[0],2);
        r = conv(r,f);
        if((int)r.size()>cur) r.resize(cur);
    }
    r.resize(n);
    return r;
}

poly logpoly(const poly &a,int n){
    poly der = diff(a);
    poly inva = invpoly(a,n);
    poly q = conv(der,inva);
    if((int)q.size()>n-1) q.resize(n-1);
    poly r = integ(q);
    if((int)r.size()>n) r.resize(n);
    return r;
}

poly exppoly(const poly &f,int n){
    poly g(1); g[0]=1;
    int cur=1;
    while(cur<n){
        int m = cur<<1;
        poly g_trunc = g;
        if((int)g_trunc.size()>cur) g_trunc.resize(cur);
        poly ln_g = logpoly(g_trunc,m);
        poly f_trunc(min((int)f.size(), m));
        for(int i=0;i<(int)f_trunc.size();i++) f_trunc[i]=f[i];
        if((int)ln_g.size()<m) ln_g.resize(m);
        if((int)f_trunc.size()<m) f_trunc.resize(m);
        for(int i=0;i<m;i++) ln_g[i]=submod(f_trunc[i], ln_g[i]);
        ln_g[0]=addmod(ln_g[0],1);
        g = conv(g, ln_g);
        if((int)g.size()>m) g.resize(m);
        cur=m;
    }
    g.resize(n);
    return g;
}

// truncated exp: E(U) = sum_{i=0}^K U^i / i!  up to degree <= deg
poly truncated_exp(const poly &U,int K,int deg){
    int N = deg;
    poly res(N+1);
    poly power(N+1);
    power[0]=1;
    vector<int> fact(K+1), invfact(K+1);
    fact[0]=1;
    for(int i=1;i<=K;i++) fact[i]=mulmod(fact[i-1],i);
    invfact[K]=invmod(fact[K]);
    for(int i=K;i>0;i--) invfact[i-1]=mulmod(invfact[i],i);
    for(int i=0;i<=K;i++){
        int coef = invfact[i];
        for(int j=0;j<=N;j++)
            res[j] = addmod(res[j], mulmod(power[j],coef));
        if(i==K) break;
        power = conv(power,U);
        if((int)power.size()>N+1) power.resize(N+1);
    }
    return res;
}

// Example 1: connected labeled graphs (A001187)
vector<int> connected_graphs(int N){
    vector<int> fact(N+1),invfact(N+1);
    fact[0]=1;
    for(int i=1;i<=N;i++) fact[i]=mulmod(fact[i-1],i);
    invfact[N]=invmod(fact[N]);
    for(int i=N;i>0;i--) invfact[i-1]=mulmod(invfact[i],i);

    poly F(N+1);
    for(int n=0;n<=N;n++){
        long long edges = 1LL*n*(n-1)/2;
        int fn = fpow(2,edges);
        F[n] = mulmod(fn, invfact[n]);   // EGF coeff
    }
    poly C = logpoly(F,N+1);             // C(x) = log F(x)
    vector<int> c(N+1);
    for(int n=0;n<=N;n++)
        c[n] = mulmod(C[n], fact[n]);    // c_n = C_n * n!
    return c;
}

// Example 2: rooted labeled trees with at most K children per node
// Spec: T(x) = x * sum_{i=0}^K T(x)^i / i!
// Solve by Newton on power series
vector<int> rooted_trees_children_leq_K(int N,int K){
    if(N==0) return vector<int>(1,0);
    poly T(N+1);
    T[0]=0;
    if(N>=1) T[1]=1;
    int cur = 2;
    while(cur<=N){
        int m = min(cur<<1, N+1);
        poly U = T;
        if((int)U.size()<m) U.resize(m,0);
        else U.resize(m);

        poly E  = truncated_exp(U,K,m-1);
        poly F(m);
        for(int i=0;i<m;i++) F[i] = U[i];
        for(int i=1;i<m;i++) F[i] = submod(F[i], E[i-1]);

        poly Ep = truncated_exp(U,max(K-1,0),m-1);
        poly Fp(m);
        Fp[0]=1;
        for(int i=1;i<m;i++) Fp[i] = submod(0, Ep[i-1]);

        poly invFp = invpoly(Fp,m);
        poly delta = conv(F,invFp);
        if((int)delta.size()>m) delta.resize(m);
        for(int i=0;i<m;i++) U[i] = submod(U[i], delta[i]);

        T.swap(U);
        cur = m;
    }
    T.resize(N+1);
    vector<int> fact(N+1), ans(N+1);
    fact[0]=1;
    for(int i=1;i<=N;i++) fact[i]=mulmod(fact[i-1],i);
    for(int n=1;n<=N;n++) ans[n] = mulmod(T[n], fact[n]);
    return ans;
}

int main(){
    int N = 10;

    auto c = connected_graphs(N);
    cout << "Connected labeled graphs c_n for n=1.." << N << ":\n";
    for(int n=1;n<=N;n++)
        cout << "n=" << n << " -> " << c[n] << "\n";

    int K = 3; // max children per node
    auto t = rooted_trees_children_leq_K(N,K);
    cout << "\nRooted labeled trees with at most "
         << K << " children per node (t_n for n=1.." << N << "):\n";
    for(int n=1;n<=N;n++)
        cout << "n=" << n << " -> " << t[n] << "\n";
}
