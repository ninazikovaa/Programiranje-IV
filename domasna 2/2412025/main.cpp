#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class LONG_INT
{
private:
    vector<int> data;

public:
    LONG_INT() {}

    LONG_INT(const string& str)
    {
        for(int i=str.length()-1;i>=0;--i)
        {
            data.push_back(str[i] - '0');
        }
    }

    void print() const
    {
        for(int i=data.size()-1;i>=0;--i)
        {
            cout<<data[i];
        }
        cout<<endl;
    }
    LONG_INT operator+(const LONG_INT& other)
    {
        LONG_INT rez;
        const vector<int>& a=data;
        const vector<int>& b=other.data;

        int c=0;
        int i=0;
        while(i<a.size() || i<b.size() || c)
        {
            int sum=c;
            if(i<a.size())
                sum+=a[i];
            if(i<b.size())
                sum+=b[i];
            rez.data.push_back(sum%10);
            c=sum/10;
            i++;
        }
        return rez;
    }

     LONG_INT operator-(const LONG_INT& other) const {

        LONG_INT rez;
        const vector<int>& a = data;
        const vector<int>& b = other.data;

        int borrow = 0;
        for (int i = 0; i < a.size(); ++i) {
            int b_digit = 0; //na b digit
            if (i < b.size()) {
                b_digit = b[i]; //ako a ima cifra tamu zemi go
            }
            int diff = a[i] - borrow - b_digit;

            if (diff < 0) { //ako e negativen, borrow od predhodniot broj
                diff += 10;
                borrow = 1; //zemeno e 1
            } else {
                borrow = 0;
            }

            rez.data.push_back(diff);
        }
        while (rez.data.size() > 1 && rez.data.back() == 0) {
            rez.data.pop_back(); //brisi ja poslednata ako 0
        }

        return rez;
     }
};

int main()
{
    LONG_INT num1("103");
    LONG_INT num2("102");
    (num1 + num2).print();
    (num2-num1).print();
    return 0;
}
