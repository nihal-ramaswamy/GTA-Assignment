#ifndef __DSU_HPP__
#define __DSU_HPP__ 1
#include <vector>
#include <iostream>
#define debug(x) std::cout << "[" << __FILE__ << "] " << "[" << __LINE__ << "] " << #x << ":" << x << "\n";

namespace dsu {
class DSU {
 public:
  DSU(int n) : _n(n + 1) {
    parent.assign((size_t)this->_n, 0);
    rank.assign((size_t)this->_n, 0);
    for (int i = 0; i < (int)parent.size(); i++) {
      parent[(size_t)i] = i;
    }
  }

  int find(int i) {
    if (this->parent[(size_t)i] != i) this->parent[(size_t)i] = find(this->parent[(size_t)i]);
    return this->parent[(size_t)i];
  }

  void merge(int x, int y) {
    int xroot = this->find(x);
    int yroot = this->find(y);

    if (this->rank[(size_t)xroot] < this->rank[(size_t)yroot])
        this->parent[(size_t)xroot] = yroot;
    else if (this->rank[(size_t)xroot] > this->rank[(size_t)yroot])
        this->parent[(size_t)yroot] = xroot;
    else
    {
      this->parent[(size_t)yroot] = xroot;
      this->rank[(size_t)xroot]++;
    }
  }

 private:
  int _n;
  std::vector<int> parent, rank;
};
}  // namespace dsu
#endif
