#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int INF = 2e9;
class Graph {
private:
    vector<vector<int>> adj_matrix;
public:
    Graph() {
        
    }
    Graph(int n) {
        adj_matrix = vector<vector<int>>(n, vector<int>(n, 0));
    }
    void add_edge(int a, int b, int c) {
        adj_matrix[a][b] = c;
    }
    int get_cell(int i, int j) {
        return adj_matrix[i][j];
    }
    void set_cell(int i, int j, int x) {
        adj_matrix[i][j] = x;
    }
};
class STCut {
private:
    int n;
    int S, T;
    Graph adj, r_graph;
public:
    STCut(int n, int S, int T, Graph adj, Graph r_graph) {
        this->n = n;
        this->S = S;
        this->T = T;
        this->adj = adj;
        this->r_graph = r_graph;
    }
    int bfs(vector<int> & parent) {
        vector<bool> visited(n, false);
        
        queue<int> q;
        q.push(S);
        visited[S] = true;
        parent[S] = -1;
        
        while(!q.empty()) {
            int c = q.front();
            q.pop();
            
            for(int i = 0; i < 30; i++) {
                if(r_graph.get_cell(c, i) > 0 and !visited[i]) {
                    q.push(i);
                    parent[i] = c;
                    visited[i] = true;
                }
            }
        }
        if(visited[T]) {
            return true;
        }
        return false;
        
    }
    void dfs(vector<bool> & visited, int node) {
        visited[node] = true;
        for(int i = 0; i < 30; i++) {
            if(r_graph.get_cell(node, i) > 0 and !visited[i]) {
                dfs(visited, i);
            }
        }
    }
    int min_cut() {
        vector<int> parent(30);
        
        while(bfs(parent)) {
            int path_flow = INF;
            for(int i = T; i != S; i = parent[i]) {
                int j = parent[i];
                path_flow = min(path_flow, r_graph.get_cell(j, i));
            }
            for(int i = T; i != S; i = parent[i]) {
                int j = parent[i];
                r_graph.set_cell(i, j, r_graph.get_cell(i, j) + path_flow);
                r_graph.set_cell(j, i, r_graph.get_cell(j, i) - path_flow);
            }
            
        }
        vector<bool> visited(30, false);
        dfs(visited, S);
        int res = 0;
        for(int i = 0; i < 30; i++) {
            for(int j = 0; j < 30; j++) {
                if(visited[i] and !visited[j] and adj.get_cell(i, j)) {
                    res += adj.get_cell(i, j);
                }
            }
        }
        return res;
    }
};
int main() {
    int n;
    cin >> n;
    char a, b;
    cin >> a >> b;
    int S = a - 'A';
    int T = b - 'A';
    
    Graph g(30);
    for(int i = 0; i < n; i++) {
        char A, B;
        int c;
        cin >> A >> B >> c;
        int tmp_a = A - 'A';
        int tmp_b = B - 'A';
        g.add_edge(tmp_a, tmp_b, c);
        g.add_edge(tmp_b, tmp_a, c);
        
        
    }
    STCut st(n, S, T, g, g);
    cout << st.min_cut();
}