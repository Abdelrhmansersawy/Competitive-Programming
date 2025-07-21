// - str_mod(s, m): O(N)
// - str_div2(s): O(N)
// - str_add(s, x): O(N)
// - str_sub1(s): O(N)
// - str_multiply(s, x): O(N)
// - str_sub(s, x): O(N), assumes s >= x and x is a small integer
// - two_string_add(a, b): O(max(N, M))
// - two_string_sub(a, b): O(max(N, M)), assumes a >= b
// - two_string_mul(a, b): O(N * M)



using ll = long long;

// Calculates (s % m) for a large number s.
int str_mod(const string &s, int m) {
    ll res = 0;
    for (char c : s) res = (res * 10 + (c - '0')) % m;
    return (int)res;
}

// Divides a large number s by 2.
string str_div2(const string &s) {
    string q;
    int carry = 0;
    for (char c : s) {
        int d = carry * 10 + (c - '0');
        q.push_back('0' + d / 2);
        carry = d % 2;
    }
    size_t pos = q.find_first_not_of('0');
    return pos == string::npos ? "0" : q.substr(pos);
}

// Adds a small integer x to a large number s.
string str_add(string s, int x) {
    int i = s.length() - 1;
    int carry = x;
    while (i >= 0 && carry > 0) {
        int d = (s[i] - '0') + carry;
        s[i] = '0' + (d % 10);
        carry = d / 10;
        i--;
    }
    while (carry > 0) {
        s.insert(0, 1, '0' + (carry % 10));
        carry /= 10;
    }
    return s;
}

// Subtracts 1 from a large number s.
string str_sub1(const string &s) {
    if (s == "0") return "0";
    string res = s;
    int i = res.size() - 1;
    while (i >= 0) {
        if (res[i] > '0') {
            res[i]--;
            break;
        } else {
            res[i] = '9';
            i--;
        }
    }
    size_t pos = res.find_first_not_of('0');
    return pos == string::npos ? "0" : res.substr(pos);
}


// Multiplies a large number s by a small integer x.
string str_multiply(const string& s, int x) {
    if (s == "0" || x == 0) return "0";
    string res;
    int carry = 0;
    for (int i = s.length() - 1; i >= 0; --i) {
        int p = (s[i] - '0') * x + carry;
        res.push_back('0' + (p % 10));
        carry = p / 10;
    }
    while (carry > 0) {
        res.push_back('0' + (carry % 10));
        carry /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

// Subtracts a small integer x from a large number s. Assumes s >= x.
string str_sub(string s, int x) {
    int i = s.length() - 1;
    int borrow = 0;
    while (i >= 0) {
        int diff = (s[i] - '0') - (x % 10) - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        s[i] = '0' + diff;
        x /= 10;
        i--;
        if (x == 0 && borrow == 0) break;
    }
    size_t pos = s.find_first_not_of('0');
    return pos == string::npos ? "0" : s.substr(pos);
}

// Adds two large numbers.
string two_string_add(const string& a, const string& b) {
    string res;
    int i = a.length() - 1, j = b.length() - 1, carry = 0;
    while (i >= 0 || j >= 0 || carry > 0) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        res.push_back('0' + (sum % 10));
        carry = sum / 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

// Subtracts two large numbers. Assumes a >= b.
string two_string_sub(const string& a, const string& b) {
    string res;
    int i = a.length() - 1, j = b.length() - 1, borrow = 0;
    while (i >= 0) {
        int diff = (a[i] - '0') - borrow;
        if (j >= 0) diff -= (b[j--] - '0');
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res.push_back('0' + diff);
        i--;
    }
    reverse(res.begin(), res.end());
    size_t pos = res.find_first_not_of('0');
    return pos == string::npos ? "0" : res.substr(pos);
}

// Multiplies two large numbers.
string two_string_mul(const string& a, const string& b) {
    if (a == "0" || b == "0") return "0";
    vector<int> res(a.length() + b.length(), 0);
    int i_a = 0;
    for (int i = a.length() - 1; i >= 0; i--) {
        int carry = 0;
        int n1 = a[i] - '0';
        int i_b = 0;
        for (int j = b.length() - 1; j >= 0; j--) {
            int n2 = b[j] - '0';
            int sum = n1 * n2 + res[i_a + i_b] + carry;
            carry = sum / 10;
            res[i_a + i_b] = sum % 10;
            i_b++;
        }
        if (carry > 0) res[i_a + i_b] += carry;
        i_a++;
    }
    int i = res.size() - 1;
    while (i >= 0 && res[i] == 0) i--;
    if (i == -1) return "0";
    string s = "";
    while (i >= 0) s += to_string(res[i--]);
    return s;
}
