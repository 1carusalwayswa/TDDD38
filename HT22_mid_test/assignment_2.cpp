#include <type_traits>
#include <cassert>
#include <string>
#include <iostream>

// Originally from: 2019-06-03 Assignment #3

/* implement your classes here */
template <typename T1, typename T2>
struct common_type {
    using type = typename std::remove_reference
                    <decltype(true ? std::declval<T1>() : std::declval<T2>())>  
                    ::type;
};

template <typename T>
struct common_type<T, T> {
    using type = T;
};

template <typename T2>
struct common_type<void, T2> {
    using type = void;
};

template <typename T1>
struct common_type<T1, void> {
    using type = void;
};

template <>
struct common_type<void, void> {
    using type = void;
};

int main()
{
  // is_same_v is true if both types in the template-argument list are the same
  // and false otherwise.
    // 输出 common_type<int, int>::type
  assert((std::is_same_v<
          common_type<int, int>::type,
          int>));

  assert((std::is_same_v<
          common_type<int const, int>::type,
          int const>));
  
  assert((std::is_same_v<
          common_type<int, double>::type,
          double>));
  
  assert((std::is_same_v<
          common_type<double, int>::type,
          double>));
  
  assert((std::is_same_v<
          common_type<std::string, char const*>::type,
          std::string>));

  assert((std::is_same_v<
          common_type<void, int>::type,
          void>));

  assert((std::is_same_v<
          common_type<double, void>::type,
          void>));

  assert((std::is_same_v<
          common_type<void, void>::type,
          void>));
}