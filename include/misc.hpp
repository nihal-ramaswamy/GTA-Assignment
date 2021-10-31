#ifndef __MISC_HPP__
#define __MISC_HPP__ 1

#include <vector>

namespace misc {

template< typename T >
void insert_sorted(std::vector<T> & vec, T const& item) {
    vec.insert
        (
            std::upper_bound( vec.begin(), vec.end(), item ),
            item
        );
    return;
}

template< typename T, typename U >
void remove_sorted(std::vector<T> & vec, U const& item) {
    auto cmp = [](const T& el, const U i) -> bool {
        return el.first < i;
    };
    const auto lower = std::lower_bound(vec.begin(), vec.end(), item, cmp);
    vec.erase(lower);
}



} // namespace misc

#endif
