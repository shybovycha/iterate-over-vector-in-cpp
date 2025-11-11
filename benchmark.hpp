#pragma once

#include <numeric>
#include <vector>
#include <list>
#include <chrono>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cmath>
#include <random>

using duration_t = std::chrono::nanoseconds;

struct MyStruct {
  bool f0;
  float f1[100];
  double f2[53];
  char f3[64];
};

inline std::vector<MyStruct> generate_data(unsigned long n) {
  std::vector<MyStruct> a;

  std::random_device rd;
  std::mt19937_64 gen(rd());

  std::uniform_int_distribution<int> bool_dist(0, 1);
  std::uniform_real_distribution<float> float_dist(0.0f, 1000.0f);
  std::uniform_int_distribution<int> int_dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

  for (auto i = 0; i < 10000; ++i) {
      MyStruct e;

      e.f0 = static_cast<bool>(bool_dist(gen));

      for (auto t = 0; t < 100; ++t)
        e.f1[t] = float_dist(gen);

      for (auto t = 0; t < 53; ++t)
        e.f2[t] = static_cast<double>(float_dist(gen));

      for (auto t = 0; t < 64; ++t)
        e.f3[t] = static_cast<char>(int_dist(gen) % 255);

      a.push_back(e);
  }

  return a;
}

inline duration_t calculate_percentile(const std::vector<duration_t>& sorted_data, double p) {
    const size_t n = sorted_data.size();

    if (n == 0) {
        return duration_t::zero();
    }

    if (n == 1) {
        return sorted_data[0];
    }

    double rank = (static_cast<double>(n) - 1.0) * p;
    size_t k = static_cast<size_t>(std::floor(rank));
    double d = rank - k;

    if (k >= n - 1) {
        return sorted_data.back();
    }

    auto v_k = static_cast<double>(sorted_data[k].count());
    auto v_k1 = static_cast<double>(sorted_data[k + 1].count());

    double p_value_ns = v_k + d * (v_k1 - v_k);

    return duration_t(static_cast<long long>(std::round(p_value_ns)));
}

inline void benchmark(std::function<void(void)> fn, unsigned long n) {
    std::vector<duration_t> times;
    times.reserve(n);

    for (auto x = 0; x < n; ++x) {
        const auto t1 = std::chrono::high_resolution_clock::now();

        fn();
        
        const auto t2 = std::chrono::high_resolution_clock::now();

        const auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);

        times.push_back(duration);
    }

    std::sort(times.begin(), times.end());

    auto [min_t, max_t] = std::minmax_element(times.begin(), times.end());
    auto mean_t = std::accumulate(times.begin(), times.end(), duration_t::zero()) / times.size();
    auto p50 = calculate_percentile(times, 0.5);
    auto p90 = calculate_percentile(times, 0.9);
    auto p95 = calculate_percentile(times, 0.95);

    std::cout << "min (ns): " << min_t->count() << "\n";
    std::cout << "max (ns): " << max_t->count() << "\n";
    std::cout << "50%% (ns): " << p50.count() << "\n";
    std::cout << "90%% (ns): " << p90.count() << "\n";
    std::cout << "95%% (ns): " << p95.count() << "\n";
}

