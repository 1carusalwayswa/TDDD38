#include <utility>
#include <vector>
#include <map>
#include <list>
#include <iostream>

namespace details
{

    template <typename T, typename U, typename Callable>
    auto apply(std::pair<T, U> const& pair, Callable const& callable, int, int, int)
        -> decltype(callable(pair.first), std::declval<void>())
    {
        callable(pair.first);
    }

    template <typename T, typename U, typename Callable>
    auto apply(std::pair<T, U> const& pair, Callable const& callable, int, int, float)
        -> decltype(callable(pair.second), std::declval<void>())
    {
        callable(pair.second);
    }

    template <typename T, typename U, typename Callable>
    auto apply(std::pair<T, U> const& pair, Callable const& callable, int, float, float)
        -> decltype(callable(pair.first, pair.second), std::declval<void>())
    {
        callable(pair.first, pair.second);
    }

    template <typename T, typename Callable>
    void apply(T const& data, Callable const& callable, float, float, float)
    {
        callable(data);
    }

}

template <typename It, typename Callable>
void iterate(It begin, It end, Callable const& callable)
{
    while (begin != end)
    {
        details::apply(*begin, callable, 0, 0, 0);
        ++begin;
    }
}

/** TESTCASES **/

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