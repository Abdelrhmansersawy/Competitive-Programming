#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef complex<ld> Point;

inline ld cross(const Point& a, const Point& b) { return a.real() * b.imag() - a.imag() * b.real(); }
inline ld lengthSqr(const Point& p) { return norm(p); }
inline ld triangleAreaBH(ld base, ld height) { return base * height / 2.0L; }
inline ld triangleArea2SidesAngle(ld a, ld b, ld angle) { return fabs(a * b * sin(angle)) / 2.0L; }
inline ld triangleArea2AnglesSide(ld ang1, ld ang2, ld side) {
    return fabs(side * side * sin(ang1) * sin(ang2) / (2.0L * sin(ang1 + ang2)));
}
inline ld triangleArea3Sides(ld a, ld b, ld c) {
    ld s = (a + b + c) / 2.0L;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}
inline ld cosRule(ld a, ld b, ld c) {
    ld denom = 2.0L * b * c;
    if (fabs(denom) < 1e-9) return 0.0L;
    return acos(min(max((b * b + c * c - a * a) / denom, -1.0L), 1.0L));
}

int main() { return 0; }
