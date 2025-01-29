#include <iostream>

using namespace std;


int NZD_recursive(int a, int b) {
    if (b == 0) 
        return a;
    return NZD_recursive(b, a % b);
}

int NZD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int NZS(int a, int b) {
    return (a / NZD(a, b)) * b;  
}



int main() {
    int a = 24, b = 36;

    cout << "NZD rekurzivno: " << NZD_recursive(a, b) << endl;
    cout << "NZD: " << NZD(a, b) << endl;
    
    cout << "NZS: " << NZS(a, b) << endl;

    return 0;
}
