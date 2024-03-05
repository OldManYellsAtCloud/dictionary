#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <fstream>
#include "dictionaryindex.h"
#include "entry.h"

class Dictionary
{
private:
    DictionaryIndex idx;
    std::fstream dictStream;
    std::string dictPath_;
public:
    explicit Dictionary(std::string dictPath);
    ~Dictionary();
    Dictionary(const Dictionary& other);

    Dictionary& operator=(const Dictionary& other);
    std::string getFirstMatchingLine(std::string word);
    Entry getEntries(std::string word);
};

#endif // DICTIONARY_H
