#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;
template<class T> using ordered_set = tree<T, null_type , less_equal<T> , rb_tree_tag , tree_order_statistics_node_update> ;
int solve(string &s1 , string &s2){
	if(s1.size() != s2.size() || count(s1.begin() , s1.end() , '1') != count(s2.begin() , s2.end() , '1')){
		return INT32_MAX; // Two strings can't be equal 
	}
	ordered_set<int> pos[2];
	for(int i = 0; i < s1.size(); ++i){
		pos[s1[i] == '1'].insert(i);
	}
	ll ans = 0;
	for(auto &ch : s2){
		int f = (ch == '1');
		assert(pos[f].size());
		int i = *pos[f].find_by_order(0);
		int ope = pos[f ^ 1].order_of_key(i);
		ans += ope;
		pos[f].erase( pos[f].lower_bound(i - 1) );
	}
	return ans;
}
