#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__ 1

#include <iostream>
#include <vector>
#include "edge.hpp"
#include "misc.hpp"

namespace graphs {
class graph {
 public:
  size_t _n;
  std::vector<std::vector<edges::_edge>> _graph;

  graph(size_t _n) : _n(_n) {
    this->_graph.assign(this->_n + 1, std::vector<edges::_edge>());
  }

  void add_edge(int source, int destination, int weight) {
    assert(0 <= source < this->_n);
    assert(0 <= destination < this->_n);
    misc::insert_sorted<edges::_edge>(this->_graph[(size_t)source], {destination, weight});
    misc::insert_sorted<edges::_edge>(this->_graph[(size_t)destination], {source, weight});
  }

  void remove_edge(int source, int destination) {
    misc::remove_sorted<edges::_edge, int>(this->_graph[(size_t)source], destination);
    misc::remove_sorted<edges::_edge, int>(this->_graph[(size_t)destination], source);
  }

  std::vector<edges::edge<int, int, int>> get_edge_list() {
    std::vector<edges::edge<int, int, int>> edge_list;
    for (size_t source = 0; source <= this->_n; source++) {
      for (auto [destination, weight] : this->_graph[source]) {
        if (source < destination)
          edge_list.push_back({(int)source, destination, weight});
      }
    }
    return edge_list;
  }
  friend std::ostream& operator<<(std::ostream& out, const graph& graph);
};

std::ostream& operator<<(std::ostream& out, const graph& graph) {
  for (size_t source = 0; source <= graph._n; source++) {
    out << source << ": ";
    for (auto [destination, weight] : graph._graph[source]) {
      out << "{" << destination << " " << weight << "} ";
    }
    if (source != graph._n) {
      out << "\n";
    }
  }

  return out;
}
}  // namespace graphs

#endif
