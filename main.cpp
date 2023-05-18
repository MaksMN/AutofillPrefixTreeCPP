#include <iostream>
#include <string>
#include "Trie.h"
#include "Input.h"

int main(int argc, const char *argv[])
{
    Trie t;

    t.insert("dog");
    t.insert("doctor");
    t.insert("doc");
    t.insert("document");
    t.insert("dot");
    t.insert("duck");
    t.insert("man");
    t.insert("mail");
    t.insert("master");
    t.insert("model");
    t.insert("moment");
    t.insert("mode");

    Input input(&t);
    input.Run(Outputs::enter_word);
    return 0;
}