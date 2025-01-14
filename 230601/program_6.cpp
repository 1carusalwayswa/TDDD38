#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <numeric>

struct queue_extractor
{
    std::priority_queue<double>& que;
    double operator()() {
        double res = que.top();
        que.pop();
        return res;
    }
};


namespace std {
    istream& operator>>(istream& is, std::vector<int>& dataset) {
        std::string line { };
        std::getline(is, line);
        std::stringstream ss { line };
        dataset = std::vector<int> { std::istream_iterator<int> { ss },
                                         std::istream_iterator<int> { } };
        return is;
    }

    // ostream& operator<<(ostream& os, double data) {
    //     os << 
    // }
}

int main() {
    int n;
    std::cin >> n;
    std::ifstream ifs("/Users/lyon/Desktop/TDDD38/practice/230601/data.txt");
    std::vector<std::vector<int>> datasets { std::istream_iterator<std::vector<int>> { ifs }, 
                                                    std::istream_iterator<std::vector<int>> { } };
    std::vector<double> data_averages;
    std::transform(std::begin(datasets), std::end(datasets),
                    std::back_inserter(data_averages), 
                    [](std::vector<int>& dataset) {
                        int sum = std::accumulate(std::begin(dataset), std::end(dataset), 0);
                        double ans = sum * 1.0 / dataset.size();
                        return ans;
                    });
    std::priority_queue<double> que { std::begin(data_averages), std::end(data_averages) };

    // std::partial_sort(std::begin(data_averages), std::next(std::begin(data_averages), n),
    //                   std::end(data_averages), std::greater<double>{});
    size_t size_n = n;
    std::vector<double> ans { }; 
    ans.reserve(n);
    std::generate_n(std::back_inserter(ans), n, [&que]() {
        double val = que.top();
        que.pop();
        return val;
    });
    // std::transform(std::begin(ans), std::end(ans), 
    //                 std::begin(ans), 
    //                 [&que](double) {
    //                     double res = que.top();
    //                     que.pop();
    //                     return res;                                       
    //                 });
    
    std::copy(std::begin(ans), std::end(ans), std::ostream_iterator<double> { std::cout, "\n" });
}