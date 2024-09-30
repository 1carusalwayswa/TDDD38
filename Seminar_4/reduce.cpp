#include <cstddef> // gives access to size_t
#include <iostream>
#include <string>

using namespace std;

/*
  Your code here
 */

template <typename T>
T add(T const& a, T const& b) {
    return a + b;
}

template <typename T, size_t N>
// T const &arr[N] is wrong, which means a array include N T const& elements
// and ref dont have real memory, it cannot be stored in array.
// T const (&arr)[N] means: a ref of an array contains N T const& elements.
T reduce(T const (&arr)[N], T initial_val = {}, 
                        T (*op)(T const&, T const&) = add<T>) {
    T res {initial_val};
    for (size_t i = 0; i < N; i++) {
        res = op(res, arr[i]);
    }

    return res;
}

double multiply(double const& lhs, double const& rhs)
{
    return lhs * rhs;
}

int main()
{
    double pi[]{0.0505, 0.0505, 0.0405};
    double factorial[]{1.0, 2.0, 3.0, 4.0, 5.0};
    string concat[]{" ", "world"};
    cout << reduce({1,2,3,4,5}) << endl;
    cout << reduce(pi, 3.0) << endl;
    cout << reduce(factorial, 1.0, multiply) << endl;
    cout << reduce(concat, "hello"s) << endl;
}