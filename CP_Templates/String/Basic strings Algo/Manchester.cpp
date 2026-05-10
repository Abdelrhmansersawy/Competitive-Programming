struct Manacher {
// P[i] : the radius of the longest palindrome centered at t[i] , t is one base
// P[2 * j + 1] : palindrome info for jth character in string s , zero base
// P[2 * j + 2] : palindrome info for the gap between j , j + 1 in string s
	vector<int> p;
	
	void build(string &s) {
		string t;
		t.reserve(s.size() * 2 + 1); // Optimization to prevent reallocation
		for(auto &val : s) t += '#', t += val;
		t += '#';
		
		int n = (int)t.size();
		p.resize(n, 1);
		int l = 1, r = 1;
		
		for(int i = 1; i < n; i++) {
			p[i] = (i < r) ? min(r - i, p[l + r - i]) : 0;
			
			while(i - p[i] >= 0 and i + p[i] < n and t[i + p[i]] == t[i - p[i]]) p[i]++;
			
			if(p[i] + i > r) {
				r = i + p[i];
				l = i - p[i];
			}
		}
	}
	
	int GetLongest(int center, bool odd = true) {
		int NewCenter = 2 * center + !odd + 1;
		return p[NewCenter] - 1;
	}
	
	bool IsPalindrome(int l, int r) {
		return (r - l + 1) <= GetLongest((l + r) / 2, l % 2 == r % 2);
	}
};
