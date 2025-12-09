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
