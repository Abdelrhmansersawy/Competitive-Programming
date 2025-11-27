/**
 * kitamasa — computes the n-th term of a linear recurrence.
 *
 * You are given a linear recurrence of order k:
 *      A_n = c_1*A_{n-1} + c_2*A_{n-2} + ... + c_k*A_{n-k}
 *
 * The polynomial `f` is the characteristic polynomial of the recurrence:
 *      f(x) = x^k - c_1*x^(k-1) - c_2*x^(k-2) - ... - c_k
 *
 * The array `a` contains the first k values:
 *      a[0] = A_0, a[1] = A_1, ... , a[k-1] = A_{k-1}
 *
 * The function returns A_n modulo `mod`.
 * It uses Kitamasa's algorithm, which repeatedly squares and multiplies
 * polynomials to compute the coefficients expressing A_n as a combination of
 * the initial values A_0..A_{k-1}.
 *
 * Complexity: O(k^2 log n)
 * or O(K logK logN)  when you manipulate polynomial with FFT.
 */


const int mod = 1e9 + 7;
using poly = vector<long long>;
poly Mul(const poly &a, const poly &b){
    poly ret(a.size() + b.size() - 1);
    for(int i=0; i<a.size(); i++) for(int j=0; j<b.size(); j++) {
        ret[i+j] = (ret[i+j] + a[i] * b[j]) % mod;
    }
    return ret;
}
 
poly Div(const poly &a, const poly &b){
    poly ret(a.begin(),a.end());
    for(int i=ret.size()-1; i>=b.size()-1; i--) for(int j=0; j<b.size(); j++) {
        ret[i+j-b.size()+1] = (ret[i+j-b.size()+1] - (ret[i] * b[j] % mod) + mod) % mod;
    }
    ret.resize(b.size()-1);
    return ret;
}
 
/// A_{n} = \sum c_{i}A_{n-i} = \sum d_{i}A_{i}
long long kitamasa(poly f, poly a, long long n){
    poly d = {1};
    poly xn = {0, 1};
    while(n){
        if(n & 1) d = Div(Mul(d, xn), f);
        n >>= 1; xn = Div(Mul(xn, xn), f);
    }
    long long ret = 0;
    for(int i=0; i<a.size(); i++) ret = (ret + (a[i] * d[i])%mod)%mod;
    return ret;
}
