#include <cassert>
#include <iostream>

// implement the Fibonacci class here
template<int N>
struct Fibonacci {
    static const uint64_t value {Fibonacci<N-1>::value + Fibonacci<N - 2>::value};
};

template<>
struct Fibonacci <1> {
    static const uint64_t value = 1;
};


template<>
struct Fibonacci <0> {
    static const uint64_t value = 0;
};

int main()
{
  assert(Fibonacci<0>::value == 0);
  assert(Fibonacci<1>::value == 1);
  assert(Fibonacci<5>::value == 5);
  assert(Fibonacci<10>::value == 55);
  assert(Fibonacci<12>::value == 144);

  std::cout << Fibonacci<92>::value << '\n';
  std::cout << Fibonacci<93>::value << '\n';
}

/*
    Implement calculate the Fibonacci number at compile time using template specialization.
    In this way, it's faster then the template function.
    In template function, the compiler will make a lot of function during the compile time.
    But in template specialization, type definitions are not repeated, so it's faster.
*/