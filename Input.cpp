#include "Input.h"

Input::Input(Tree* tree)
{
    _tree = tree;
}

void Input::Run(Outputs action)
{
    do
    {
        if (action == Outputs::enter_word)
            action = enterWord();
        if (action == Outputs::add_dictionary)
            action = addDictionary();
    } while (action != Outputs::_exit);
}

Outputs Input::addDictionary()
{
    std::string _s;
    std::string word;
    std::string wrong_msg = "Wrong input. Enter one or more characters [a-z]";
    std::string message = "Enter a word to add to the dictionary [a-z] (0 - Exit, 1 - Go to autofill): ";
    bool wrong = false;
    do
    {
        if (wrong)
            std::cout << wrong_msg << std::endl;
        wrong = false;
        _tree->clear();
        _tree->findWords(_tree->Root, 0, _s, 20);
        _tree->words.listValues("Keywords in the dictionary: ", false);
        std::cout << message;
        std::cin >> word;
        while (std::cin.get() != '\n')
        {
        }

        if (word == "0")
            return Outputs::_exit;
        if (word == "1")
        {
            std::cout << std::endl;
            return Outputs::enter_word;
        }
        if (word.length() == 0)
        {
            wrong = true;
            continue;
        }

        for (int i{ 0 }; i < word.length(); i++)
        {
            if (word[i] < 97 || word[i] > 122)
            {
                wrong = true;
                break;
            }
        }
        if (wrong)
            continue;

        _tree->insert(word);
        std::cout << std::endl;

    } while (true);

    return Outputs();
}

Outputs Input::enterWord()
{
    std::string _s;
    std::string word;
    std::string wrong_msg = "Wrong input. Enter one or more characters [a-z]";
    std::string message = "Enter a part of any keyword from the dictionary (0 - Exit, 1 - Go to adding to the dictionary): ";
    bool wrong = false;

    do
    {
        if (wrong)
            std::cout << wrong_msg << std::endl;
        wrong = false;
        _tree->clear();
        _tree->findWords(_tree->Root, 0, _s, 20);
        _tree->words.listValues("Keywords in the dictionary: ", false);
        std::cout << message;
        std::cin >> word;
        while (std::cin.get() != '\n')
        {
        }
        if (word == "0")
            return Outputs::_exit;
        if (word == "1")
        {
            std::cout << std::endl;
            return Outputs::add_dictionary;
        }

        if (word.length() == 0)
        {
            wrong = true;
            continue;
        }

        for (int i{ 0 }; i < word.length(); i++)
        {
            if (word[i] < 97 || word[i] > 122)
            {
                wrong = true;
                break;
            }
        }
        if (wrong)
            continue;
        _tree->clear();
        _tree->findWords(_tree->Root, 0, word, 20);
        _tree->words.listValues("Keywords for autocomplete: ", false);
        std::cout << std::endl;
    } while (true);

    return Outputs::_exit;
}