#include <bits/stdc++.h>
using namespace std;

int bit[2000005];

void update(int i, int x) {
	for (; i < 2000005; i += i & (-i)) bit[i] += x;
}
int query(int i) {
	int sum = 0;
	for (; i > 0; i -= i & (-i)) sum += bit[i];
	return sum;
}

int n;
vector<array<int, 4>> v;

int main() {
	cin.tie(0)->sync_with_stdio(0);

	cin >> n;
	for (int i = 0, x1, y1, x2, y2; i < n; ++i) {
		cin >> x1 >> y1 >> x2 >> y2;
		if (y1 == y2) v.push_back({y1, 2, x1, x2});
		else {
			v.push_back({y1, 1, x1, 1});
			v.push_back({y2, 3, x1, 1});
		}
	}
	sort(begin(v), end(v));

	long long ans = 0;
	for (auto x : v) {
		x[2] += 1000001, x[3] += 1000001;
		if (x[1] == 1) update(x[2], 1);
		else if (x[1] == 2) ans += query(x[3]) - query(x[2] - 1);
		else update(x[2], -1);
	}
	cout << ans << '\n';
}
