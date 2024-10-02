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

class EdmondsKarpAlgorithm {
private:
    int n;
    Graph adj;
    vector<vector<int>> capacity;
    
public:
    EdmondsKarpAlgorithm(int n, vector<vector<int>> capacity, Graph adj) {
        this->n = n;
        this->capacity = capacity;
        this->adj = adj;
    }
    
    int bfs(int S, int E, vector<int>& parent) {
        fill(parent.begin(), parent.end(), -1);
        parent[S] = -2;
        
        queue<pair<int, int>> q;
        q.push({S, INF});
        
        while (!q.empty()) {
            int c = q.front().first;
            int flow = q.front().second;
            q.pop();
            
            for (int neigh : adj.get_neighbours(c)) {
                if (parent[neigh] == -1 && capacity[c][neigh] > 0) {
                    parent[neigh] = c;
                    int new_flow = min(flow, capacity[c][neigh]);
                    if (neigh == E) {
                        return new_flow;
                    }
                    q.push({neigh, new_flow});
                }
            }
        }
        return 0;
    }
    
    int max_flow(int S, int E) {
        int flow = 0;
        vector<int> parent(this->n);
        
        int new_flow;
        while ((new_flow = bfs(S, E, parent)) > 0) {
            flow += new_flow;
            int b = E;
            while (b != S) {
                int prev = parent[b];
                capacity[prev][b] -= new_flow;  
                capacity[b][prev] += new_flow;  
                b = prev;
            }
        }
        return flow;
    }
};

int main() {
    int V = 6;

    int graph[6][6] = { 
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}
    };

    Graph adj(6);
    vector<vector<int>> capacity(6, vector<int>(6, 0));

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            capacity[i][j] = graph[i][j];
            if (graph[i][j] != 0) {
                adj.add_edge(i, j);
            }
        }
    }

    EdmondsKarpAlgorithm edka(6, capacity, adj);
    cout << "Maximum flow: " << edka.max_flow(0, 5) << endl;  
    return 0;
}
