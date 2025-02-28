#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct Point
{
    double e[3];

    Point(double x=0.0, double y=0.0, double w=0.0)
    {
        e[0]=x;
        e[1]=y;
        e[2]=w;
    }
};

struct Matrix
{
    double m[3][3]={0};
    Matrix()
    {
        for(int i=0;i<3;i++)
        {
            m[i][i]=1;
        }
    }
    Matrix(int v)
    {
        for(int i=0;i<3;i++)
        {
            m[i][i]=v;
        }
    }
    double& at(int x, int y)
    {
        return m[x][y];
    }
    Matrix operator*(const Matrix &second)
    {
        Matrix result(0);
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                for(int k=0;k<3;k++)
                {
                    result.m[i][j]+=m[i][k]*second.m[k][j];
                }
            }
        }
        return result;
    }
    Point operator*(const Point& second)
    {
        Point result;
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                result.e[i]+=m[i][j]*second.e[j];

            }
        }
        return result;

    }
};

ostream & operator<<(ostream &os, const Matrix &matrix)
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            os<<matrix.m[i][j]<<" ";
        }
        cout<<endl;
    }
}
ostream & operator<<(ostream &os, const Point &p)
{
    os<<"[ ";
    for(int i=0;i<3;i++)
    {
        os<<p.e[i]<<" ";
    }
    os<<"]"<<endl;
    return os;
}

int main()
{

   Matrix first;
   Matrix second;

   //first.m[0][0]=2;
   //first.m[1][1]=5;
   first.m[0][2]=3;
   second.m[0][0]=0.5;

   Matrix rot;
   rot.m[0][0]=cos(M_PI/2);
   rot.m[1][1]=cos(M_PI/2);
   rot.m[0][1]=(-1)*sin(M_PI/2);
   rot.m[1][0]=sin(M_PI/2);

   //second.m[0][0]=3;
   Point p1(3,1,1);

   Matrix result=first*second;
   Point p2=rot*p1;

   //cout<<p1<<endl;
   cout<<p2<<endl;
   cout<<result;

   return 0;
}
