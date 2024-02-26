const int mods[] = {1000000007, 1000000009, 1000000021, 1000000033, 1000000087, 1000000093, 1000000097, 1000000103, 1000000123, 1000000181}, b = 10, K = 6;
array<int, K> gethash(string &s) {
	array<int, K> ans, pw;
	for (int k = 0; k < K; k++) {
		ans[k] = 0;
		pw[k] = 1;
	}
	for (auto i : s) {
		for (int k = 0; k < K; k++) {
			ans[k] += 1ll * pw[k] * (i - '0') % mods[k];
			ans[k] %= mods[k];
			pw[k] = (lll) pw[k] * b % mods[k];
		}
	}
	return ans;
}
