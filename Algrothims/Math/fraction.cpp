long long gcd (long long a, long long b) {
  while (b) {
      a %= b;
      swap(a, b);
  }
  return a;
}
struct frac{
  // fraction n / d
  long long n ,d;
  // constructor
  frac(){n = 0; d = 1;} 
  frac(ll n , ll d): n(n) , d(d){simplify();};
  bool operator < (const frac &other) const{
    return n * other.d < d * other.n;
  }
  frac operator + (const frac &f) const{
    frac ans {n * f.d + f.n * d , d * f.d};
    ans.simplify();
    return ans;
  }
  frac operator - (const frac &f) const{
    frac ans {n * f.d - f.n * d , d * f.d};
    ans.simplify();
    return ans;
  }
  void Abs(){n = abs(n); d = abs(d);}
  void simplify(){
    long long g = gcd(abs(n) , abs(d));
    n /= g; d /= g;
  }
};
