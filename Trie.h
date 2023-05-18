#pragma once
#include <string>
#include "Array.h"

const int ALPHABET_SIZE = 26;
const int BUF_SIZE = 26;

/// @brief Структура узла дерева
struct Node
{
    struct Node *children[ALPHABET_SIZE];
    int freq = 0;
    bool isEndOfWord;
};

/// @brief Префиксное дерево для хранения ключевых слов
class Trie
{
private:
    char buf[BUF_SIZE]{};
    /// @brief Удаляет всю динамическую память, выделенную под узлы
    /// @param node Коневой узел
    void erase(Node *node);

    /// @brief Проверяет совпадение начала строки с началом массива символов.
    /// @param ch 
    /// @param key Если пустая строка - поиск всегда является удачным.
    /// @return 
    bool compare(char ch[], std::string &key);
    Node *getNewNode();

public:
    Trie();
    ~Trie();
    Node *Root; // Корневой узел    
    Array<std::string> words; // Массив слов полученный в методе findWords()

    /// @brief // Вставляет ключ в дерево, если его нет, иначе если ключ является префиксом узла дерева помечает конец слова
    /// @param str 
    void insert(std::string str);

    /// @brief Ищет слова в дереве и записывает их в массив trie->words
    /// @param root Корень дерева
    /// @param ind Индекс
    /// @param key Ключевое слово
    /// @param max Максимальное количество слов записываемых в trie->words, если их больше, то пропускаются.
    /// @param unique true - вывод уникальных префиксов, false - вывод всех слов соответствующих шаблону key
    void findWords(Node *root, int ind, std::string &key, int max, bool unique = false);

    /// @brief Очищает trie->words
    void clear();
};