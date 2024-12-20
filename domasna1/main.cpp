#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    int counter=0;
    cin>>n;
    bool niza[n+1];
    memset(niza,0,sizeof(n));
    for(int i=2;i<n;i++)
    {
        if(niza[i])
            continue;
        cout<<i<<" ";
        counter++;
        for(int j=i;j<=n;j+=i)
        {
            niza[j]=1;
        }
    }

    return 0;
}
