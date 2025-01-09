#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>
#include <cmath>

std::vector<double> get_num() {
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    std::vector<double> nums { };
    std::transform(std::istream_iterator<std::string>{ ss }, 
                   std::istream_iterator<std::string>{ },
                   std::back_inserter(nums),
                   [](std::string const& str) {
                        return std::stod(str);
                   });
    return nums;
}

double my_pow(double x, int k) {
    double ans = 1;
    while(k) {
        if (k & 1) {
            ans *= x;
        }
        x *= x;
        k >>= 1;
    }
    return ans;
}

int main() {
    std::cout << "Enter coefficients: ";
    std::vector<double> coefficients { get_num() };
    // for (auto& num: coefficients) {
    //     std::cout << num << std::endl;
    // }
    std::string init_str = "p(x) = ";
    int cnt = -1;
    std::cout << std::accumulate(std::begin(coefficients), std::end(coefficients),
                                    init_str,
                                    [&cnt](std::string line, double cur) {
                                        cnt++;
                                        if (cnt == 0) {
                                            return line + std::to_string((int)cur);
                                        } else if (cnt == 1) {
                                            return line + '+' + std::to_string((int)cur) + "*x"; 
                                        }
                                        return line + '+' + std::to_string((int)cur) + "*x^" + std::to_string((int)cnt); 
                                    }) << std::endl;
    std::cout << "Enter values of x to evaluate: ";
    std::vector<double> x_values { get_num() };

    // std::cout << 1 << '\n';
    std::vector<double> ans { };
    std::transform(std::begin(x_values), std::end(x_values), std::back_inserter(ans),
                   [&coefficients](double x_value) {
                    int cnt = 0;
                    int ans = std::accumulate(std::begin(coefficients), std::end(coefficients),
                                                0, [&cnt, &x_value](double sum, double cur) {
                                                        // std::cout << sum << " " << cur << " " << x_value << " " << pow(x_value, cnt) << '\n';
                                                        return sum += cur * pow(x_value, cnt++);
                                                });
                    std::cout << "p(" << (int)x_value << ") = " << ans << '\n';
                    return ans;
                   });
    
}

/* Running examples:

$ ./a.out 
Enter coefficients: 1 2 3
p(x) = 1+2*x+3*x^2
Enter values of x to evaluate: 1 2 3
p(1) = 6
p(2) = 17
p(3) = 34

$ ./a.out 
Enter coefficients: 1 0 1
p(x) = 1+0*x+1*x^2
Enter values of x to evaluate: 0 1 2 3 4
p(0) = 1
p(1) = 2
p(2) = 5
p(3) = 10
p(4) = 17

$ ./a.out 
Enter coefficients: 1 1 1 1 1 1 1
p(x) = 1+1*x+1*x^2+1*x^3+1*x^4+1*x^5+1*x^6
Enter values of x to evaluate: 0 1 2
p(0) = 1
p(1) = 7
p(2) = 127

$ ./a.out 
Enter coefficients: 10
p(x) = 10
Enter values of x to evaluate: 0 1 2 3 4 5 6 7 8 9
p(0) = 10
p(1) = 10
p(2) = 10
p(3) = 10
p(4) = 10
p(5) = 10
p(6) = 10
p(7) = 10
p(8) = 10
p(9) = 10

*/