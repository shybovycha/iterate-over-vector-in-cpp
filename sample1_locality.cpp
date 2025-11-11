#include <vector>
#include <sstream>
#include <iostream>

#include "benchmark.hpp"

void moo(MyStruct i) {
  std::stringstream os;
  os << i.f0 << i.f1[0] << i.f2[1] << i.f3[2];
}

int main() {
  std::vector<MyStruct> a = generate_data(10000);
  
  auto fn = [a]() {
    for (auto i = 0; i < a.size(); ++i) {
      moo(a[i]);
    }
  };

  benchmark(fn, 10000);

  a.clear();

  return 0;
}
