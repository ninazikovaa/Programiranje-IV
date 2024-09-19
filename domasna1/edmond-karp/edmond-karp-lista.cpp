#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int INF = 1e9;
class Graph {
private:
    vector<vector<int>> adj_list;
public:
    Graph() {}
    Graph(int n) {
        adj_list.resize(n);
    }
    void add_edge(int a, int b) {
        adj_list[a].push_back(b);
    }
    vector<int> get_neighbours(int x) {
        return adj_list[x];
    }
    
};
class EdmnodKarpAlgorithm {
private:
    int n;
    Graph adj;
    vector<vector<int>> capacity;
    
public:
    EdmnodKarpAlgorithm(int n, vector<vector<int>> capacity, Graph adj) {
        this->n = n;
        this->capacity = capacity;
        this->adj = adj;
    }
    
    int bfs(int S, int E, vector<int> & parent) {
        fill(parent.begin(), parent.end(), -1);
        parent[S] = -2;
        
        queue<int> q;
        q.push(S);
        q.push(INF);
        
        while(!q.empty()) {
            int c = q.front();
            q.pop();
            int flow = q.front();
            q.pop();
            
            for(int neigh : adj.get_neighbours(c)) {
                if(parent[neigh] == -1 and capacity[c][neigh]) {
                    parent[neigh] = c;
                    int new_flow = min(flow, capacity[c][neigh]);
                    if(neigh == E) {
                        return new_flow;
                    }
                    q.push(neigh);
                    q.push(new_flow);
                }
                
            }
            
        }
        return 0;
    }
    
    int max_flow(int S, int E) {
        int flow = 0;
        vector<int> parent(this->n);
        
        int tmp;
        while(tmp = bfs(S, E, parent)) {
            flow += tmp;
            int b = E;
            while(b != S) {
                int prev = parent[b];
                capacity[prev][b] -= tmp;
                capacity[b][prev] += tmp;
                b = prev;
            }
        }
        return flow;
    }
    
};
 
int main() {
    int V = 6;
    int graph[6][6] = { {0, 16, 13, 0, 0, 0},
                           {0, 0, 10, 12, 0, 0},
                           {0, 4, 0, 0, 14, 0},
                           {0, 0, 9, 0, 0, 20},
                           {0, 0, 0, 7, 0, 4},
                           {0, 0, 0, 0, 0, 0}
                         };
    Graph adj(6);
    vector<vector<int>> capacity(6, vector<int>(6, 0));
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            capacity[i][j] = graph[i][j];
            if(graph[i][j] != 0) {
                adj.add_edge(i, j);
            }
        }
    }
    EdmnodKarpAlgorithm edka(6, capacity, adj);
    cout << edka.max_flow(0, 5) << endl;
    return 0;
}