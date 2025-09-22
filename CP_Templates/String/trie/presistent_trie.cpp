const int BIT = 30; // bits 0..30 (adjust if you want 64-bit)

struct Node {
    Node* child[2];
    int   s; // count / size
    Node(int val = 0) {
        child[0] = child[1] = nullptr;
        s = val;
    }
};

// helpers (your style)
Node* getL(Node* x){ return x == nullptr ? nullptr : x->child[0]; }
Node* getR(Node* x){ return x == nullptr ? nullptr : x->child[1]; }
int   getS(Node* x){ return x == nullptr ? 0 : x->s; }
Node* newLeaf(int val){ return new Node(val); }

Node* newPar(Node* l, Node* r){
    Node* res = new Node();
    res->child[0] = l;
    res->child[1] = r;
    res->s = getS(l) + getS(r);
    return res;
}

// persistent insert (adds +1 occurrence of value x)
Node* add(Node* root, int x, int bit = BIT){
    if(bit < 0){
        // leaf level: increment count
        return newLeaf(getS(root) + 1);
    }
    int b = (x >> bit) & 1;
    if(b == 0){
        return newPar(add(getL(root), x, bit - 1), getR(root));
    } else {
        return newPar(getL(root), add(getR(root), x, bit - 1));
    }
}

// persistent erase (removes one occurrence of x if present).
// If x does not exist in this version, returns original root unchanged.
Node* erase(Node* root, int x, int bit = BIT){
    if(root == nullptr || getS(root) == 0) return root; // nothing to erase

    // quick existence check: ensure path exists and counts > 0
    Node* check = root;
    for(int b = bit; b >= 0; --b){
        if(!check) return root;
        int bitv = (x >> b) & 1;
        check = bitv ? getR(check) : getL(check);
        if(!check || getS(check) == 0) return root; // not present
    }

    // actual persistent decrement
    if(bit < 0){
        return newLeaf(getS(root) - 1);
    }
    int pb = (x >> bit) & 1;
    if(pb == 0){
        return newPar(erase(getL(root), x, bit - 1), getR(root));
    } else {
        return newPar(getL(root), erase(getR(root), x, bit - 1));
    }
}


// return -1 if empty; else maximum xor value (x ^ y) with y from trie
int max_xor_value(Node* root, int x){
    if(root == nullptr || getS(root) == 0) return -1;
    Node* u = root;
    int res = 0;
    for(int b = BIT; b >= 0; --b){
        int bitv = (x >> b) & 1;
        int want = bitv ^ 1;
        Node* nxt = want ? getR(u) : getL(u);
        if(nxt && getS(nxt) > 0){
            res |= (1 << b);
            u = nxt;
        } else {
            Node* other = bitv ? getR(u) : getL(u);
            if(!other) break;
            u = other;
        }
    }
    return res;
}

// min xor value (returns -1 if empty)
int min_xor_value(Node* root, int x){
    if(root == nullptr || getS(root) == 0) return -1;
    Node* u = root;
    int res = 0;
    for(int b = BIT; b >= 0; --b){
        int bitv = (x >> b) & 1;
        Node* prefer = bitv ? getR(u) : getL(u); // prefer same bit
        if(prefer && getS(prefer) > 0){
            u = prefer;
        } else {
            Node* other = bitv ? getL(u) : getR(u);
            if(!other) break;
            res |= (1 << b);
            u = other;
        }
    }
    return res;
}
