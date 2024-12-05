struct RollbackUF {
   vector<int> e;              // Parent/size array (-ve size, +ve parent)
   vector<pair<int,int>> st;   // History for rollback (index, prev value)
   
   RollbackUF(int n) : e(n, -1) {} 
   
   int size(int x) {          // Returns size of set containing x
       return -e[find(x)]; 
   }
   
   int find(int x) {          // Gets root/representative of x's set
       return e[x] < 0 ? x : find(e[x]); 
   }
   
   int time() {               // Current operation count
       return st.size(); 
   }
   
   void rollback(int t) {     // Undo operations after time t
       for(int i = time(); i > t; i--) {
           e[st[i-1].first] = st[i-1].second;
       }
       st.resize(t);
   }
   
   bool join(int a, int b) {  // Union sets of a and b, return true if joined
       a = find(a);
       b = find(b);
       if(a == b) return false;
       
       if(e[a] > e[b]) swap(a, b);  // a will be root
       
       st.push_back({a, e[a]});     // Save state for rollback
       st.push_back({b, e[b]});
       e[a] += e[b];                // Update size
       e[b] = a;                    // Set parent
       return true;
   }
};
