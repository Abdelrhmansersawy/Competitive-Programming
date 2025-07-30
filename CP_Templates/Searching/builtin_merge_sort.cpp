#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> vec1 = {1, 3, 5};
    vector<int> vec2 = {2, 4, 6};
    vector<int> merged(vec1.size() + vec2.size());

    // Both vec1 and vec2 must be sorted
    merge(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), merged.begin());

    for (int x : merged) cout << x << ' ';
    // Output: 1 2 3 4 5 6
}
