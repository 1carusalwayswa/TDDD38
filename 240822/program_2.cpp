#include <algorithm>
#include <cassert>
#include <iterator>
#include <string>
#include <type_traits>
#include <vector>
#include <deque>
#include <type_traits>
#include <iostream>

template<typename T>
struct isArr : std::false_type {};

template<typename T, size_t N>
struct isArr<T[N]> : std::true_type {};

template<typename T>
struct isArr<T[]> : std::true_type {};

template<typename T>
concept isBool = std::is_same_v<T, bool>;

template<typename T>
concept isSigned = std::is_signed_v<T>;

template<typename T>
concept isContainerWithChar = requires() {
    requires std::is_same_v<typename T::value_type, char>;
};

template<typename T>
concept isContainer = requires() {
    typename T::iterator;
};

template<typename T>
concept isArr_ = isArr<T>::value;

template<typename T>
concept isArrOrContainer = isArr_<T> || isContainer<T>;


template <typename T>
T& negate(T& value);

namespace details {
    template<typename T>
    requires isBool<T>
    T& negate_helper(T& t, int, int, int, int) {
        return t = (!t);
    }

    template<isSigned T>
    T& negate_helper(T& t, float, int, int, int) {
        return t = -t;
    }

    template<typename T>
    requires isContainerWithChar<T>
    T& negate_helper(T& t, float, float, int, int) {
        reverse(t.begin(), t.end());
        return t;
    }

    template<typename T>
    requires isArrOrContainer<T>
    T& negate_helper(T& t, float, float, float, int) {
        for (auto& it: t) {
            it = negate(it);
        }
        return t;
    } 

    template<typename T>
    T& negate_helper(T& t, float, float, float, float) {
        t = ~t;
        return t;
    }

}

template<typename T>
T& negate(T& t) {
    return details::negate_helper(t, 0, 0, 0, 0);
}

int main()
{
    // signed value
    double n { 1.0 };
    std::cout << std::is_signed<double>::value << std::endl;
    assert(negate(n) == -1.0);

    // bool value
    bool b { true };
    assert(negate(b) == false);

    // bitwise negation
    unsigned u { 2196674553u };
    assert(negate(u) == 2098292742u);

    // string
    std::string s { "drawer" };
    assert(negate(s) == "reward");

    // container
    std::vector<int> v { 1, -2, 3, -4 };
    assert(( negate(v) == std::vector<int>{ -1, 2, -3, 4 } ));

    // recursive container case
    std::vector<std::deque<std::string>> r {
	std::deque<std::string>{ "bat", "brag" },
	std::deque<std::string>{ "flow", "loop" }
    };

    std::vector<std::deque<std::string>> result {
	std::deque<std::string>{ "tab", "garb" },
	std::deque<std::string>{ "wolf", "pool" }
    };

    assert(negate(r) == result);

    // C-array case
    int a[] { 6, -4, 0, 5 };
    negate(a);

    assert(a[0] == -6);
    assert(a[1] == 4);
    assert(a[2] == 0);
    assert(a[3] == -5);
}