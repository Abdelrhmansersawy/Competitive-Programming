const int N = 2e5 + 9;
const int mod[] = { (int)1e9 + 7, 998244353 };
int o;  // Which mod wher I current use.
mt19937 random_seed(time(0));
int rnd(int l , int r){
    uniform_int_distribution<int> dist(l, r);
    return dist(random_seed);
}
ll bpw(ll a , ll b ){
    a %= mod[o];
    ll res = 1;
    while(b){
        if(b % 2) res = (res * a) % mod[o];
        a = (a * a) % mod[o];
        b >>= 1;
    }
    return res;
}
struct Mint{
    ll x;
    Mint(ll x = 0){  this->x = x % mod[o]; }
    Mint operator +(const Mint &other) const{ return (x + other.x) % mod[o]; }
    Mint operator -(const Mint &other) const{ return (x - other.x + mod[o]) % mod[o]; }
    Mint operator *(const Mint &other) const{ return (x * other.x) % mod[o]; }
    Mint operator /(const Mint &other) const{ return ( x * bpw(other.x , mod[o] - 2) ) % mod[o]; }
    bool operator ==(const Mint &other) const{ return x == other.x; }
    bool operator !=(const Mint &other) const{ return x != other.x; }
};

Mint p[2] , pw[2][N];
void init(){
    for(o = 0; o < 2; o++){
        p[o] = Mint( rnd(31 , 39) );
        pw[o][0] = Mint(1);
        for(int i = 1; i < N; ++i){
            pw[o][i] = pw[o][i - 1] * p[o];
        }
    }
}
struct Hash{
    Mint pref[2] , suff[2];
    int len;
    Hash(char ch = '?'){
        if(ch == '?'){
            pref[0] = pref[1] = suff[0] = suff[1] = Mint(0);
            len = 0;
            return;
        }
        len = 1;
        for(o = 0;o < 2; ++o){
            pref[o] = suff[o] = Mint(ch - 'a' + 1);
        }
    }
    Hash operator +(const Hash &other) const{
        Hash res;
        res.len = len + other.len;
        for(o = 0;o < 2; ++o){
            res.pref[o] = pref[o] + other.pref[o] * pw[o][len]; 
            res.suff[o] = other.suff[o] + suff[o] * pw[o][other.len]; 
        }
        return res;
    }
    void rev(){
        for(o = 0; o < 2; ++o) swap(pref[o] , suff[o]);
    }
    bool is_palindrome() const{
        for(o = 0; o < 2; ++o){
            if(pref[o] != suff[o]) return false;
        }
        return true;
    }
};
Hash excludePrefix(Hash s1 , Hash s2){
    Hash res;
    res.len = s1.len - s2.len;
    for(o = 0; o < 2; ++o){
        res.pref[o] = s1.pref[o] - s2.pref[o];
        res.pref[o] = res.pref[o] / pw[o][s2.len];

        res.suff[o] = s1.suff[o] - s2.suff[o] * pw[o][s1.len - s2.len];
    }
    return res;
}
Hash excludeSuffix(Hash s1 , Hash s2){
    Hash res;
    res.len = s1.len - s2.len;
    for(o = 0; o < 2; ++o){
        res.pref[o] = s1.pref[o] - s2.pref[o] * pw[o][s1.len - s2.len];

        res.suff[o] = s1.suff[o] - s2.suff[o];
        res.suff[o] = res.suff[o] / pw[o][s2.len]; 
    }
    return res;
}
