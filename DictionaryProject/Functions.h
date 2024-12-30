#pragma once
#include "Libary.h"

int convertCharToIndex(char c);

char convertIndexToChar(int i);

void insertWord(Trie& Dictionary, string word);

bool isLeafNode(Node*& node);

void solveRemoveWord(Node*& root, string& word, int index);

void removeWord(Trie& Dictionary, string& word);

void createTrieFromFile(Trie& dictionary, string fileName);

bool isWordExist(Trie& Dictionary, string word);

void collectWordsFromNode(Trie& Dictionary, Node* node, string word, vector<string>& suggestedWord);

vector<string> createSuggestedWordList(Trie& Dictionary, string& prefix);

void printWordsFromPrefix(Trie& Dictionary, string prefix, Display& display, bool f);

void generateSearchSuggestions(Trie& Dictionary, Display& display);

void proccessStartMenu(Point& current, const Point initial, Trie& Dictionary, Display& display);

void processEnter(Point current, const Point initial, Trie& Dictionary, Display& display, int& flag, char& choice);

void processAbout();

void processInsertWord(Trie& Dictionary, Display& display);

void processRemoveWord(Trie& Dictionary, Display& display);

void processSettings(Trie& Dictionary, Display& display, char& choice);

void processExit(Trie& Dictionary);
