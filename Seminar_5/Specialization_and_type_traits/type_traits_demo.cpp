#include <iostream>

// Implement is_const, is_pointer, is_array and is_const_pointer here

struct false_type
{
    static const bool value {false};
};

struct true_type
{
    static const bool value {true};
};

template <typename T1>
struct is_const : false_type {};

// we use const to indicate that the T1 is constant
// if T1 is a pointer, the const shoule be used to modify the pointer.
template <typename T1>
struct is_const<T1 const> : true_type {};

template <typename T1>
struct is_pointer : false_type {};

template <typename T1>
struct is_pointer<T1 *> : true_type {};

// cause (T1* const) is not a pointer type
// const is not used to modify pointer, it is used to modify the data pointed by the pointer.
template <typename T1>
struct is_pointer<T1* const> : true_type {};

template <typename T1>
struct is_array : false_type {};

template <typename T1, unsigned N>
struct is_array<T1[N]> : true_type {};

template <typename T1>
struct is_const_pointer : false_type {};

template <typename T1>
struct is_const_pointer<T1* const> : true_type {};

int main()
{ 
  static_assert(is_const<int const>::value, "is_const failed for 'int const'");
  static_assert(is_const<int* const>::value, "is_const failed for 'int* const'");
  static_assert(!is_const<int>::value, "is_const failed for 'int'");
  static_assert(!is_const<int const*>::value, "is_const failed for 'int const*'");

  static_assert(is_pointer<int*>::value, "is_pointer failed for 'int*'");
  static_assert(is_pointer<int const*>::value, "is_pointer failed for 'int const*'");
  static_assert(is_pointer<int* const>::value, "is_pointer failed for 'int* const'");
  static_assert(!is_pointer<int>::value, "is_pointer failed for 'int'");

  static_assert(is_array<int[5]>::value, "is_array failed for 'int[5]'");
  static_assert(is_array<int const[7]>::value, "is_array failed for 'int const[7]'");
  static_assert(!is_array<int>::value, "is_array failed for 'int'");

  static_assert(is_const_pointer<int* const>::value, "is_const_pointer failed for 'int* const'");
  static_assert(!is_const_pointer<int*>::value, "is_const_pointer failed for 'int*'");
  static_assert(!is_const_pointer<int>::value, "is_const_pointer failed for 'int'");
  static_assert(!is_const_pointer<int const>::value, "is_const_pointer failed for 'int const'");
}