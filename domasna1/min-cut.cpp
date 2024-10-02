#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 2e9;

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

    bool bfs(vector<int>& parent) {
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(S);
        visited[S] = true;
        parent[S] = -1;

        while (!q.empty()) {
            int c = q.front();
            q.pop();

            for (int i = 0; i < n; i++) {
                if (r_graph.get_cell(c, i) > 0 && !visited[i]) {
                    q.push(i);
                    parent[i] = c;
                    visited[i] = true;
                }
            }
        }
        return visited[T];
    }

    void dfs(vector<bool>& visited, int node) {
        visited[node] = true;
        for (int i = 0; i < n; i++) {
            if (r_graph.get_cell(node, i) > 0 && !visited[i]) {
                dfs(visited, i);
            }
        }
    }

    int min_cut() {
        vector<int> parent(n);

        while (bfs(parent)) {
            int path_flow = INF;
            for (int i = T; i != S; i = parent[i]) {
                int j = parent[i];
                path_flow = min(path_flow, r_graph.get_cell(j, i));
            }

            for (int i = T; i != S; i = parent[i]) {
                int j = parent[i];
                r_graph.set_cell(i, j, r_graph.get_cell(i, j) + path_flow);
                r_graph.set_cell(j, i, r_graph.get_cell(j, i) - path_flow);
            }
        }

        vector<bool> visited(n, false);
        dfs(visited, S);

        int res = 0;
        vector<pair<int, int>> cut_edges;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (visited[i] && !visited[j] && adj.get_cell(i, j)) {
                    res += adj.get_cell(i, j);
                    cut_edges.push_back({i, j});
                }
            }
        }

       
        cout << "Edges in the minimum cut:"<<endl;
        for (auto edge : cut_edges) {
            char from = 'A' + edge.first;
            char to = 'A' + edge.second;
            cout << from << " - " << to << '\n';
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
    for (int i = 0; i < n; i++) {
        char A, B;
        int c;
        cin >> A >> B >> c;
        int tmp_a = A - 'A';
        int tmp_b = B - 'A';
        g.add_edge(tmp_a, tmp_b, c);
        g.add_edge(tmp_b, tmp_a, c);
    }

    STCut st(30, S, T, g, g);
    int min_cut_value = st.min_cut();
    cout << "Minimum cut value: " << min_cut_value <<endl;

    return 0;
}
/*
5
A D
A B 5
A C 5
B D 4
C D 6
B C 2
*/
