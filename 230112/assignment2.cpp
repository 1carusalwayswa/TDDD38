#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cassert>
#include <sstream>


template <typename T>
class Formatter {
public:
    static void format(std::ostream& os, const T& obj) {
        os << obj;
    }
};

template<>
class Formatter<std::string> {
public:
    static void format(std::ostream& os, const std::string& obj) {
        os << "<" << obj << ">";
    }
};

// template<typename T>
// class Formatter<std::vector<T>> {
// public:
//     static void format(std::ostream& os, const std::vector<T>& obj) {
//         os << "<";
//         for (T const& element : obj) {
//             os << " ";
//             Formatter<T>::format(os, element);
//         }
//         os << ">";
//     }
// };

template <typename T>
class Formatter<std::vector<T>>
{
public:

    static void format(std::ostream& os, std::vector<T> const& data)
    {
        os << "{";
        for (T const& element : data)
        {
            os << " ";
            Formatter<T>::format(os, element);
        }
        os << " }";
    }
    
};

namespace details {
    void format(std::ostringstream& oss, std::string const& specifier) {
        auto index = specifier.find("{}");
        if (index != std::string::npos) {
            throw std::runtime_error{"Need more argument pass to the formet"};
        }
        oss << specifier;
    }

    template <typename Arg, typename... Args>
    void format(std::ostringstream& oss, std::string const& specifier, Arg&& arg, Args&&... args) {
        int index = specifier.find("{}");
        if (index == std::string::npos) {
            throw std::runtime_error{"Extra argument pass to the formet"};
        }
        std::string tmp {specifier};
        oss << tmp.erase(index);
        Formatter<Arg>::format(oss, arg);
        format(oss, specifier.substr(index+2), args...);
    }
}

template <typename... Args>
std::string format(std::string const& specifier, Args&&... args) {
    std::ostringstream oss { };
    details::format(oss, specifier, args...);
    return oss.str();
}

int main()
{
    std::string str1 { format("Hello world!") };
    std::cout << str1 << '\n';
    assert(str1 == "Hello world!");
    
    std::string str2 { format("int: {}", 5) };
    assert(str2 == "int: 5");

    std::string my_string { "my string" };
    
    std::string str3 { format("string: {}", my_string) };
    std::cout << str3 << std::endl;
    assert(str3 == "string: <my string>");

    std::string str4 { format("{}:{}:{}", 1, 2, 3) };
    assert(str4 == "1:2:3");

    std::vector<std::string> v { "abc", "def", "ghi" };
    
    std::string str5 { format("vector: {}", v) };
    assert(str5 == "vector: { <abc> <def> <ghi> }");
    
    try
    {
        format("{}");
        assert(false);
    }
    catch (...) { }

    try
    {
        format("my string", 5);
        assert(false);
    }
    catch (...) { }
}