int add(int a, int b) {
    return (a + b);
}

int sub(int a, int b) {
    return (a - b);
}

void fwht(vector<int> &a, int inv, int f) {
    int sz = a.size();
    for (int len = 1; 2 * len <= sz; len <<= 1) {
        for (int i = 0; i < sz; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                int x = a[i + j];
                int y = a[i + j + len];

                if (f == 0) {
                    if (!inv)  a[i + j] = y, a[i + j + len] = add(x,  y);
                    else  a[i + j] = sub(y, x), a[i + j + len] = x;
                }
                else if (f == 1) {
                    if (!inv)  a[i + j + len] = add(x, y);
                    else  a[i + j + len] = sub(y, x);
                }
                else {
                    a[i + j] = add(x, y);
                    a[i + j + len] = sub(x, y);
                }
            }
        }
    }
}
// for example to get all pairs xor send a and b as the frequency array of values
vector<int> mul(vector<int> a, vector<int> b, int f) { // 0:AND, 1:OR, 2:XOR
    int sz = a.size();
    fwht(a, 0, f);  fwht(b, 0, f);
    vector<int> c(sz);
    for (int i = 0; i < sz; ++i) {
        c[i] = a[i] * b[i];
    }
    fwht(c, 1, f);
    if (f == 2) {
        for (int i = 0; i < sz; ++i) {
            c[i] = c[i] / sz;
        }
    }
    return c;
}
