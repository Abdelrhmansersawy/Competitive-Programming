struct rect {
	long long x, y, a;
	bool operator<(rect o) {
		return make_pair(x, -y) <= make_pair(o.x, -o.y);
	}
};
 
struct mxCHT {
	deque<long long> B;
	deque<long long> A;
 
	bool cmp(int l1, int l2, int l3) {
		return (B[l3] - B[l1]) * (long double) (A[l1] - A[l2])
				>= (B[l2] - B[l1]) * (long double) (A[l1] - A[l3]);
	}
	void add(long long a, long long b) {
		A.push_back(a);
		B.push_back(b);
		while (A.size() >= 3 && cmp(A.size() - 3, A.size() - 2, A.size() - 1)) {
			A.erase(A.end() - 2);
			B.erase(B.end() - 2);
		}
	}
 
	long long f(long long x, int l) {
		return A[l] * x + B[l];
	}
 
	long long query(long long x) {
		int lo = 0, hi = (int) A.size() - 2, res = A.size() - 1;
 
		while (lo <= hi) {
			int md = (lo + hi) >> 1;
			if (f(x, md) <= f(x, md + 1)) {
				lo = md + 1;
			} else {
				res = md;
				hi = md - 1;
			}
		}
		return f(x, res);
	}
 
	long long queryMonotonic(long long x) {
		while (A.size() > 1 && f(x, 0) < f(x, 1)) {
			A.pop_front(), B.pop_front();
		}
		if (A.empty())
			return LLONG_MIN;
		return f(x, 0);
	}
};
