#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

struct PatriciaTrieNode {
    int number; // Бројот на бит до кој се споредуваат зборовите
    string data; // Податок (збор) зачуван во јазолот
    PatriciaTrieNode *left_child, *right_child; // Лев и десен потомок
    
    PatriciaTrieNode() {
        left_child = NULL; // Иницијализира левото дете
        right_child = NULL; // Иницијализира десното дете
    }
};

struct PatriciaTrie {
    PatriciaTrieNode *root; // Коренот на Patricia Trie
    const int max_bits = 256; // Максимален број битови (ограничување)
    
    PatriciaTrie() {
        root = NULL; // Иницијализирање на празно дрво
    }
    
    void clear_trie() {
        root = NULL; // Ја ресетира структурата
    }
    
    bool is_empty() {
        if (root == NULL) {
            return true; // Ако коренот е празен, структурата е празна
        }
        return false;
    }
    
    // Проверува дали одреден бит во зборот е 1 или 0
    bool bit(string k, int i) {
        int char_index = (i - 1) / 8; // Пресметува индекс на карактерот
        int bit_index = 7 - ((i - 1) % 8); // Пресметува индекс на битот во карактерот
        
        if (char_index >= k.size()) {
            cout << "Max limits" << endl; // Грешка ако го надминува максимумот
            return false;
        }
        
        return (k[char_index] & (1 << bit_index)) != 0; // Враќа дали битот е 1
    }
    
    // Пребарува јазол кој содржи даден збор
    PatriciaTrieNode* search_node(PatriciaTrieNode* node, string k) {
        PatriciaTrieNode* current_node, * next_node;
        
        if (node == NULL) {
            return NULL; // Ако нема корен, враќа NULL
        }
        
        next_node = node->left_child; // Почнува со левото дете
        current_node = node;
        
        while (next_node->number > current_node->number) { // Додека не се најде точниот јазол
            current_node = next_node;
            
            if (bit(k, next_node->number)) {
                next_node = next_node->right_child; // Одете во десното дете ако битот е 1
            } else {
                next_node = next_node->left_child; // Одете во левото дете ако битот е 0
            }
        }
        return next_node; // Го враќа најдениот јазол
    }
 
    bool search(string k) {
        PatriciaTrieNode* tmp_node = search_node(root, k); // Пребарува збор
        return (tmp_node and tmp_node->data == k); // Враќа true ако зборот е најден
    }
    
    // Вметнува нов јазол во Patricia Trie
    PatriciaTrieNode* insert_node(PatriciaTrieNode* node, string value) {
        PatriciaTrieNode* current_node = NULL;
        PatriciaTrieNode* parent, * last_node, * new_node;
        
        if (node == NULL) { // Ако дрвото е празно, иницијализира нов корен
            node = new PatriciaTrieNode();
            node->number = 0;
            node->data = value;
            node->left_child = node; // Самиот јазол покажува на себе
            node->right_child = NULL;
            return node;
        }
        
        last_node = search_node(node, value); // Пребарува каде да се додаде зборот
        if (value == last_node->data) {
            cout << "This key already exists" << endl; // Ако веќе постои, не додава повторно
            return node;
        }
        
        int i;
        for (i = 1; bit(value, i) == bit(last_node->data, i); i++) {
            current_node = root->left_child; // Наоѓа каде почнуваат разликите
        }
        parent = node;
        
        while (current_node->number > parent->number and current_node->number < i) {
            parent = current_node;
            if (bit(value, current_node->number)) {
                current_node = current_node->right_child; // Движење кон десно дете
            } else {
                current_node = current_node->left_child; // Движење кон лево дете
            }
        }
        
        new_node = new PatriciaTrieNode();
        new_node->number = i; // Го поставува бројот на бит каде што се разликуваат
        new_node->data = value;
        
        if (bit(value, i)) { // Ако битот на зборот на позиција i е 1
            new_node->left_child = current_node;
            new_node->right_child = new_node;
        } else { // Ако битот на зборот на позиција i е 0
            new_node->left_child = new_node;
            new_node->right_child = current_node;
        }
        
        if (current_node == parent->left_child) { // Ако е левото дете на родителот
            parent->left_child = new_node;
        } else { // Ако е десното дете
            parent->right_child = new_node;
        }
        
        return node;
    }
    
    void insert(string value) {
        if (value.size() * 8 > max_bits) { // Проверува дали зборот ја надминува должината
            cout << "Max limit" << endl;
            return;
        }
        root = insert_node(root, value); // Го вметнува зборот
    }
};

int main() {
    PatriciaTrie* trie = new PatriciaTrie();
    trie->insert("hello");
    trie->insert("world");
    trie->insert("how");
    trie->insert("are");
    
    cout << trie->search("wo") << endl; // Пребарува збор
    
    return 0;
}
