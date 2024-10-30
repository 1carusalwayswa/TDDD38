#include <utility>
#include <iostream>

template <typename T>
auto get_priority_helper(int, int, int, T&&t) -> decltype(t.first())
{
    return t.first();
}

template <typename T>
auto get_priority_helper(float, int , int, T&&t) -> decltype(t.second())
{
    return t.second();
}

template <typename T>
auto get_priority_helper(float, float, int, T&&t) -> decltype(t.third())
{
    return t.third();
}

template <typename T>
auto get_priority_helper(float, float, float, T&&t) {
    return 4;
}

template <typename T>
auto get_priority(T&& t)
{
    return get_priority_helper<T>(0, 0, 0, std::forward<T&&>(t));
}

struct X
{
  int first() const { return 1; }
};

struct Y
{
  int second() const { return 2; }
};

struct Z
{
  int third() const { return 3; }
};

struct XY
{
  int first() const { return 1; }
  int second() const { return 2; }
};

struct XZ
{
  int first() const { return 1; }
  int third() const { return 3; }
};

struct YZ
{
  int second() const { return 2; }
  int third() const { return 3; }
};

struct XYZ
{
  int first() const { return 1; }
  int second() const { return 2; }
  int third() const { return 3; }
};

int main()
{
  using std::cout;
  using std::endl;
  
    cout << get_priority(X{}) << endl
         << get_priority(Y{}) << endl
         << get_priority(Z{}) << endl
         << get_priority(XY{}) << endl
         << get_priority(XZ{}) << endl
         << get_priority(YZ{}) << endl
         << get_priority(XYZ{}) << endl
         << get_priority(5) << endl;
}