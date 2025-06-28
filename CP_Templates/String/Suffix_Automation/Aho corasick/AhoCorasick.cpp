struct AhoCorasick {
    // Modify these values based on input alphabet
    // alpha: size of alphabet (26 for lowercase letters)
    // first: first character of alphabet ('a' for lowercase letters)
    enum { alpha = 26, first = 'a' };
    
    struct Node {
        int nxt[alpha];        // Next state transition for each character
        int suflink;           // Suffix link points to longest proper suffix
        int start = -1;        // Start index of pattern in original array
        int end = -1;          // Index in backup of longest matched suffix pattern
        int nmatches = 0;      // Count of matched strings ending at this node
        
        Node(int v) { 
            memset(nxt, v, sizeof nxt); 
        }
    };
    
    vector<Node> v;           // Stores all nodes of the trie
    vector<int> backup;       // Stores pattern indices with longest matching suffixes
                             // Returns -1 if no match exists
                             // Note: All patterns must be distinct when using backup
    
    // Inserts a pattern into the automaton
    // Time: O(|s|) where |s| is pattern length
    void insert(string &s, int id) {
        assert(s.size());     // Empty patterns not allowed
        int node = 0;
        for(auto &c : s) {
            int &m = v[node].nxt[c - first];
            if(m == -1) { 
                node = m = v.size(); 
                v.emplace_back(-1); 
            }
            else node = m;
        }
        if(v[node].end == -1) v[node].start = id;
        backup.emplace_back(v[node].end);
        v[node].end = id;
        v[node].nmatches++;
    }
    
    // Builds Aho-Corasick automaton from patterns
    // Time: O(26N) where N = sum of all pattern lengths
    // - Creates suffix links
    // - Allows duplicate patterns
    // - For large alphabets, split symbols into chunks with sentinel bits
    AhoCorasick(vector<string> &pat): v(1, -1) {
        for(int i = 0; i < pat.size(); ++i) 
            insert(pat[i], i);
            
        v[0].suflink = v.size();    // Dummy node as suffix link of root
        v.emplace_back(0);
        
        queue<int> q;
        q.push(0);                   // BFS from root to build suffix links
        
        while(q.size()) {
            int node = q.front(); 
            q.pop();
            int prv = v[node].suflink;
            
            for(int i = 0; i < alpha; ++i) {
                int &x = v[node].nxt[i], y = v[prv].nxt[i];
                if(x == -1) x = y;
                else {
                    v[x].suflink = y;
                    (v[x].end == -1 ? v[x].end : backup[v[x].start]) = v[y].end;
                    v[x].nmatches += v[y].nmatches;
                    q.push(x);
                }
            }
        }
    }
    
    // Returns index of longest word ending at each position, or -1 if none
    // Time: O(|word|) where |word| is text length
    vector<int> find(string &word) {
        int node = 0;
        vector<int> res;
        for(auto &c : word) {
            node = v[node].nxt[c - first];
            res.push_back(v[node].end);
        }
        return res;
    }
    
    // Finds all patterns starting at each position (shortest first)
    // Time: O(NM) where N = text length, M = number of matches
    // Can find up to N√N matches if no duplicate patterns
    vector<vector<int>> findAll(vector<string> &pat, string word) {
        vector<int> r = find(word);
        vector<vector<int>> res(word.size());
        for(int i = 0; i < word.size(); ++i) {
            int ind = r[i];
            while(ind != -1) {
                res[i - pat[ind].size() + 1].push_back(ind);
                ind = backup[ind];
            }
        }
        return res;
    }
};
