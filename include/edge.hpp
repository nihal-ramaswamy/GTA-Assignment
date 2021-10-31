#ifndef __EDGE_HPP__
#define __EDGE_HPP__ 1

#include <iostream>

namespace edges {
using _edge = std::pair<int, int>;

template <class U, class V, class W>
struct edge {
  U src;
  V dest;
  W weight;
  edge(U src, V dest, W weight) : src(src), dest(dest), weight(weight) {}
  bool operator<(const edge& other) const { return weight < other.weight; }
  friend std::ostream& operator<<(std::ostream& out, const edge<U, V, W>& edge);
};
template <class U, class V, class W>
std::ostream& operator<<(std::ostream& out, const edge<U, V, W>& edge) {
  out << "{" << edge.src << ", " << edge.dest << ", " << edge.weight << "}";
  return out;
}

template <class U = int, class V = int, class W = int>
edges::edge<U, V, W> make_edge(U src, V dest, W weight) {
  return edge(src, dest, weight);
}
}  // namespace edges
#endif
