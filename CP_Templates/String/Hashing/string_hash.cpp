const int MOD1 = 1e9+7, MOD2 = 1e9+9;
const int P1 = rnd(1e7, 1e8), P2 = rnd(1e7, 1e8);
const int MAXN = 1e6 + 5;
vector<ll> pw1(MAXN), pw2(MAXN);

void init_hash(){ // call once
    pw1[0]=pw2[0]=1;
    for(int i=1;i<MAXN;i++){
        pw1[i]=pw1[i-1]*P1%MOD1;
        pw2[i]=pw2[i-1]*P2%MOD2;
    }
}

struct Hash {
    vector<ll> ph1,ph2,sh1,sh2;
    void build(const string &s){
        int n=s.size();
        ph1.assign(n,0); ph2.assign(n,0);
        sh1.assign(n,0); sh2.assign(n,0);
        for(int i=0;i<n;i++){
            ll v = s[i]-'a'+1;
            ph1[i] = ((i?ph1[i-1]:0) + v*pw1[i]) % MOD1;
            ph2[i] = ((i?ph2[i-1]:0) + v*pw2[i]) % MOD2;
        }
        for(int i=n-1,j=0;i>=0;i--,j++){
            ll v = s[i]-'a'+1;
            sh1[i] = ((i+1<n?sh1[i+1]:0) + v*pw1[j]) % MOD1;
            sh2[i] = ((i+1<n?sh2[i+1]:0) + v*pw2[j]) % MOD2;
        }
    }
    // hash for s[l..r]
    ull get(int l,int r){
        ll a1 = ph1[r] - (l?ph1[l-1]:0);
        ll a2 = ph2[r] - (l?ph2[l-1]:0);
        if(a1<0)a1+=MOD1; if(a2<0)a2+=MOD2;
        a1 = a1 * pw1[MAXN-1 - l] % MOD1;
        a2 = a2 * pw2[MAXN-1 - l] % MOD2;
        return ( (ull)a1<<32 ) ^ (ull)a2;
    }
    // reverse-hash for s[l..r]
    ull rev(int l,int r){
        int n = sh1.size();
        ll b1 = sh1[l] - (r+1<n?sh1[r+1]:0);
        ll b2 = sh2[l] - (r+1<n?sh2[r+1]:0);
        if(b1<0)b1+=MOD1; if(b2<0)b2+=MOD2;
        b1 = b1 * pw1[MAXN-1 - (n-1-r)] % MOD1;
        b2 = b2 * pw2[MAXN-1 - (n-1-r)] % MOD2;
        return ( (ull)b1<<32 ) ^ (ull)b2;
    }
};
