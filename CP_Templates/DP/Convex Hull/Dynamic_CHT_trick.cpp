#include <iostream>
#include <set>
#include <climits>

using ll = long long;
using namespace std;

/*
 * LineContainer (Dynamic Convex Hull Trick)
 * -----------------------------------------
 * Adds lines y = kx + m and queries for the maximum (or minimum) value
 * at a given x in O(log n) time. Slopes can be added in any order.
 */

struct Line {
	// `mutable` allows p to be changed inside the set.
	mutable ll k, m, p;

	bool operator<(const Line& other) const { return k < other.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	bool is_min = false;
	LineContainer(bool is_min_mode = false) : is_min(is_min_mode) {}

	static const ll INF = LLONG_MAX;

	// Integer division that floors result correctly for negative numbers.
	ll div(ll a, ll b) {
		return a / b - ((a > 0) != (b > 0) && a % b);
	}

	bool isect(iterator x, iterator y) {
		if (y == end()) {
			x->p = INF;
			return false;
		}
		if (x->k == y->k) {
			x->p = (x->m > y->m) ? INF : -INF;
		} else {
			x->p = div(y->m - x->m, x->k - y->k);
		}
		return x->p >= y->p;
	}

	void add(ll k, ll m) {
		if (is_min) {
			k = -k;
			m = -m;
		}
		auto z = insert({k, m, 0});
		auto y = z++;

		// Remove lines made redundant by the new line.
		while (isect(y, z)) {
			z = erase(z);
		}
		if (y != begin()) {
			auto x = prev(y);
			if (isect(x, y)) {
				isect(x, erase(y));
			}
		}
		auto x = begin();
		if (y != x) {
			x = prev(y);
			while (y != begin() && isect(x, y)) {
				y = erase(y);
				x = prev(y);
			}
		}
	}

	ll query(ll x) {
		if (empty()) {
			return is_min ? LLONG_MAX : LLONG_MIN;
		}
		auto l = *lower_bound(x);
		ll res = l.k * x + l.m;
		return is_min ? -res : res;
	}
};
