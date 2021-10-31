#include <graph>
#include <iostream>

class Euler: public graphs::graph {
public:
    Euler(int _n): graphs::graph((size_t)_n) {}

    int dfs(int v, std::vector<bool>& visited) {
        visited[v] = true;
        int count = 1;
        for (auto i: this->_graph[v]) {
            if (!visited[i.first])
                count += dfs(i.first, visited);
        }
        return count;
    }

    bool isValidNextEdge(int source, int child) {
        if (this->_graph[source].size() == 1) return true;
        std::vector<bool> visited(this->_n + 1, false);

        int count1 = this->dfs(source, visited);
        this->remove_edge(source, child);
        visited.assign(visited.size(), false);
        int count2 = this->dfs(source, visited);
        this->add_edge(source, child, -1); // weight does not matter
        return (count1 > count2 ? false: true);
    }

    void getEulerTourUtil(int source) {
        for (auto [child, weight]: this->_graph[source]) {
            if (isValidNextEdge(source, child)) {
                this->remove_edge(source, child);
                std::cout << source << "-" << child << "\n";
                getEulerTourUtil(child);
                break;
            }
        }
    }

    void getEulerTour() {
        int u = 1;
        for (int i = 1; i <= this->_n; i++) {
            if (this->_graph[i].size() & 1) {
                u = i;
                break;
            }
        }
        getEulerTourUtil(u);
    }
};


int main() {

    int n, m;
    std::cin >> n >> m;
    Euler e(n);
    int u, v, w;
    for (int i = 0; i < m; i++) {
        std::cin >> u >> v >> w;
        e.add_edge(u, v, w);
    }
    std::cout << "Euler path:\n";
    e.getEulerTour();
    return 0;
}
