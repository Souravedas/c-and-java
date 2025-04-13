#include <iostream>
#include <string>
#include <vector>
#include <regex>

int main() {
    std::cout << "Using fixed set of regular expressions and test strings from the assignment.\n";

    // Fixed regex patterns from assignment
    std::vector<std::regex> regexes;
    std::vector<std::string> patterns = {
        "a(bc)de",  // 1. Zero or more
        "a(bc)+de",  // 2. One or more
        "a(bc)?de"   // 3. Once or not at all
    };

    // Compile the regex patterns
    for (const auto& pattern : patterns) {
        try {
            regexes.emplace_back("^" + pattern + "$", std::regex::extended);
        } catch (const std::regex_error &e) {
            std::cerr << "Invalid regex: " << pattern << "\n";
            return 1;
        }
    }

    // Fixed test strings
    std::vector<std::string> testStrings = {
        "ade",         // Matches pattern 1 and 3
        "abcbcde",     // Matches all 3 patterns
        "abcbde",      // Matches none
        "abcde",       // Matches pattern 2 and 3
        "abc"           // Matches none
    };

    for (const auto& s : testStrings) {
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
