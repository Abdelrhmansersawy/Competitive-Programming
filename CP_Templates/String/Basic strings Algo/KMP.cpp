//
//  main.cpp
//
#include "bits/stdc++.h"
using namespace std;

struct KMP {
    vector<int> F;
    string pat;
    int patSz;

    KMP(string &pat) : pat(pat) {
        patSz = (int)pat.size();
        F = vector<int>(patSz + 1, 0);
        build();
    }

    int getFulier(int len, char c) {
        while (len && pat[len] != c) len = F[len - 1];
        len += (pat[len] == c);
        return len;
    }

    void build() {
        F[0] = 0;
        for (int i = 1; i < patSz; ++i) {
            F[i] = getFulier(F[i - 1], pat[i]);
        }
    }

    vector<int> match(string &str) {
        int len = 0;
        vector<int> ret;

        for (int i = 0; i < (int)str.size(); ++i) {
            len = getFulier(len, str[i]);

            if (len == patSz) {
                ret.push_back(i - len + 1); // Zero-Based
                len = F[len - 1];
            }
        }

        return ret;
    }
};


int main() {
    return 0;
}
