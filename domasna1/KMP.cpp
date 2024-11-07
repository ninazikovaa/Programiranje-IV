#include <iostream>
#include <vector>
using namespace std;

class String {
    char *chars;
    unsigned int length;

public:
    String() : chars(nullptr), length(0) {}

    ~String() {
        delete[] chars;
    }

    // Copy constructor
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

    // setiranje na vrednostite
    void setString(const char* str) {
        length = 0;
        while (str[length] != '\0') length++;  // dolzinata da se njde
        
        chars = new char[length + 1];  
        for (unsigned int i = 0; i < length; i++) {
            chars[i] = str[i];
        }
        chars[length] = '\0';  
    }

    // Longest Prefix Suffix niza za KMP 
    int* LPS(const String& subStr) const {
        int n = subStr.length;
        int* lps = new int[n];
        int j = 0;
        lps[0] = 0;

        int i = 1;
        while (i < n) {
            if (subStr.chars[i] == subStr.chars[j]) {
                j++;
                lps[i] = j;
                i++;
            } else {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        return lps;
    }

    // site pojavuvanja
    int* findAllSubStr(const String& subStr) const {
        int* lps = LPS(subStr);
        int n = subStr.length;
        vector<int> result;

        int i = 0, j = 0;
        while (i < (int)length) {
            if (chars[i] == subStr.chars[j]) {
                i++;
                j++;
                if (j == n) {
                    result.push_back(i - j);
                    j = lps[j - 1];
                }
            } else {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }

        int* resultArr = new int[result.size() + 1];
        for (size_t i = 0; i < result.size(); ++i) {
            resultArr[i] = result[i];
        }
        resultArr[result.size()] = -1;  // kraj na nizata
        delete[] lps;
        return resultArr;
    }

    // prvo pojavuvanje
    int findFirstSubStr(const String& subStr) const {
        int* lps = LPS(subStr);
        int n = subStr.length;
        int i = 0, j = 0;

        while (i < (int)length) {
            if (chars[i] == subStr.chars[j]) {
                i++;
                j++;
                if (j == n) {
                    delete[] lps;
                    return i - j;  // ima match
                }
            } else {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }
        delete[] lps;
        return -1;  // nema match
    }

    // Reverse LPS za od pozadi
    int* reverseLPS(const String& subStr) const {
        int m = subStr.length;
        int* lps = new int[m];
        int len = 0;
        int i = m - 2;

        while (i >= 0) {
            if (subStr.chars[i] == subStr.chars[m - 1 - len]) {
                len++;
                lps[i] = len;
                i--;
            } else {
                if (len != 0) {
                    len = lps[m - len];
                } else {
                    lps[i] = 0;
                    i--;
                }
            }
        }

        return lps;
    }

    // poslednoto
    int findLastSubStr(const String& subStr) const {
        int* lps = reverseLPS(subStr);
        int m = subStr.length;
        int i = length - 1, j = m - 1;

        while (i >= 0) {
            if (chars[i] == subStr.chars[j]) {
                i--;
                j--;
                if (j < 0) {
                    delete[] lps;
                    return i + 1;
                }
            } else {
                if (j != m - 1) {
                    j = m - 1 - lps[j];
                } else {
                    i--;
                }
            }
        }
        delete[] lps;
        return -1;
    }

    // najdi gi iste vo reverse order (KMP)
    int* findAllSubStrReverse(const String& subStr) const {
        int* lps = reverseLPS(subStr);
        int m = subStr.length;
        vector<int> result;

        int i = length - 1, j = m - 1;
        while (i >= 0) {
            if (chars[i] == subStr.chars[j]) {
                i--;
                j--;
                if (j < 0) {
                    result.push_back(i + 1);
                    j = m - 1 - lps[j + 1];
                }
            } else {
                if (j != m - 1) {
                    j = m - 1 - lps[j];
                } else {
                    i--;
                }
            }
        }

        int* resultArr = new int[result.size() + 1];
        for (size_t i = 0; i < result.size(); ++i) {
            resultArr[i] = result[i];
        }
        resultArr[result.size()] = -1;  // krajot na nizata
        delete[] lps;
        return resultArr;
    }
};

int main() {
    String text;
    text.setString("ababxabababaxababa");

    String pattern;
    pattern.setString("ababa");

    // site pojavuvanja
    int* allOccurrences = text.findAllSubStr(pattern);
    cout << "Site pojavuvanja: ";
    for (int i = 0; allOccurrences[i] != -1; i++) {
        cout << allOccurrences[i] << " ";
    }
    cout << endl;
    delete[] allOccurrences;

    // prvoto pojavuvanje
    int firstOccurrence = text.findFirstSubStr(pattern);
    cout << "Prvoto pojavuvanje: " << firstOccurrence << endl;

    // posledno pojavuvanje
    int lastOccurrence = text.findLastSubStr(pattern);
    cout << "Posledno pojavuvanje: " << lastOccurrence << endl;

    // site pojavuvanja od pozadi
    int* reverseAllOccurrences = text.findAllSubStrReverse(pattern);
    cout << "Site pojavuvanja od pozadi: ";
    for (int i = 0; reverseAllOccurrences[i] != -1; i++) {
        cout << reverseAllOccurrences[i] << " ";
    }
    cout << endl;
    delete[] reverseAllOccurrences;

    return 0;
}

/*
KMP(Knuth-Morris Pratt) algorithm
Проверува дали некој substring е присутен во некој поголем стринг во време од О(N + M), 
каде што N e должината на поголемиот стринг, а М на substring, односно линеарно време

За KMP алгоритамот потребно е низа LPS
LPS → longest proper prefix that is also a suffix

Proper prefix → prefix во кој го нема целиот стринг 

За abc:
Префикси: a, b, ,c ab, bc
Суфикси: c, bc, abc

LPS[i] → должина на најдолгиот proper prefix од pattern[0..i] што исто така е и суфикс pattern[0..i]

LPS[0] = 0
се користи променлива j која кажува колку е големината на претходниот lps

Pattern[i] == pattern[j] → j++
Patterr[i] != pattern[j] AND j == 0 → lps[i] = 0
Pattern[i] != pattern[j] and j > 0 → можно е да постои помал префикс кој ќе биде ист 
како суфиксот и треба да го најдеме истиот. Pattern[i - j .. i - 1]

*/