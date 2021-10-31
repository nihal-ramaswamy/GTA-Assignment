#include <vector>
#include <iostream>
#include <graph>
using namespace std;

class Tarjan: public graphs::graph {
private:
    vector<int> disc, low;
    vector<bool> visited, isAP;
    int time;

    void APUtil(int u, int parent) {
        int children = 0;
        visited[u] = true;
        disc[u] = low[u] = ++time;
        for (auto [v, w]: this->_graph[u]) {
            if (!visited[v]) {
                children++;
                APUtil(v, u);
                low[u] = min(low[u], low[v]);
                if (parent != -1 && low[v] >= disc[u]) {
                    isAP[u] = true;
                }
            }
            else if (v != parent) {
                low[u] = min(low[u], disc[v]);
            }
        }
        if (parent == -1 && children > 1) {
            isAP[u] = true;
        }
    }
public:
    Tarjan(int _n): graphs::graph(_n), time(0) {
        disc.assign(this->_n+1, 0);
        low.assign(this->_n+1, 0);
        visited.assign(this->_n+1, false);
        isAP.assign(this->_n+1, false);
    }

    void AP() {
        for (int u = 1; u <= this->_n; u++) {
            if (!visited[u]) {
                APUtil(u, -1);
            }
        }

        for (int u = 1; u <= this->_n; u++) {
            if (isAP[u] == true) {
                cout << u << " ";
            }
        }
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    Tarjan t(n);
    int u, v, w;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        t.add_edge(u, v, w);
    }
    cout << "Articulation Points: ";
    t.AP();
    return 0;
}
