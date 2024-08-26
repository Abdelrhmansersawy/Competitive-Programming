struct AhoCorasick{
    enum{ alpha = 26 , first = 'a'}; // change it
    struct Node{
        int nxt[alpha];
        int suflink; // store no. nlong suffix node
        int start = -1, end = -1; // end: represent index in backup od longest suffix pattern 
        int nmatches = 0; // no. of matched string
        Node(int v){ memset(nxt , v , sizeof nxt); }
    };
    vector<Node> v;
    vector<int> backup; // backup indices of strings into end point vecter into trie.
    void insert(string &s , int id){
        assert(s.size()); // Pattern mustn't be empty
        int node = 0;
        for(auto &c : s){
            int &m = v[node].nxt[c - first];
            if(m == -1){ node = m = v.size(); v.emplace_back(-1); }
            else node = m;
        }
        if(v[node].end == -1) v[node].start = id;
        backup.emplace_back(v[node].end); // I don't know what's used for?
        v[node].end = id;
        v[node].nmatches++;
    }
    AhoCorasick(vector<string> &pat): v(1 , -1) {
        for(int i = 0; i < pat.size(); ++i) insert(pat[i] , i);
        v[0].suflink = v.size(); // probability of error here
        v.emplace_back(0);

        queue<int> q;
        q.push(0); // push root
        while(q.size()){
            int node = q.front(); q.pop();
            int prv = v[node].suflink; 
            for(int i = 0; i < alpha; ++i){
                int &x = v[node].nxt[i] , y = v[prv].nxt[i];
                if(x == -1) x = y;
                else{
                    v[x].suflink = y;
                    (v[x].end == -1 ? v[x].end : backup[v[x].start]) = v[y].end;
                    v[x].nmatches += v[y].nmatches;
                    q.push(x);
                }
            }
        }
    }
    vector<int> find(string &word){
        int node = 0;
        vector<int> res;
        for(auto &c : word){
            node = v[node].nxt[c - first];
            res.push_back(v[node].end);
        }
        return res;
    }
    vector<vector<int>> findAll(vector<string>&pat, string word) {
        vector<int> r = find(word);
        vector<vector<int>> res(word.size());
        for(int i = 0; i < word.size(); ++i){
            int ind = r[i];
            while (ind != -1) {
                res[i - pat[ind].size() + 1].push_back(ind);
                ind = backup[ind];
            }
        }
        return res;
    }
};
