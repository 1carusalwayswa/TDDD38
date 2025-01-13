#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <numeric>
#include <cmath>

std::vector<double> get_num() {
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    std::vector<double> num_str {std::istream_iterator<double> { ss }, std::istream_iterator<double> { }};
    return num_str;
}

double get_inner_product(std::vector<double> const& u, std::vector<double> const& v) {
    int idx = 0;
    double inner_product = std::accumulate(std::begin(u), 
                            std::end(u), 0, [&v, &idx](double sum, double cur_elem) {
                                return sum += cur_elem * v[idx++];
                            }
                        );
    return inner_product;
}

int main() {
    int n;
    std::cout << "Enter dimensions: ";
    std::cin >> n;
    getchar();

    std::cout << "Enter u: ";
    std::vector<double> u {get_num()};
    std::cout << "Enter v: ";
    std::vector<double> v {get_num()};

    std::cout << "Their scalar product is: " << get_inner_product(u, v) << '\n';

    double inner_product_u = get_inner_product(u, u);
    double sqrt_inner_product_u = sqrt(inner_product_u);
    double inner_product_v = get_inner_product(v, v);
    double sqrt_inner_product_v = sqrt(inner_product_v);

    std::transform(std::begin(u), std::end(u), std::begin(u), [&sqrt_inner_product_u](int cur_elem) {
        return cur_elem / sqrt_inner_product_u; 
    });
    
    std::transform(std::begin(v), std::end(v), std::begin(v), [&sqrt_inner_product_v](int cur_elem) {
        return cur_elem / sqrt_inner_product_v; 
    });

    std::cout << "u = [ ";
    std::copy(std::begin(u), std::end(u), std::ostream_iterator<double>{ std::cout, " " });
    std::cout << "]\n";
    std::cout << "u = [ ";
    std::copy(std::begin(v), std::end(v), std::ostream_iterator<double>{ std::cout, " " });
    std::cout << "]\n";
}

/* Example outputs:

Enter dimensions: 2
Enter u: 1 1
Enter v: 0 1
Their scalar product is: 1
u = [ 0.707107 0.707107 ]
v = [ 0 1 ]


Enter dimensions: 3 
Enter u: 0 1 2
Enter v: 3 4 5
Their scalar product is: 14
u = [ 0 0.447214 0.894427 ]
v = [ 0.424264 0.565685 0.707107 ]


Enter dimensions: 4 
Enter u: 1 0 0 0
Enter v: 0 0 0 1
Their scalar product is: 0
u = [ 1 0 0 0 ]
v = [ 0 0 0 1 ]

*/