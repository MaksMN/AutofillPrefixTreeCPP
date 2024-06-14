#include "Tree.h"

Tree::Tree()
{
    Root = getNewNode();
}

Tree::~Tree()
{
    erase(Root);
}

Node* Tree::getNewNode()
{
    // Выделяем память по новый узел
    struct Node* pNode = new Node;
    pNode->freq = 0;
    // устанавливаем флаг конца слова в false
    pNode->isEndOfWord = false;

    // инициализируем детей нулевым указателем
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;
    return pNode;
}

void Tree::insert(std::string key)
{
    Node* node = Root;

    for (int i = 0; i < key.length(); i++)
    {
        // вычисляем индекс в алфавите через смещение относительно первой буквы
        int index = key[i] - 'a';

        // если указатель пустой, т.е. детей с таким префиксом нет
        // создаем новый узел
        if (!node->children[index])
            node->children[index] = getNewNode();
        // else
        node->children[index]->freq += 1;
        node = node->children[index];
    }

    // помечаем последний узел как лист, т.е. конец слова
    node->isEndOfWord = true;
}

void Tree::findWords(Node* root, int ind, std::string& key, int max, bool unique)
{

    if (root == nullptr)
        return;

    if (unique)
    {
        if (root->isEndOfWord)
        {
            words.insertAtEnd(buf);
            return;
        }
    }
    else if (root->isEndOfWord && compare(buf, key) && words.getLength() < max)
    {
        words.insertAtEnd(buf);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i] != nullptr)
        {
            buf[ind] = i + 'a';
            findWords(root->children[i], ind + 1, key, max, unique);
            buf[ind] = '\0';
        }
    }
}

bool Tree::compare(char ch[], std::string& key)
{
    if (key == std::string())
    {
        return true;
    }
    if (key.length() > BUF_SIZE)
        return false;
    for (int i{ 0 }; i < key.length(); i++)
    {
        if (key[i] != ch[i])
            return false;
    }
    return true;
}

void Tree::clear()
{
    words.erase();
    for (int i{ 0 }; i < BUF_SIZE; i++)
    {
        buf[i] = '\0';
    }
}

void Tree::erase(Node* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i] != nullptr)
        {
            erase(root->children[i]);
        }
    }
    delete root;
}