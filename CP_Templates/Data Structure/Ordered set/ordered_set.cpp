/*
    Title: Ordered Set Templates using PBDS
    Theme: Indexed Set / Multiset with order_of_key, find_by_order, lower_bound, upper_bound, erase
    Requires:
        - g++ compiler with -std=c++17 or higher
        - #include <ext/pb_ds/assoc_container.hpp>
        - #include <ext/pb_ds/tree_policy.hpp>
    Notes:
        - order_of_key(x): # of elements strictly < x
        - find_by_order(k): iterator to k-th (0-indexed) smallest element
        - lower_bound(x): iterator to first element >= x
        - upper_bound(x): iterator to first element > x
        - erase(iterator) or erase(value): removes element(s)
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // PBDS main file
#include <ext/pb_ds/tree_policy.hpp>     // tree_order_statistics_node_update
using namespace std;
using namespace __gnu_pbds;

/// Strict ordered set — like std::set
template<class T>
using order_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

/// Ordered multiset — allows duplicates
template<class T>
using multi_order_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

/// Ordered set of pairs — useful for tracking duplicates using indices
template<class T1, class T2 = int>
using pair_order_set = tree<pair<T1, T2>, null_type, less_equal<pair<T1, T2>>, rb_tree_tag, tree_order_statistics_node_update>;

/// Usage Example
int main() {
    // order_set example
    order_set<int> s;
    s.insert(10);
    s.insert(20);
    s.insert(30);
    
    // order_of_key(x)
    cout << "s.order_of_key(25) = " << s.order_of_key(25) << "\n"; // 2
    
    // find_by_order(k)
    cout << "*s.find_by_order(1) = " << *s.find_by_order(1) << "\n"; // 20
    
    // lower_bound(x) and upper_bound(x)
    auto it_lb = s.lower_bound(20);  // first >= 20
    auto it_ub = s.upper_bound(20);  // first > 20
    if(it_lb != s.end()) cout << "lower_bound(20) = " << *it_lb << "\n";
    if(it_ub != s.end()) cout << "upper_bound(20) = " << *it_ub << "\n";
    
    // erase by value
    s.erase(20);
    cout << "After erase(20), s contains:";
    for(auto v : s) cout << " " << v;
    cout << "\n";
    
    // multi_order_set example
    multi_order_set<int> ms;
    ms.insert(5);
    ms.insert(5);
    // erase one occurrence of 5
    ms.erase(ms.find_by_order(ms.order_of_key(5)));

    // pair_order_set example
    pair_order_set<int> ps;
    ps.insert({3, 1});
    ps.insert({3, 2});
    ps.insert({5, 1});
    
    cout << "ps.order_of_key({4,0}) = " << ps.order_of_key({4,0}) << "\n";
    
    return 0;
}
