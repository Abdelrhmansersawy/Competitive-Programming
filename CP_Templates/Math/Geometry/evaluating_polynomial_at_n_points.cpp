//evalating a polynomial at a number of points under a mod, the length of the polynomial is a power of 2
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n;
ll m, q, a[1 << 20], q_pow[1 << 20];

vector<ll> dft(int k = 1, int idx = 0) {
	if (k == n) return {a[idx]};
	else {
		vector<ll> even = dft(k * 2, idx);
		vector<ll> odd = dft(k * 2, idx | k);

		int mid = n / k / 2;
		vector<ll> ans;
		for (int i = 0; i < 2 * mid; i++)
			ans.push_back((even[i % mid] + q_pow[k * i] * odd[i % mid] % m) %
			              m);
		return ans;
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m >> q;
	for (int i = 0; i < n; i++) cin >> a[i];

	q_pow[0] = 1;
	for (int i = 1; i < n; i++) q_pow[i] = q * q_pow[i - 1] % m;

	vector<ll> ans = dft();
	ll tot = 0;
	for (ll i : ans) tot = (tot + i) % m;
	cout << tot << '\n';
	for (int i = 1; i < n; i++) cout << ans[i] << ' ';
	cout << ans[0];
	return 0;
}
