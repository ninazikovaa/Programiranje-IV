#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

class String {
    char *chars;
    unsigned int length;

public:
    String() : chars(nullptr), length(0) {}

    ~String() {
        delete[] chars;
    }


    String(const String& other) : length(other.length) {
        chars = new char[length + 1];
        for (unsigned int i = 0; i < length; i++) {
            chars[i] = other.chars[i];
        }
        chars[length] = '\0';
    }

    String& operator=(const String& other) {
        if (this != &other) {
            delete[] chars;
            length = other.length;
            chars = new char[length + 1];
            for (unsigned int i = 0; i < length; i++) {
                chars[i] = other.chars[i];
            }
            chars[length] = '\0';
        }
        return *this;
    }


    void setString(const char* str) {
        length = 0;
        while (str[length] != '\0') length++;
        
        chars = new char[length + 1];
        for (unsigned int i = 0; i < length; i++) {
            chars[i] = str[i];
        }
        chars[length] = '\0';
    }

    char getChar(unsigned int i) const {
        if (i < length) {
            return chars[i];
        }
        return '\0';
    }

    unsigned int getLength() const {
        return length;
    }
};

// funkcija za base^exp % MOD 
ll mod_pow(ll base, ll exp, ll MOD) {
    ll result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exp /= 2;
    }
    return result;
}

// Rabin-Karp funkcija so sobianje
void rabin_carp(const String &text, const String &pattern, ll base, ll MOD) {
    unsigned int text_length = text.getLength();
    unsigned int pattern_length = pattern.getLength();
    
    if (pattern_length > text_length) return;

    ll pattern_hash = 0, text_hash = 0;
    for (unsigned int i = 0; i < pattern_length; i++) {
        pattern_hash = (pattern_hash * base + (ll) pattern.getChar(i)) % MOD;
        text_hash = (text_hash * base + (ll) text.getChar(i)) % MOD;
    }

    ll power = mod_pow(base, pattern_length - 1, MOD);

    for (unsigned int i = 0; i <= text_length - pattern_length; i++) {
        if (pattern_hash == text_hash) {
            bool match = true;
            for (unsigned int j = 0; j < pattern_length; j++) {
                if (text.getChar(i + j) != pattern.getChar(j)) {
                    match = false;
                    break;
                }
            }
            if (match) {
                cout << "Matching at: " << i << endl;
            }
        }
        
        if (i < text_length - pattern_length) {
            text_hash = (text_hash - (ll) text.getChar(i) * power % MOD + MOD) % MOD;
            text_hash = (text_hash * base + (ll) text.getChar(i + pattern_length)) % MOD;
        }
    }
}

// Rabin-Karp so stepenuvanje
void rabin_karp_normal(const String &text, const String &pattern, ll base, ll MOD) {
    unsigned int text_length = text.getLength();
    unsigned int pattern_length = pattern.getLength();
    
    if (pattern_length > text_length) return;

    ll pattern_hash = 0;
    ll text_hash = 0;

    
    for (unsigned int i = 0; i < pattern_length; i++) {
        pattern_hash = (pattern_hash * base + pattern.getChar(i)) % MOD;
        text_hash = (text_hash * base + text.getChar(i)) % MOD;
    }

    ll power = mod_pow(base, pattern_length - 1, MOD);


    for (unsigned int i = 0; i <= text_length - pattern_length; i++) {

        if (pattern_hash == text_hash) {
            bool match = true;
            for (unsigned int j = 0; j < pattern_length; j++) {
                if (text.getChar(i + j) != pattern.getChar(j)) {
                    match = false;
                    break;
                }
            }
            if (match) {
                cout << "Match: " << i << endl;
            }
        }

        if (i < text_length - pattern_length) {
            text_hash = (text_hash - text.getChar(i) * power % MOD + MOD) % MOD;
            text_hash = (text_hash * base + text.getChar(i + pattern_length)) % MOD;
        }
    }
}

int main() {
    String text;
    text.setString("ABBCAABCBB");

    String pattern;
    pattern.setString("BC");

    ll MOD = 1e9 + 7;
    ll base = 26;

    cout << "Sobiranje Rabin-Karp:" << endl;
    rabin_carp(text, pattern, base, MOD);

    cout<<endl;
    
    cout << "Stepenuvanje Rabin-Karp:" << endl;
    rabin_karp_normal(text, pattern, base, MOD);

    return 0;
}
