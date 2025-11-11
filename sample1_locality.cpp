#include <vector>
#include <sstream>
#include <iostream>

#include "benchmark.hpp"

void moo(MyStruct i) {
  std::stringstream os;
  os << i.f0 << i.f1 << i.f2 << i.f3 << i.f4[0];
}

int main() {
  std::vector<MyStruct> a = generate_data(10000);
  
  auto fn = [a]() {
    for (auto i = 0; i < a.size(); ++i) {
      moo(a[i]);
    }
  };

  benchmark(fn, 10000);

  for (auto& item : a) {
    delete item.f3;
  }

  a.clear();

  return 0;
}
