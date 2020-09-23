#include "Trie.hpp"


void Trie::Insert(std::string_view word) {
    auto curr = root_.get();

    for (size_t i = 0; i < word.length(); ++i) {

        // go down through the tree
        if (auto it = curr->children.find(word[i]); 
            it != curr->children.end()) {
            curr = it->second.get();
        }

        // insert a new node
        else {
            curr->children[word[i]] = std::make_unique<Node>();
            curr = curr->children[word[i]].get();
        }
    }

    curr->complete_word = true;
}


bool Trie::Search(std::string_view word) const {
    auto curr = root_.get();

    for (size_t i = 0; i < word.length(); ++i) {
        if (auto it = curr->children.find(word[i]);
            it != curr->children.end()) {
                curr = it->second.get();
            }
        else {
            return false;
        }
    }

    return curr->complete_word;
}


uint64_t Trie::WordsCount() const {
    return WordsCount(root_.get());
}