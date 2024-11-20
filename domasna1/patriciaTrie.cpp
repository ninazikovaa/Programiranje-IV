#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
struct PatriciaTrieNode {
    int number;
    string data;
    PatriciaTrieNode *left_child, *right_child;
    
    PatriciaTrieNode() {
        left_child = NULL;
        right_child = NULL;
    }
};
struct PatriciaTrie {
    PatriciaTrieNode *root;
    const int max_bits = 256;
    
    
    PatriciaTrie() {
        root = NULL;
    }
    void clear_trie() {
        root = NULL;
    }
    bool is_empty() {
        if(root == NULL) {
            return true;
        }
        return false;
    }
    
    bool bit(string k, int i) {
        int char_index = (i - 1) / 8;
        int bit_index = 7 - ((i - 1) % 8);
        
        if(char_index >= k.size()) {
            cout << "Max limits" << endl;
            return false;
        }
 
        return (k[char_index] & (1 << bit_index)) != 0;
    }
    PatriciaTrieNode * search_node(PatriciaTrieNode * node, string k) {
        PatriciaTrieNode * current_node, * next_node;
        
        if(node == NULL) {
            return NULL;
        }
        
        next_node = node->left_child;
        current_node = node;
        
        while(next_node->number > current_node->number) {
            current_node = next_node;
            
            if(bit(k, next_node->number)) {
                next_node = next_node->right_child;
            }
            else {
                next_node = next_node->left_child;
            }
        }
        return next_node;
    }
 
    bool search(string k) {
        
        PatriciaTrieNode * tmp_node = search_node(root, k);
        if(tmp_node and tmp_node->data == k)
            return true;
        else
            return false;
    }
    
    PatriciaTrieNode * insert_node(PatriciaTrieNode * node, string value) {
        PatriciaTrieNode * current_node = NULL;
        PatriciaTrieNode * parent, * last_node, * new_node;
        
        if(node == NULL) {
            node = new PatriciaTrieNode();
            node->number = 0;
            node->data = value;
            node->left_child = node;
            node->right_child = NULL;
            
            return node;
        }
        last_node = search_node(node, value);
        if(value == last_node->data) {
            cout << "This key already exists" << endl;
            return node;
        }
        int i;
        for(i = 1; bit(value, i) == bit(last_node->data, i); i++) {
            current_node = root->left_child;
        }
        parent = node;
 
        while(current_node->number > parent->number and current_node->number < i) {
            parent = current_node;
            
            if(bit(value, current_node->number)) {
                current_node = current_node->right_child;
            }
            else {
                current_node = current_node->left_child;
            }
        }
        new_node = new PatriciaTrieNode();
        new_node->number = i;
        new_node->data = value;
        
        if(bit(value, i)) {
            new_node->left_child = current_node;
            new_node->right_child = new_node;
        }
        else {
            new_node->left_child = new_node;
            new_node->right_child = current_node;
        }
        
        if(current_node == parent->left_child) {
            parent->left_child = new_node;
        }
        else {
            parent->right_child = new_node;
        }
        
        return node;
        
        
    }
    void insert(string value) {
        if(value.size() * 8 > max_bits) {
            cout << "Max limit" << endl;
            return;
        }
        root = insert_node(root, value);
    }
};
 
int main() {
    
    PatriciaTrie *trie = new PatriciaTrie();
    trie->insert("hello");
    trie->insert("world");
    trie->insert("how");
    trie->insert("are");
    
    cout << trie-> search("wo") << endl;
    
    
    
    return 0;
}