# Iterating over vector in C++

Benchmark iterating over a vector (heap memory) using various techniques.

## sample1

Iterate over a vector using a simple `for` loop:

```cpp
for (auto i = 0; i < a.size(); ++i)
```

## sample2

Iterate over a vector using a backward `for` loop:

```cpp
for (auto i = a.size() - 1; i >= 0; --i)
```

## sample3

Iterate over a vector using a `foreach` loop:

```cpp
for (auto i : a)
```

## sample1_suffix

Use suffix / postfix increment operator:

```cpp
for (auto i = 0; i < a.size(); i++)
```

## sample2_suffix

Use suffix / postfix decrement operator:

```cpp
for (auto i = a.size() - 1; i >= 0; i--)
```
