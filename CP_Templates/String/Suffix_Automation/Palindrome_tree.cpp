struct Node {
    int len;                              // Length of the palindrome
    int suffLink;                         // Suffix link to longest proper palindromic suffix
    unordered_map<char, int> next;        // Transitions by character
};

class PalindromicTree {
    vector<Node> tree;                    // The tree structure
    string s;                             // Processed string
    int suff;                             // Index of the node representing the current max suffix palindrome
    int n;                                // Current length of string `s`

public:
    PalindromicTree() {
        // Two root nodes:
        // Node 0: length = -1 (imaginary node), suffix link to itself
        // Node 1: length = 0 (empty string), suffix link to node 0
        tree.push_back({-1, 0, {}});
        tree.push_back({0, 0, {}});
        suff = 1;
        n = 0;
    }

    // Adds character `c` and returns true if it created a new palindrome
    bool addChar(char c) {
        s += c;
        n++;
        int cur = suff;

        // Find the largest suffix palindrome of the current string such that
        // s[n - 2 - len] == c (i.e., the current character can extend the palindrome)
        while (true) {
            int curlen = tree[cur].len;
            if (n - 2 - curlen >= 0 && s[n - 2 - curlen] == c)
                break;
            cur = tree[cur].suffLink;
        }

        // If the transition already exists, just move the suffix pointer
        if (tree[cur].next.count(c)) {
            suff = tree[cur].next[c];
            return false; // No new palindrome created
        }

        // Create a new node for the new palindrome
        int newNode = tree.size();
        tree.push_back({tree[cur].len + 2, 0, {}});
        tree[cur].next[c] = newNode;

        // Set suffix link for the new node
        if (tree[newNode].len == 1) {
            tree[newNode].suffLink = 1; // Single-letter palindrome links to empty string node
        } else {
            int temp = tree[cur].suffLink;
            while (true) {
                int len = tree[temp].len;
                if (n - 2 - len >= 0 && s[n - 2 - len] == c) {
                    tree[newNode].suffLink = tree[temp].next[c];
                    break;
                }
                temp = tree[temp].suffLink;
            }
        }

        suff = newNode;
        return true; // New palindrome created
    }

    // Returns the number of odd-length palindromes of length >= 3
    int countOddPalindromesLenAtLeast3() {
        int count = 0;
        for (int i = 2; i < tree.size(); i++) {
            if (tree[i].len % 2 == 1 && tree[i].len >= 3)
                count++;
        }
        return count;
    }

    int countDistinctPalindromes() {
        return tree.size() - 2; // Exclude the two root nodes
    }
};
