#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <set>
#include <stdexcept>

#include "Trie.hpp"


static constexpr bool IsDelimiter(const char symbol, 
                                  std::string_view delimiters) {
    for (const auto del: delimiters) {
        if (symbol == del) return true;
    }

    return false;
}


static void Split(std::set<std::string>& words, 
                  const std::string& str,
                  std::string_view delimiters) {
    std::string word;
    std::istringstream iss(str);
    char symbol{};

    while (iss.get(symbol)) { 
        if (!IsDelimiter(symbol, delimiters)) {
            word.push_back(symbol);
        }
        else {
            if (!word.empty()) {
                words.insert(word);
                word.clear();
            }
        }
    }

    if (!word.empty()) words.insert(word);
}


int main() {
    try {
        auto trie = std::make_unique<Trie>();

        const char* english_punctuation_signs = " ";
        std::set<std::string> words;
        std::string line;

        while (std::getline(std::cin, line)) {
            if (line == "endline") break;
            
            Split(words, line, english_punctuation_signs);

            for (const auto& word: words) trie->Insert(word);

            words.clear();
        }

        std::cout << "Number of unique words: " << trie->WordsCount() << '\n';
    }
    catch (const std::exception& e) {
        std::cerr << "Error catched: " << e.what() << '\n';
    }

    return 0;   
}