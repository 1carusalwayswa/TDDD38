#include <iostream>
#include <list>
#include <map>
#include <string>
#include <utility>
#include <vector>

/** TESTCASES **/

/* Expected output:

1 2 3 
1 2 
one two 
(1, one) (2, two) 
one three two 

 */
template<typename T, typename U, typename Callable>
concept Addable1 = requires(std::pair<T,U> t, Callable const& call) {
    call(t.first);
};

template<typename T, typename U, typename Callable>
concept Addable2 = requires(std::pair<T,U> t, Callable const& call) {
    call(t.second);
};

template<typename T, typename U, typename Callable>
concept Addable3 = requires(std::pair<T,U> const& t, Callable const& call) {
    call(t.first, t.second);
};

template<typename T, typename U, typename Callable>
requires Addable1<T, U, Callable>
auto add(std::pair<T,U> const& t, Callable const& call, int, int, int) {
    call(t.first);
}

template<typename T, typename U, typename Callable>
requires Addable2<T, U, Callable>
auto add(std::pair<T,U> const& t, Callable const& call, float, int, int) {
    call(t.second);
}

template<typename T, typename U, typename Callable>
requires Addable3<T, U, Callable>
auto add(std::pair<T,U> const& t, Callable const& call, float, float, int) {
    call(t.first, t.second);
}

template<typename T, typename Callable>
auto add(T const& t, Callable const& call, float, float, float) {
    call(t);
}

template<typename T, typename Callable>
void iterate(T begin, T const& end, Callable const& call) {
    while (begin != end) {
        add(*begin, call, 0, 0, 0);
        begin++;
    }
}

void print(int key, std::string const& value)
{
    std::cout << "(" << key << ", " << value << ") ";
}

struct IntPrinter
{
    void operator()(int key) const
    {
        std::cout << key << " ";
    };
};

int main()
{
    std::vector<int> v { 1, 2, 3 };
    iterate(v.begin(), v.end(), [](int v) { std::cout << v << " "; });
    std::cout << std::endl;

    std::list<std::pair<int, std::string>> l { { 1, "one" }, { 2, "two" } };
    iterate(l.begin(), l.end(), IntPrinter{});
    std::cout << std::endl;

    iterate(l.begin(), l.end(), [](std::string const& v) { std::cout << v << " "; });
    std::cout << std::endl;

    iterate(l.begin(), l.end(), print);
    std::cout << std::endl;

    std::map<std::string, std::string> m { { "one", "1" }, { "two", "2" }, { "three", "3" } };
    iterate(m.begin(), m.end(), [](std::string const& k) { std::cout << k << " "; });
    std::cout << std::endl;
}