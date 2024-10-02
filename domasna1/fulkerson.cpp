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
        adj_list[b].push_back(a); 
    }
    vector<int> get_neighbours(int x) {
        return adj_list[x];
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

    bool dfs(vector<int>& parent, vector<bool>& visited, int x, int t) {
        if (x == t) return true; 
        visited[x] = true;

        for (int i : this->adj.get_neighbours(x)) {
            if (capacity[x][i] > 0 && !visited[i]) {
                parent[i] = x;
                if (dfs(parent, visited, i, t))
                    return true; 
            }
        }
        return false;
    }

    int ford_fulkerson(int S, int E) {
        int max_flow = 0;
        vector<int> parent(n, -1);

        while (true) {
            vector<bool> visited(n, false);
            
            if (!dfs(parent, visited, S, E)) {
                
                break;
            }

            int path_flow = INF;
            for (int v = E; v != S; v = parent[v]) {
                int u = parent[v];
                path_flow = min(path_flow, capacity[u][v]);
            }

            for (int v = E; v != S; v = parent[v]) {
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
    int n = 4; 

    
    vector<vector<int>> capacity = {
        {0, 10, 10, 0},  
        {0, 0, 2, 4},    
        {0, 0, 0, 8},    
        {0, 0, 0, 0}    
    };

    Graph g(n);
    g.add_edge(0, 1);  
    g.add_edge(0, 2);  
    g.add_edge(1, 3);  
    g.add_edge(2, 3);  
    g.add_edge(1, 2);  

    FordFulkerson ff(n, capacity, g);
    cout << "The maximum flow is: " << ff.ford_fulkerson(0, 3) << endl;  

    return 0;
}
