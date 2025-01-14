// essentialy, when we want to use no-loop way to read several data.
// we always follow this routine: string -> stringstream -> special data (Thx, my bro ohao)

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <sstream>

namespace std {
    std::istream& operator>>(std::istream& is, std::set<std::string>& words) {
        std::string line;
        std::getline(is, line, '\n');
        std::stringstream ss(line);
        words = std::set<std::string>{std::istream_iterator<std::string> {ss},
                        std::istream_iterator<std::string> {}};
        return is;
    }
}

std::set<std::string> get_common_words(std::set<std::string> const& a, std::set<std::string> const& b) {
    std::set<std::string> common { };
    std::set_intersection(std::begin(a), std::end(a), std::begin(b), std::end(b),
                            std::inserter(common, std::end(common)));
    return common;
}

int main() {
    std::vector<std::set<std::string>> lines { std::istream_iterator<std::set<std::string>> { std::cin }, 
                                                std::istream_iterator<std::set<std::string>> { }};
    // std::transform(std::istream_iterator<Line>{std::cin},
    //                std::istream_iterator<Line>{ },
    //                std::back_inserter(lines),
    //                [](Line const& line) {
    //                     std::stringstream ss(line.str);
    //                     std::set<std::string> words {std::istream_iterator<std::string> {ss},
    //                                     std::istream_iterator<std::string> {}};
    //                     return words;
    //                });
    
    // lines.erase(std::remove_if(std::begin(lines), std::end(lines), [](auto&& words) {
    //     return words.size() == 0;
    // }), std::end(lines));
    std::erase_if(lines, [](auto&& words) {
        return words.size() == 0;
    });
    
    if (lines.size() > 0) {
        std::set<std::string> common { std::accumulate(std::begin(lines),
                                std::end(lines), lines.front(), get_common_words) };
        if (common.size() > 0) {
            std::copy(std::begin(common), std::end(common),
                         std::ostream_iterator<std::string> {std::cout, "\n"});
        }
    }
}