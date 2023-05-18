#pragma once
#include <iostream>
#include <string>
#include "Trie.h"
enum Outputs
{
    enter_word,
    add_dictionary,
    back,
    _exit
};
class Input
{
private:
    std::string word;
    std::string key;
    Trie *_trie;

public:
    Input() = default;
    Input(Trie *trie);
    ~Input() = default;

    void Run(Outputs action = enter_word);

    Outputs addDictionary();
    Outputs enterWord();
};