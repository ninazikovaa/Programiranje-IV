#include <iostream>
#include <bits/stdc++.h>
using namespace std;
 
class Graph {
public:
    int n;
    
    vector<vector<int>> capacity, flow;
    vector<int> height, excess;
    vector<int> visited;
    queue<int> excess_nodes;
    
    Graph(int n) {
        this->n = n;
        capacity = vector<vector<int>>(n, vector<int>(n, 0));
    }
    
    void push(int A, int B) {
        int f = min(excess[A], capacity[A][B] - flow[A][B]);
        flow[A][B] += f;
        flow[B][A] -= f;
        excess[A] -= f;
        excess[B] += f;
        
        if(f > 0 and excess[B] == f) {
            excess_nodes.push(B);
        }
    }
    void relabel(int node) {
        int f = 2e9;
        for(int i = 0; i < n; i++) {
            if(capacity[node][i] - flow[node][i] > 0) {
                f = min(f, height[i]);
            }
        }
        if(f < 2e9) {
            height[node] = f + 1;
        }
    }
    void drain(int node) {
        while(excess[node] > 0) {
            if(visited[node] < n) {
                int v = visited[node];
                
                if(capacity[node][v]  - flow[node][v] > 0 and height[node] > height[v]) {
                    push(node, v);
                }
                else {
                    visited[node]++;
                }
            }
            else {
                relabel(node);
                visited[node] = 0;
            }
        }
    }
    int max_flow(int S, int T) {
        height = vector<int>(n, 0);
        height[S] = n;
        flow = vector<vector<int>>(n, vector<int>(n, 0));
        excess = vector<int>(n, 0);
        
        excess[S] = 2e9;
        for(int i = 0; i < n; i++) {
            if(i != S) {
                push(S, i);
            }
        }
        visited = vector<int>(n, 0);
        
        while(!excess_nodes.empty()) {
            int c = excess_nodes.front();
            excess_nodes.pop();
            
            if(c != S and c != T) {
                drain(c);
            }
        }
        int res = 0;
        for(int i =0 ; i < n; i++) {
            res += flow[i][T];
        }
        return res;
    
    }
    
};
 
 
int main() {
    Graph g(6);
    
    int graph[6][6]
            = { { 0, 16, 13, 0, 0, 0 }, { 0, 0, 10, 12, 0, 0 },
                { 0, 4, 0, 0, 14, 0 },  { 0, 0, 9, 0, 0, 20 },
                { 0, 0, 0, 7, 0, 4 },   { 0, 0, 0, 0, 0, 0 } };
     
    for(int i = 0; i < 6; i++ ){
        for(int j =0 ; j < 6; j++) {
            g.capacity[i][j] = graph[i][j];
        }
    }
    cout << g.max_flow(0, 5);
   
    
  
    return 0;
}

/*
Се користи за наоѓање на maximum flow во еден flow graph.
Од почетниот node, пушти вода до сите негови соседи
Дозволено е да има и вишок вода во едно теме
Ако има вишок вода, тогаш потребно е да се испразни таа вода до теме кое е со помала висина


Height на едно теме со одредува според тоа дали може да пуштиме вода од тоа теме до некој негов сосед.

Excess flow → збир на flow до темето - збир од изваден flow од темето, total inflow - total outflow 


Preflow, initialize height of each node
While push() or relabel() → do push() or relabel()
Return flow;

preflow():
Height, flow на секое теме ќе биде еднакво на 0
Height на source темето е еднакво со бројот на соседи на source
Секој edge ќе има flow од 0
Само соседите на source ќе имаат flow, excess flow еднаков на иницијалниот капацитет

*/
