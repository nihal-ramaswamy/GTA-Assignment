#include <dsu>
#include <edge>
#include <graph>
#include <iostream>
#include <set>
#include <vector>
using Edges = edges::edge<int, int, int>;

class Boruvka: public graphs::graph {
public:
  Boruvka(int _n): graphs::graph((size_t)_n) {}

  void boruvkaMST() {
    int numVertices = this->_n;
    std::vector<Edges> edge_list = this->get_edge_list();
    graphs::graph MST((size_t)numVertices);
    dsu::DSU Dsu(numVertices);

    std::vector<int> cheapest((size_t)numVertices + 1, -1);

    int numTrees = numVertices, MSTweight = 0;

    while (numTrees > 1) {
      cheapest.assign(cheapest.size(), -1);
      for (int i = 0; i < (int)edge_list.size(); i++) {
        int set1 = Dsu.find(edge_list[(size_t)i].src);
        int set2 = Dsu.find(edge_list[(size_t)i].dest);
        if (set1 == set2) continue;
        if (cheapest[(size_t)set1] == -1 || edge_list[(size_t)cheapest[(size_t)set1]].weight > edge_list[(size_t)i].weight)
          cheapest[(size_t)set1] = i;

        if (cheapest[(size_t)set2] == -1 || edge_list[(size_t)cheapest[(size_t)set2]].weight > edge_list[(size_t)i].weight)
          cheapest[(size_t)set2] = i;
      }
      for (int i = 0; i < numVertices; i++) {
        if (cheapest[(size_t)i] != -1) {
          int set1 = Dsu.find(edge_list[(size_t)cheapest[(size_t)i]].src);
          int set2 = Dsu.find(edge_list[(size_t)cheapest[(size_t)i]].dest);
          if (set1 == set2) continue;
          MSTweight += edge_list[(size_t)cheapest[(size_t)i]].weight;
          MST.add_edge(edge_list[(size_t)cheapest[(size_t)i]].src, edge_list[(size_t)cheapest[(size_t)i]].dest, edge_list[(size_t)cheapest[(size_t)i]].weight);
          Dsu.merge(set1, set2);
          numTrees--;
        }
      }
    }
    std::cout << "MST By boruvkaMST:\n" << MST << "\n";
    std::cout << "Weight = " << MSTweight << "\n";
  }
};

int main() {
  int n, m;
  std::cin >> n >> m;

  Boruvka b(n);

  int u, v, w;

  for (int i = 0; i < m; i++) {
    std::cin >> u >> v >> w;
    b.add_edge(u, v, w);
  }

  b.boruvkaMST();
  return 0;
}
