#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <fstream>
#include <vector>
#include "dictionaryindex.h"
#include "entry.h"


class Dictionary
{
private:
    DictionaryIndex idx;
    std::fstream dictStream;
    std::string dictPath_;
    long getBestMatchingIndex(std::string word);
public:
    explicit Dictionary(std::string dictPath);
    ~Dictionary();
    Dictionary(const Dictionary& other);

    Dictionary& operator=(const Dictionary& other);
    std::string getFirstMatchingLine(std::string word);
    DictionaryEntry::Entry getFirstEntry(std::string word);
    std::vector<DictionaryEntry::Entry> getEntries(std::string word);
};

#endif // DICTIONARY_H
