#include <algorithm>
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <type_traits>
#include <vector>

template <typename T>
class MyVector {
 public:
  using value_type = T;
  template <size_t N>
  MyVector(const T (&arr)[N]) : sz_(N) {
  }
  template <typename It>
  MyVector(It from, It to) : sz_(std::distance(from, to)) {
  }
  const size_t size() const {
    return sz_;
  }
 private:
  const size_t sz_;
};

template <typename It>
MyVector(It, It) -> MyVector<typename std::iterator_traits<It>::value_type>;

// template <typename T, size_t N>
// using ArrayAlias = MyArray<T, N>;

int main(int, char**) {

  /*
  int arr[4] = {1, 2, 3, 4};
  MyArray myarr{arr};
  static_assert(std::is_same_v<decltype(myarr)::value_type, int>);
  static_assert(decltype(myarr)::size() == 4);
  */

  // ArrayAlias arral{arr}; // Doesn't compile

  MyVector v1{{1, 2, 3}};
  static_assert(std::is_same_v<decltype(v1)::value_type, int>);
  assert(v1.size() == 3);

  std::vector<double> dv = {1.0, 3.0, 5.0, 7.0};
  MyVector v2{dv.begin(), dv.end()};
  static_assert(std::is_same_v<decltype(v2)::value_type, double>);
  assert(v2.size() == 4);

  return 0;

}

