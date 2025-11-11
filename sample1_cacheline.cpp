#include <vector>
#include <sstream>
#include <iostream>

#include "benchmark.hpp"

void moo(MyShortStruct i) {
  std::stringstream os;
  os << i.f0 << i.f1[0] << i.f2[1] << i.f3[1];
}

int main() {
  std::vector<MyShortStruct> a = generate_short_data(10000);

  auto fn = [a]() {
    for (auto i = 0; i < a.size(); ++i) {
      moo(a[i]);
    }
  };

  benchmark(fn, 10000);

  for (auto& i : a) {
    delete[] i.f1;
    delete[] i.f2;
    delete[] i.f3;
  }

  a.clear();
  
  return 0;
}
