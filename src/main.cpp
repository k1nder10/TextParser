#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <stdexcept>

#include "Trie.hpp"


static constexpr bool IsDelimiter(const char symbol, 
                                  std::string_view delimiters) {
    return delimiters.find(symbol) != std::string_view::npos;
}


static void Split(Trie* words, 
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
                words->Insert(word);
                word.clear();
            }
        }
    }

    if (!word.empty()) words->Insert(word);
}


int main() {
    try {
        auto words = std::make_unique<Trie>();
        const char* english_punctuation_signs = " ";
        std::string line;

        while (std::getline(std::cin, line)) {
            if (line == "endline") break;
            
            Split(words.get(), line, english_punctuation_signs);
        }

        std::cout << "Number of unique words: " << words->WordsCount() << '\n';
    }
    catch (const std::exception& e) {
        std::cerr << "Error catched: " << e.what() << '\n';
    }

    return 0;   
}