#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class LONG_INT {
private:
    bool is_negative; 
    vector<int> data; 

public:
    LONG_INT() : is_negative(false) {} 

   
    LONG_INT(const string& str) {
        is_negative = (str[0] == '-'); 
        for (int i = str.length() - 1; i >= is_negative; --i) { 
            data.push_back(str[i] - '0'); // Сместување на цифрите во векторот
        }
        if (data.empty()) { // Ако нема цифри, постави го на 0
            data.push_back(0);
            is_negative = false;
        }
    }

    void print() const {
        if (is_negative && !(data.size() == 1 && data[0] == 0)) cout << '-'; // Ако не е 0, печати '-'
        for (int i = data.size() - 1; i >= 0; --i) {
            cout << data[i];
        }
        cout << endl;
    }

    // Собирање
    LONG_INT operator+(const LONG_INT& other) const {
        if (is_negative == other.is_negative) { // Ако двата броја имаат ист знак
            LONG_INT result;
            result.is_negative = is_negative; // Знакот е ист како оригиналните броеви
            int carry = 0;
            for (int i = 0; i < max(data.size(), other.data.size()) || carry; ++i) {
                int sum = carry;
                if (i < data.size()) sum += data[i];
                if (i < other.data.size()) sum += other.data[i];
                result.data.push_back(sum % 10);
                carry = sum / 10;
            }
            return result;
        } else { // Ако имаат различни знаци, користи одземање
            if (is_negative) return other - (-(*this));
            else return *this - (-other);
        }
    }

    // Оператор за негација (-)
    LONG_INT operator-() const {
        LONG_INT result = *this;
        if (!(data.size() == 1 && data[0] == 0)) { // Ако бројот не е 0, промени го знакот
            result.is_negative = !is_negative;
        }
        return result;
    }

    // Одземање
    LONG_INT operator-(const LONG_INT& other) const {
        if (is_negative != other.is_negative) { // Ако имаат различни знаци, користи собирање
            return *this + (-other);
        } else {
            if (abs_compare(*this, other) >= 0) { // Ако левиот број е поголем или еднаков
                LONG_INT result;
                result.is_negative = is_negative; // Резултатот го задржува знакот на поголемиот број
                int borrow = 0;
                for (int i = 0; i < data.size(); ++i) {
                    int left, right;

                    if (i < data.size()) { // Ако има цифра во левиот број
                        left = data[i];
                    } else {
                        left = 0;
                    }

                    if (i < other.data.size()) { // Ако има цифра во десниот број
                        right = other.data[i];
                    } else {
                        right = 0;
                    }

                    int diff = left - right - borrow;
                    if (diff < 0) { // Ако е негативен, позајмувај
                        diff += 10;
                        borrow = 1;
                    } else {
                        borrow = 0;
                    }
                    result.data.push_back(diff);
                }
                while (result.data.size() > 1 && result.data.back() == 0) { // Отстранување на водечки нули
                    result.data.pop_back();
                }
                return result;
            } else { // Ако десниот број е поголем, направи негација
                return -(other - *this);
            }
        }
    }

    // Множење
    LONG_INT operator*(const LONG_INT& other) const {
        LONG_INT result("0");
        result.is_negative = (is_negative != other.is_negative); // Ако броевите имаат различни знаци, резултатот е негативен
        result.data.resize(data.size() + other.data.size(), 0); // Поставување на доволен број цифри

        for (int i = 0; i < data.size(); ++i) {
            int carry = 0;
            for (int j = 0; j < other.data.size() || carry; ++j) {
                int sum;
                int multiplier;

                if (j < other.data.size()) {
                    multiplier = other.data[j];
                } else {
                    multiplier = 0;
                }

                sum = result.data[i + j] + data[i] * multiplier + carry;

                result.data[i + j] = sum % 10;
                carry = sum / 10;
            }
        }

        while (result.data.size() > 1 && result.data.back() == 0) { // Отстранување на водечки нули
            result.data.pop_back();
        }

        return result;
    }

    // Делење
    LONG_INT operator/(const LONG_INT& other) const {
        //if (other == LONG_INT("0")) throw runtime_error("Division by zero!"); // Проверка за делење со 0

        LONG_INT result, remainder;
        result.is_negative = (is_negative != other.is_negative); // Дефинирање на знакот на резултатот

        for (int i = data.size() - 1; i >= 0; --i) {
            remainder.data.insert(remainder.data.begin(), data[i]); // Додавање на цифрата во остатокот
            while (remainder.data.size() > 1 && remainder.data.back() == 0) { // Отстранување на нули
                remainder.data.pop_back();
            }
            int count = 0;
            while (abs_compare(remainder, other) >= 0) { // Намалување со одземање додека остатокот е поголем
                remainder = remainder - abs(other);
                count++;
            }
            result.data.insert(result.data.begin(), count); // Додавање на резултатната цифра
        }

        while (result.data.size() > 1 && result.data.back() == 0) { // Отстранување на водечки нули
            result.data.pop_back();
        }

        return result;
    }

    // Проверка за еднаквост
    bool operator==(const LONG_INT& other) const {
        return is_negative == other.is_negative && data == other.data;
    }

private:
    // Споредба на апсолутните вредности
    static int abs_compare(const LONG_INT& a, const LONG_INT& b) { 
        if (a.data.size() != b.data.size()) return a.data.size() - b.data.size();
        for (int i = a.data.size() - 1; i >= 0; --i) {
            if (a.data[i] != b.data[i]) return a.data[i] - b.data[i];
        }
        return 0;
    }

    // Враќа апсолутна вредност
    static LONG_INT abs(const LONG_INT& x) {
        LONG_INT result = x;
        result.is_negative = false;
        return result;
    }
};

int main() {
    LONG_INT num1("100");
    LONG_INT num2("2");

    cout << "Sobiranje: ";
    (num1 + num2).print();

    cout << "Odzimanje: ";
    (num1 - num2).print();

    cout << "Mnozenje: ";
    (num1 * num2).print();

    cout << "Delenje: ";
    (num1 / num2).print();

    LONG_INT num3("2");
    LONG_INT num4("100");

    cout << "Odzimanje za negativen: ";
    (num3 - num4).print();

    return 0;
}
