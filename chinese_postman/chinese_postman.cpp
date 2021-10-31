#include <graph>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;


class ChinesePostman: public graphs::graph {
private:
    vector<int> oddVertices, d, path;
    vector<vector<pair<int, int>>> allCombinations, allPairs;
    const int INF = 1e9 + 7;

    bool isEulerian() {
        for (int i = 1; i <= this->_n; i++) {
            if (this->_graph[i].size() & 1) {
                oddVertices.push_back(i);
            }
        }
        return oddVertices.empty();
    }

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

    void gen_pairs() {
        for (int i = 0; i < oddVertices.size() - 1; i++) {
            allCombinations.push_back(vector<pair<int, int>>());
            for (int j = i + 1; j < oddVertices.size(); j++) {
                allCombinations[i].push_back({oddVertices[i], oddVertices[j]});
            }
        }
    }

    void backtrack(vector<pair<int, int>> p, set<int> seen, int idx) {
        if (idx == allCombinations.size()) {
            if (2 * p.size() == oddVertices.size())
                allPairs.push_back(p);
            return;
        }
        if (seen.find(allCombinations[idx][0].first) != seen.end()) {
            backtrack(p, seen, idx + 1);
            return;
        }
        seen.insert(allCombinations[idx][0].first);
        for (auto i: allCombinations[idx]) {
            if (seen.find(i.second) != seen.end()) {
                backtrack(p, seen, idx + 1);
            }
            else {
                p.push_back(i);
                seen.insert(i.second);
                backtrack(p, seen, idx + 1);
                p.pop_back();
                seen.erase(i.second);
            }
        }
        return;
    }

    void restore_path(int start, int end) {
        vector<int> p;
        for (int v = end; v != start; v = path[v]) {
            p.push_back(v);
        }
        p.push_back(start);
        for (int i = 0; i < p.size() - 1; i++) {
            this->add_edge(p[i], p[i+1], INF);
        }
        return;
    }

    int dijkstraUtil(int start, int end, int add = 0) {
        d.assign(this->_n + 1, INF);
        path.assign(this->_n + 1, -1);

        d[start] = 0;
        set<pair<int, int>> q;
        q.insert({0, start});
        while (!q.empty()) {
            int v = q.begin()->second;
            q.erase(q.begin());
            for (auto [to, len]: this->_graph[v]) {
                if (d[v] + len < d[to]) {
                    q.erase({d[to], to});
                    d[to] = d[v] + len;
                    path[to] = v;
                    q.insert({d[to], to});
                }
            }
        }
        if (add) {
            restore_path(start, end);
        }
        return d[end];
    }

    int dijkstra(vector<pair<int, int>> comb) {
        int sum = 0;
        for (auto [x, y]: comb) {
            sum += dijkstraUtil(x, y);
        }
        return sum;
    }


public:
    ChinesePostman(int _n): graphs::graph(_n) {}

    void solve() {
        if (this->isEulerian()) {
            this->getEulerTour();
            return;
        }
        sort(oddVertices.begin(), oddVertices.end());
        gen_pairs();
        backtrack(vector<pair<int, int>>(), set<int>(), 0);
        // for (auto i: allPairs) {
        //     for (auto j: i) {
        //         cout << "[" << j.first << " " << j.second << "] ";
        //     }
        //     cout << "\n";
        // }
        vector<pair<int, int>> oddCost;
        for (int i = 0; i < allPairs.size(); i++) {
            oddCost.push_back({dijkstra(allPairs[i]), i});
        }
        int idx = (*min_element(oddCost.begin(), oddCost.end())).second;
        // cout << idx << "\n";
        for (auto [x, y]: allPairs[idx]) {
            dijkstraUtil(x, y, 1);
        }
        this->getEulerTour();
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    ChinesePostman cp(n);
    int u, v, w;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        cp.add_edge(u, v, w);
    }
    cp.solve();

    return 0;
}

