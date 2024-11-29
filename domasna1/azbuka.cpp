#include <iostream>
#include <fstream>
#include <map>
#include <codecvt> // за UTF8 encoding
#include <locale> // за локацијата на датотеката
using namespace std;
const int ALPHABET_SIZE = 36;
map<wchar_t, int> alphabet; // мапирање од буква до индекс
map<int, wchar_t> rev_alpha; // обратна мапа, од индекс до буква


struct node {
    node * children_of_node[ALPHABET_SIZE]; // деца јазли за секоја буква
    bool is_end_of_word; // дали е крај на зборот

    // Конструктор за иницијализација на јазолот
    node() {
        is_end_of_word = false;
        for(int i = 0; i < ALPHABET_SIZE; i++) {
            children_of_node[i] = NULL;
        }
    }
};

// Функција за додавање збор во Trie
void add_word(node * trie, wstring word) {
    node * tmp = trie;
    for(int i = 0; i < (int) word.length(); i++) {
        int c = alphabet[word[i]]; // добивање индекс од мапата
        if(tmp -> children_of_node[c] == NULL) {
            tmp -> children_of_node[c] = new node(); // креирање нов јазол ако не постои
        }
        tmp = tmp -> children_of_node[c]; // премин кон следниот јазол
    }
    tmp -> is_end_of_word = true; // обележување дека е крај на зборот
}

// Функција за пребарување збор во Trie
bool search_word(node * trie, wstring word) {
    node * tmp = trie;
    for(int i = 0; i < (int) word.length(); i++) {
        int c = alphabet[word[i]]; // добивање индекс од мапата
        if(tmp -> children_of_node[c] == NULL) {
            return false; // ако не постои јазолот, зборот не е пронајден
        }
        tmp = tmp -> children_of_node[c];
    }
    return tmp -> is_end_of_word; // враќа дали зборот завршува тука
}

// Рекурзивна функција за длабочинско пребарување (DFS) во Trie
void dfs(node * trie, wstring word) {
    if(trie -> is_end_of_word) {
        wcout << word << endl; // печатење на збор ако е крај на зборот
    }

    for(int i = 0; i < ALPHABET_SIZE; i++) {
        if(trie -> children_of_node[i] != NULL) {
            dfs(trie -> children_of_node[i], word + rev_alpha[i]); // рекурзивно повикување за следните букви
        }
    }
}

int main() {
    wifstream file("all.txt"); // се чита датотеката, wifstream за кирилица
    file.imbue(locale(file.getloc(), new codecvt_utf8<wchar_t>));

    if(!file.is_open()) {
        cout << "Error opening file!" << endl;
        return 0;
    }

    locale::global(locale("mk_MK.UTF-8")); // глобална UTF8 енкодинг локација
    wcout.imbue(locale());
    wcin.imbue(locale());
    node * trie = new node(); // корен на Trie
    wstring word;
    int r = 0; // помошна променлива
    int cnt = 1; // бројач за индексите во мапите

    // Читање зборови од датотеката и додавање во Trie
    while(file >> word) {
        for(wchar_t c : word) {
            if(alphabet[c] == 0) { // ако не е веќе мапирано
                alphabet[c] = cnt; // мапирање буква -> индекс
                rev_alpha[cnt] = c; // мапирање индекс -> буква
                cnt++;
            }
        }
        add_word(trie, word); // додавање на зборот во Trie
    }

    wstring s;
    wcin >> s; // читање збор од влез

    // Проверка дали зборот постои во Trie
    node *tmp = trie;
    bool ok = true;
    for(int i = 0; i < (int) s.length(); i++) {
        int c = alphabet[s[i]]; // добивање индекс од мапата
        if(tmp -> children_of_node[c] != NULL) {
            tmp = tmp -> children_of_node[c]; // премин кон следниот јазол
        } else {
            ok = false; // ако нема јазол, зборот не постои
            break;
        }
    }
    if(!ok) {
        cout << "Ne postoi" << endl;
    }
    dfs(tmp, s); // печатење на сите зборови кои почнуваат со дадениот префикс

    return 0;
}
