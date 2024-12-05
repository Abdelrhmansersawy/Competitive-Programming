#include <bits/stdc++.h>
using namespace std;

class SparseSegtree {
  private:
	struct Node {
		int freq = 0;
		int lazy = 0;
		int left = -1;
		int right = -1;
	};
	vector<Node> tree;
	const int n;
	int timer = 0;

	int comb(int a, int b) { return a + b; }

	void apply(int cur, int len, int val) {
		if (val == 1) {
			tree[cur].lazy = val;
			tree[cur].freq = len * val;
		}
	}

	void push_down(int cur, int l, int r) {
		if (tree[cur].left == -1) {
			tree[cur].left = ++timer;
			tree.push_back(Node());
		}
		if (tree[cur].right == -1) {
			tree[cur].right = ++timer;
			tree.push_back(Node());
		}
		int m = (l + r) / 2;
		apply(tree[cur].left, m - l + 1, tree[cur].lazy);
		apply(tree[cur].right, r - m, tree[cur].lazy);
		tree[cur].lazy = 0;
	}

	void range_set(int cur, int l, int r, int ql, int qr, int val) {
		if (qr < l || ql > r) { return; }
		if (ql <= l && r <= qr) {
			apply(cur, r - l + 1, val);
		} else {
			push_down(cur, l, r);
			int m = (l + r) / 2;
			range_set(tree[cur].left, l, m, ql, qr, val);
			range_set(tree[cur].right, m + 1, r, ql, qr, val);
			tree[cur].freq =
			    comb(tree[tree[cur].left].freq, tree[tree[cur].right].freq);
		}
	}

	int range_sum(int cur, int l, int r, int ql, int qr) {
		if (qr < l || ql > r) { return 0; }
		if (ql <= l && r <= qr) { return tree[cur].freq; }
		push_down(cur, l, r);
		int m = (l + r) / 2;
		return comb(range_sum(tree[cur].left, l, m, ql, qr),
		            range_sum(tree[cur].right, m + 1, r, ql, qr));
	}

  public:
	SparseSegtree(int n, int q = 0) : n(n) {
		if (q > 0) { tree.reserve(2 * q * __lg(n)); }
		tree.push_back(Node());
	}

	void range_set(int ql, int qr, int val) { range_set(0, 0, n - 1, ql, qr, val); }

	int range_sum(int ql, int qr) { return range_sum(0, 0, n - 1, ql, qr); }
};

int main() {
	int query_num;
	cin >> query_num;
	const int RANGE_SIZE = 1e9;
	SparseSegtree st(RANGE_SIZE + 1, query_num);

	int c = 0;
	for (int i = 0; i < query_num; i++) {
		int type, x, y;
		cin >> type >> x >> y;
		if (type == 1) {
			c = st.range_sum(x + c, y + c);
			cout << c << '\n';
		} else if (type == 2) {
			st.range_set(x + c, y + c, 1);
		}
	}
}
