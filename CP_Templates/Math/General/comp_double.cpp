#define ld long double
const ld EPS = 1e-6;
int dcmp(const ld &a, const ld &b) {
    // Double compare
    if (fabs(a - b) < EPS)
        return 0;
 
    return (a > b ? 1 : -1);
}
