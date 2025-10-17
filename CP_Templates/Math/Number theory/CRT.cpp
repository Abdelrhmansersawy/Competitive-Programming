ll egcd(ll a, ll b, ll &x, ll &y)
{
    if(!b)
    {
        x = 1, y = 0; return a >= 0 ? a : -a;
    }
    ll x1, y1;
    ll g = egcd(b, a % b, x1, y1);
    x = y1, y = x1 - (a/b) * y1;
    return g;
}
bool crt_merge(__int128& x, __int128& m, ll r, ll mod)
{
    if(m <= 0)
    {
        x = 0, m = 1;
    }
    ll mmod = (ll) (m % (__int128)mod);
    ll rhs = (ll)(((__int128)r - (x % mod + mod) % mod + mod) % mod);
    ll u,v,g = egcd(mmod, mod, u, v);
    if(rhs % g) return 0;
    ll dm = mod / g;
    ll inv = (u % dm + dm) % dm;
    ll t = (ll)(((__int128)(rhs/g) * inv) % dm);
    __int128 nx = x + m * (__int128)t;
    __int128 nm = m * (__int128)dm;
    nx%=nm;
    if(nx<0) nx+=nm;
    x=nx; m=nm;
    return 1;
}
