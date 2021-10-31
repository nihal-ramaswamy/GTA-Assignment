#include <graph>
#include <edge>
#include <set>
#include <utility>
class ReverseDelete: public graphs::graph {
public:
    ReverseDelete(int _n): graphs::graph((size_t)_n) {}

    void dfs(int source, std::vector<bool>& visited) {
        visited[source] = true;
        for (auto [child, weight]: this->_graph[source]) {
            if (!visited[child]) {
                dfs(child, visited);
            }
        }
        return;
    }

    bool isConnected() {
        std::vector<bool> visited(this->_n + 1, false);
        dfs(1, visited);
        for (int i = 1; i <= this->_n; i++) {
            if (visited[i] == false) return false;
        }
        return true;
    }

    void reverseDeleteMST() {
        // std::set<std::pair<int, int>> seen;
        std::vector<edges::edge<int, int, int>> edge_list = this->get_edge_list();
        sort(edge_list.rbegin(), edge_list.rend());
        int MSTweight = 0;
        for (int i = 0; i < edge_list.size(); i++) {
            int u = edge_list[i].src, v = edge_list[i].dest;
            // if (seen.find({u, v}) != seen.end() || seen.find({v, u}) != seen.end()) continue;
            // seen.insert({u, v});
            this->remove_edge(u, v);
            if (isConnected() == false) {
                this->add_edge(u, v, edge_list[i].weight);
                MSTweight += edge_list[i].weight;
            }
        }
        std::cout << "MST Weight: " << MSTweight << "\n";
    }
};


int main() {
    int n, m;
    std::cin >> n >> m;
    ReverseDelete r(n);
    int u, v, w;
    for (int i = 0; i < m; i++) {
        std::cin >> u >> v >> w;
        r.add_edge(u, v, w);
    }

    std::cout << "Reverse Delete MST:\n";
    r.reverseDeleteMST();
    std::cout << r << "\n";
    std::cout << "--------------------------------------\n";

    return 0;
}
