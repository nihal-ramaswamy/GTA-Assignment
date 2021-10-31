#include <iostream>
#include <vector>
#include <map>
#include <graph>
using namespace std;

class WelshPowell: public graphs::graph {
private:
    vector<int> colors;
    int mex(int source) {
        map<int, int> seen;
        for (auto [v, w]: this->_graph[source]) {
            if (colors[v] != -1) {
                seen[colors[v]] = 1;
            }
        }
        int MexOfNeighbours = -1;
        for (int i = 0; i <= this->_n + 1; i++) {
            if (seen[i] == 0) {
                MexOfNeighbours = i;
                break;
            }
        }
        return MexOfNeighbours;
    }
public:
    WelshPowell(int _n): graphs::graph(_n) {
        colors.assign(this->_n + 1, -1);
    }

    int welshPowellColoring() {
        vector<pair<int, int>> degree;
        for (int i = 1; i <= this->_n; i++) {
            degree.push_back({this->_graph[i].size(), i});
        }
        sort(degree.rbegin(), degree.rend());

        for (int i = 0; i < degree.size(); i++) {
            colors[degree[i].second] = mex(degree[i].second);
        }
        cout << "Coloring:\n";
        int maxColor = -1;
        for (int i = 1; i <= this->_n; i++) {
            cout << i << ": " << colors[i] << "\n";
            maxColor = max(maxColor, colors[i]);
        }
        return maxColor + 1;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    WelshPowell W(n);
    int u, v, w;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        W.add_edge(u, v, w);
    }


    int chromaticNumber = W.welshPowellColoring();
    cout << "Chromatic Number: " << chromaticNumber << "\n";

    return 0;
}
