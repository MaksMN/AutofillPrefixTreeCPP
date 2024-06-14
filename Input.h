#pragma once
#include <iostream>
#include <string>
#include "Tree.h"
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
    Tree* _tree;

public:
    Input() = default;
    Input(Tree* tree);
    ~Input() = default;

    void Run(Outputs action = enter_word);

    Outputs addDictionary();
    Outputs enterWord();
};