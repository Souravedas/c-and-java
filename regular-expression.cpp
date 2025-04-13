#include <iostream>
#include <string>
#include <vector>
#include <regex>

int main() {
    int n, m;
    std::cout << "Enter number of regular expressions: ";
    std::cin >> n;

    std::vector<std::regex> regexes;
    std::string pattern;
    std::cout << "Enter each regular expression one by one:\n";
    while (n-- && std::cin >> pattern) {
        try {
            regexes.emplace_back("^" + pattern + "$", std::regex::extended);
        } catch (const std::regex_error &e) {
            std::cerr << "Invalid regex: " << pattern << "\n";
            return 1;
        }
    }

    std::cout << "Enter number of test strings: ";
    std::cin >> m;
    std::cout << "Enter each test string one by one:\n";
    std::string s;
    while (m-- && std::cin >> s) {
        bool matched = false;
        for (size_t i = 0; i < regexes.size(); ++i) {
            if (std::regex_match(s, regexes[i])) {
                std::cout << "YES, " << (i + 1) << "\n";
                matched = true;
                break;
            }
        }
        if (!matched) std::cout << "NO, 0\n";
    }
    return 0;
}
