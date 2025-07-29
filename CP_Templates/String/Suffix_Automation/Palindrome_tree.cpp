/*
 * ======================= Palindromic Tree (Eertree) =======================
 *
 * Description:
 * - Data structure to efficiently find and count all distinct palindromic substrings.
 * - Supports online construction in O(n) time.
 * 
 * Details:
 * - Each node represents a unique palindromic substring.
 * - `suffLink` connects to the largest proper palindromic suffix.
 * - Two imaginary roots: len = -1 (odd root), len = 0 (even root).
 * 
 * Usage:
 * - Call `addChar(c)` for each character in the string.
 * - After processing, use `countDistinctPalindromes()` or others for stats.
 *
 * ========================================================================
 */

struct Node {
    int len;                              // Length of the palindrome
    int suffLink;                         // Link to longest proper palindromic suffix
    unordered_map<char, int> next;        // Transitions by character
};

class PalindromicTree {
    vector<Node> tree;                    // Palindromic tree nodes
    string s;                             // Processed string
    int suff;                             // Current max suffix-palindrome node
    int n;                                // Length of current string

public:
    PalindromicTree() {
        // Root nodes:
        // node 0: len = -1 (imaginary odd root)
        // node 1: len = 0  (even root), both link to node 0
        tree.push_back({-1, 0, {}});
        tree.push_back({0, 0, {}});
        suff = 1;
        n = 0;
    }

    // Insert character c, return true if a new palindrome is created
    bool addChar(char c) {
        s += c;
        n++;
        int cur = suff;

        // Traverse suffix links to find the largest palindromic suffix that can be extended by c
        while (true) {
            int curlen = tree[cur].len;
            if (n - 2 - curlen >= 0 && s[n - 2 - curlen] == c)
                break;
            cur = tree[cur].suffLink;
        }

        // If such transition already exists → no new palindrome
        if (tree[cur].next.count(c)) {
            suff = tree[cur].next[c];
            return false;
        }

        // Create new node for the new palindrome
        int newNode = tree.size();
        tree.push_back({tree[cur].len + 2, 0, {}});
        tree[cur].next[c] = newNode;

        // Set suffix link for new node
        if (tree[newNode].len == 1) {
            tree[newNode].suffLink = 1;
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
        return true;
    }

    // Count number of odd-length palindromes of length ≥ 3
    int countOddPalindromesLenAtLeast3() {
        int count = 0;
        for (int i = 2; i < tree.size(); i++) {
            if (tree[i].len % 2 == 1 && tree[i].len >= 3)
                count++;
        }
        return count;
    }

    // Count total number of distinct palindromes
    int countDistinctPalindromes() {
        return tree.size() - 2; // Exclude the two roots
    }
};
