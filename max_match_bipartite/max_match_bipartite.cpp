#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

class MaxMatchBipartite {
private:
    int M, N;
    vector<vector<bool>> _graph;
    vector<int> matchR;
    vector<bool> seen;

    bool bpm(int u) {
        for (int v = 0; v < N; v++) {
            if (this->_graph[u][v] && !this->seen[v]) {
                this->seen[v] = true;
                if (this->matchR[v] < 0 || bpm(matchR[v])) {
                    this->matchR[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
public:
    MaxMatchBipartite(int N): M(N), N(N) {
        this->_graph.assign(M + 1, vector<bool>(N + 1, false));
        this->matchR.assign(N + 1, -1);
        this->seen.assign(N + 1, false);
    }
    void add_edge(int u, int v) {
        this->_graph[u][v] = this->_graph[v][u] = 1;
    }

    int maxBPM() {
        int result = 0;
        for (int u = 0; u < M; u++) {
            result += (bpm(u) == true ? 1 : 0);
        }
        return result;
    }
};

int main() {
    int N, M;
    cin >> N >> M;
    MaxMatchBipartite m(N);
    int u, v, w;
    for (int i = 0; i < M; i++) {
        cin >> u >> v >> w;
        m.add_edge(u, v);
    }
    cout << "Maximum matching = " << m.maxBPM() << endl;

    return 0;
}
