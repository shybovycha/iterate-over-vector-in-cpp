#include <vector>
#include <sstream>
#include <iostream>

#include "benchmark.hpp"

void moo(int i) {
  std::stringstream os;
  os << i;
}

int main() {
  std::vector<int> a;

  for (auto i = 0; i < 10000; ++i) {
    a.push_back(i);
  }

  auto fn = [a]() {
    for (auto i = a.begin(); i != a.end(); i++) {
      moo(*i);
    }
  };

  benchmark(fn, 10000);
  
  return 0;
}

