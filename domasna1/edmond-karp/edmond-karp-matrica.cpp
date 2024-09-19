#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int INF = 1e9;
class Graph {
private:
    vector<vector<int>> adj_matrix;
public:
    Graph() {}
    Graph(int n) {
        adj_matrix = vector<vector<int>>(n, vector<int>(n, 0));
    }
    void add_edge(int a, int b, int c) {
        adj_matrix[a][b] = c;
    }
    bool is_neighbour(int a, int b) {
        return (adj_matrix[a][b] != 0);
    }
    int get_cell(int a, int b) {
        return adj_matrix[a][b];
    }
    void set_cell(int a, int b, int c) {
        adj_matrix[a][b] = c;
    }
};
class EdmnodKarpAlgorithm {
private:
    int n;
    Graph capacity, adj;
    
public:
    EdmnodKarpAlgorithm(int n, Graph capacity, Graph adj) {
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
            
            for(int i = 0; i < n; i++) {
                if(adj.is_neighbour(c, i)) {
                    if(parent[i] == -1 and capacity.get_cell(c, i) > 0) {
                        parent[i] = c;
                        int new_flow = min(flow, capacity.get_cell(c, i));
                        if(i == E) {
                            return new_flow;
                        }
                        q.push(i);
                        q.push(new_flow);
                    }
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
                capacity.set_cell(prev, b, capacity.get_cell(prev, b) - tmp);
                capacity.set_cell(b, prev, capacity.get_cell(b, prev) + tmp);
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
    Graph capacity(6), adj(6);
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            capacity.set_cell(i, j, graph[i][j]);
            if(graph[i][j] != 0) {
                adj.set_cell(i, j, 1);
            }
        }
    }
    EdmnodKarpAlgorithm edka(6, capacity, adj);
    cout << edka.max_flow(0, 5) << endl;
    return 0;
}