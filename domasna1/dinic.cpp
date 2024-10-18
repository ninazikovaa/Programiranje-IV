#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 2e9;

struct Edge {
    int v;
    int flow, capacity;
    int rev;

    Edge(int v, int flow, int capacity, int rev) {
        this->v = v;
        this->flow = flow;
        this->capacity = capacity;
        this->rev = rev;
    }
};

class Graph {
private:
    int n;
    vector<int> level;
    vector<vector<Edge>> adj;

public:
    Graph(int n) {
        this->n = n;
        level.resize(n);
        adj.resize(n + 1);
    }

    void add_edge(int a, int b, int cap) {
        Edge forward(b, 0, cap, (int) adj[b].size());
        Edge backwards(a, 0, 0, (int) adj[a].size());
        adj[a].push_back(forward);
        adj[b].push_back(backwards);
    }

    bool bfs(int S, int T) {
        for (int i = 0; i < n; i++) {
            level[i] = -1;
        }
        level[S] = 0;
        queue<int> q;
        q.push(S);

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (Edge e : adj[node]) {
                if (level[e.v] == -1 and e.flow < e.capacity) {
                    level[e.v] = level[node] + 1;
                    q.push(e.v);
                }
            }
        }
        return level[T] != -1;
    }

    int send_flow(int node, int flow, int T, vector<int>& v) {
        if (node == T) {
            return flow;
        }
        for (; v[node] < adj[node].size(); v[node]++) {
            Edge& e = adj[node][v[node]];
            if (level[e.v] == level[node] + 1 and e.flow < e.capacity) {
                int min_flow = min(flow, e.capacity - e.flow);
                int res_flow = send_flow(e.v, min_flow, T, v);

                if (res_flow > 0) {
                    e.flow += res_flow;
                    adj[e.v][e.rev].flow -= res_flow;
                    return res_flow;
                }
            }
        }
        return 0;
    }

    int dinics_algorithm(int S, int T) {
        if (S == T) {
            return -1;
        }
        int res = 0;

        while (bfs(S, T)) {
            vector<int> v(n + 1, 0);

            while (int fl = send_flow(S, INF, T, v)) {
                res += fl;
            }
        }
        return res;
    }
};

int main() {
    Graph g(6);
    g.add_edge(0, 1, 16);
    g.add_edge(0, 2, 13);
    g.add_edge(1, 2, 10);
    g.add_edge(1, 3, 12);
    g.add_edge(2, 1, 4);
    g.add_edge(2, 4, 14);
    g.add_edge(3, 2, 9);
    g.add_edge(3, 5, 20);
    g.add_edge(4, 3, 7);
    g.add_edge(4, 5, 4);

    cout << g.dinics_algorithm(0, 5) << endl;
    return 0;
}
