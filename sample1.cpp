#include <vector>
#include <chrono>
#include <sstream>
#include <iostream>

void moo(int i) {
  std::stringstream os;
  os << i;
}

int main() {
  std::vector<int> a;

  for (auto i = 0; i < 10000; ++i) {
    a.push_back(i);
  }

  auto t1 = std::chrono::high_resolution_clock::now();
  
  for (auto i = 0; i < a.size(); ++i) {
    moo(a[i]);
  }

  auto t2 = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);

  std::cout << "sample1 (ns): " << duration.count() << "\n";
  
  return 0;
}
