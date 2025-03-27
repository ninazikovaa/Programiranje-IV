#include <bits/stdc++.h>
using namespace std;

struct Point
{
    int x, y;
    Point(int x1, int y1) 
    {
        x = x1;
        y = y1;
    }
    bool operator<(const Point& other) const 
    {
        if (x!=other.x) 
            return x<other.x;
        return y<other.y;
    }
};

bool dali_desno(Point p, Point q, Point r) 
{
    int det=(q.x - p.x)*(r.y-p.y)-(q.y-p.y)*(r.x-p.x);
    return det<=0; 
}

int main()
{
    int n;
    cin>>n;
    vector<Point> points;
    set<pair<Point, Point>> edges; 
    
    for (int i=0; i<n;i++) 
    {
        int x, y;
        cin>>x>>y;
        points.push_back(Point(x, y));
    }
    
    for (int i=0; i<n; i++) 
    {
        for (int j=0; j<n; j++) 
        {
            if (i==j) 
                continue;
            
            Point p=points[i];
            Point q=points[j];
            bool valid=true;
            
            for (int k=0; k<n; k++) 
            {
                if (k==i||k==j) 
                    continue;
                
                Point r=points[k];
                if (!dali_desno(p, q, r)) 
                {
                    valid=false;
                    break;
                }
            }
            
            if (valid) 
            {
                edges.insert({p, q}); 
            }
        }
    }
    
    for (const auto& edge : edges) 
    {
        Point a=edge.first;
        Point b=edge.second;
        cout<<"("<<a.x<<", "<<a.y<<") -> ("<<b.x<<", "<<b.y<<")<<endl;
    }
    
    return 0;
}
