// only in less_equal lower_bound work such as upper_bound;
// by *find_by_order given index --> val ;
// by order_of_key given  value --> index ;
// erase and insert in log(n) ;
// used norm policy data strc when no dublcate the same element; 

#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;
template<class T> using ordered_set = tree<T, null_type , less_equal<T> , rb_tree_tag , tree_order_statistics_node_update> ;
struct ordered__set{

	ordered_set< ll > se ;
	void erase( ll val ){  
		if( se.size() == 0 || *se.find_by_order( se.size() - 1 ) < val || *se.lower_bound( val - 1 ) != val  ) return ;
		se.erase( se.lower_bound( --val ) ) ; 
	}
	int lower_bound( ll val ){ // log --> return index ;
		if( se.size() == 0 || *se.find_by_order( se.size() - 1 ) < val  ) return -1;
		return se.order_of_key( *se.lower_bound( --val ) ) ;
	}
	int upper_bound( ll val ){ return  lower_bound( val + 1ll ) ; }
	void insert( ll val ){ se.insert( val ); }
    ll operator[](int idx) { return *se.find_by_order( idx ) ;}
	int size( ){ return se.size(); }
	void clr(  ){ se.clear() ; } 
};
