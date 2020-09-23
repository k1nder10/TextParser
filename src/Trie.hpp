#ifndef TRIE_HPP
#define TRIE_HPP

#include <string_view>
#include <map>
#include <memory>


class Trie {
public:
    Trie() : root_(new Node) {}

    void Insert(std::string_view word);

    bool Search(std::string_view word) const;

    uint64_t WordsCount() const;


private:
    struct Node;

    // TODO: change to a non-recursive version
    inline uint64_t WordsCount(Node* node) const {
        if (node->children.empty()) return node->complete_word;

        uint64_t count = 0;
        for (auto it = node->children.begin(); it != node->children.end(); ++it) {
            count += WordsCount(it->second.get());
        }

        return count + static_cast<uint64_t>(node->complete_word);
    }

    struct Node {
        bool complete_word{false};
        std::map<char, std::unique_ptr<Node>> children;
    };
    using NodePtr = std::unique_ptr<Node>;

private:
    NodePtr root_; 
};

#endif