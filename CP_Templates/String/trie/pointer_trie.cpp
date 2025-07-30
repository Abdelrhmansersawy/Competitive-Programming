/*
 * Trie (Prefix Tree) with support for:
 *  - insert(string): adds a word to the trie
 *  - remove(string): unmarks a word and decrements prefix frequencies
 *
 * Applications:
 *  - Fast prefix queries
 *  - Dictionary matching
 *  - Autocomplete systems
 *
 * Time Complexity:
 *  - Insert/Remove: O(L) where L = length of string
 *  - Space: O(26 * total characters inserted)
 */

#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    TrieNode* nxt[26];   // Pointers to children
    int pre_cnt;         // Prefix count
    bool is_word;        // Is this end of a word

    TrieNode() {
        pre_cnt = 0;
        is_word = false;
        fill(nxt, nxt + 26, nullptr);
    }
};

struct Trie {
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        clear(root);
    }

    void clear(TrieNode* node) {
        if (!node) return;
        for (int i = 0; i < 26; ++i) clear(node->nxt[i]);
        delete node;
    }

    void insert(const string& s) {
        TrieNode* cur = root;
        for (char c : s) {
            int idx = c - 'a';
            if (!cur->nxt[idx]) cur->nxt[idx] = new TrieNode();
            cur = cur->nxt[idx];
            cur->pre_cnt++;
        }
        cur->is_word = true;
    }

    void remove(const string& s) {
        TrieNode* cur = root;
        for (char c : s) {
            int idx = c - 'a';
            if (!cur->nxt[idx]) return;
            cur = cur->nxt[idx];
            cur->pre_cnt--;
        }
        cur->is_word = false;
    }
};
