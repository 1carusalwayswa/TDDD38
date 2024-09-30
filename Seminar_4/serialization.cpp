#include <istream>
#include <iostream>
#include <sstream>
#include <limits>

using namespace std;

struct Product
{
    string name;
    double price;
    int inventory;
};

ostream& operator<<(ostream& os, Product const& product)
{
    return os << product.name << ": "
              << product.price << " kr ("
              << product.inventory << " available)";
}

template <typename T>
T read(istream& is)
{
    T data;
    is >> data;
    return data;
}

template <>
std::string read(istream& is) {
    std::string res_str;
    // char single_ch; 

    // while (is.get(single_ch) && single_ch != '#');

    // while (is.get(single_ch) && single_ch != '#') {
    //     res_str += single_ch;
    // }
    is.ignore(numeric_limits<streamsize>::max(), '#');
    getline(is, res_str, '#');

    return res_str;
}

template <>
Product read(istream& is) {
    Product res_pdt {
        read<string>(is),
        read<double>(is),
        read<int>(is)
    };
    return res_pdt;
}

template <typename T>
void write(ostream& os, T const& t)
{
    os << t << ' ';
}

template <>
void write(ostream& os, std::string const& t) {
    os << "#" << t << "#";
}

template <>
void write(ostream& os, Product const& t) {
    write(os, t.name);
    write(os, t.price);
    write(os, t.inventory);

}

int main()
{
    stringstream ss;
    { // send data to ss
        Product apple {"Red Apple", 1.5, 100};
        Product laptop{"Laptop", 5995.0, 10};
        Product monitor{"4K Monitor", 8790.0, 1};
        write(ss, apple);
        write(ss, laptop);
        write(ss, monitor);
    }
    cout << ss.str() << endl;
    { // recieve data from ss
        Product apple  {read<Product>(ss)};
        Product laptop {read<Product>(ss)};
        Product monitor{read<Product>(ss)};
        cout << apple << endl
             << laptop << endl
             << monitor << endl;
    }
}