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
    
    
};
 
class FordFulkerson {
private:
    int n;
    vector<vector<int>> capacity;
    Graph adj;
public:
    FordFulkerson(int n, vector<vector<int>> capacity, Graph adj) {
        this->n = n;
        this->capacity = capacity;
        this->adj = adj;
    }
    bool dfs(vector<int> & parent, vector<bool> & visited, int x, int t){
 
        if(x == t) return true;
        visited[x] = true;
 
        for(int i = 0; i < n; i++){
            if(capacity[x][i] > 0 && !visited[i]){
                parent[i] = x;
                if(dfs(parent, visited, i, t))
                    return true;
            }
        }
        return false;
 
    }
    int ford_fulkerson(int S, int E) {
        int max_flow = 0;
        vector<bool> visited(n, false);
        vector<int> parent(n, -1);
        
         while(dfs(parent, visited, S, E)){
             fill(visited.begin(), visited.end(), false);
             int path_flow = INF;
 
                for(int v = E; v != S; v = parent[v]){
                    int u = parent[v];
                    path_flow = min(path_flow, capacity[u][v]);
                }
 
                for(int v = E; v != S; v = parent[v]){
                    int u = parent[v];
                    capacity[u][v] -= path_flow;
                    capacity[v][u] += path_flow;
                }
 
                max_flow += path_flow;
            }
        
        return max_flow;
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
            adj.add_edge(i, j, graph[i][j]);
        }
    }
    FordFulkerson ff(6, capacity, adj);
    cout << ff.ford_fulkerson(0, 5) << endl;
    return 0;
}