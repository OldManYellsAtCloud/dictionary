#include "dictionary.h"
#include <loglibrary.h>
#include "utils.h"


/**
 * @brief Dictionary::Dictionary
 * Constructor.
 * @param dictPath
 * Path to the dictionary file.
 */
Dictionary::Dictionary(std::string dictPath): idx{dictPath}, dictPath_{dictPath}
{
    dictStream = std::fstream(dictPath, std::ios_base::in);
}

/**
 * @brief Dictionary::~Dictionary
 * Destructor.
 */
Dictionary::~Dictionary()
{
    dictStream.close();
}

/**
 * @brief Dictionary::Dictionary
 * Copy constructor.
 * @param other
 * The other Dictionary object to copy.
 */
Dictionary::Dictionary(const Dictionary &other): idx{other.dictPath_}, dictPath_{other.dictPath_}
{
    dictStream = std::fstream(dictPath_, std::ios_base::in);
}

/**
 * @brief Dictionary::operator =
 * Assignment operator.
 * @param other
 * The other Dictionary to assign to this.
 * @return
 * This Dictionary with the values from the argument.
 */
Dictionary &Dictionary::operator=(const Dictionary &other)
{
    if (this == &other)
        return *this;

    idx = DictionaryIndex{other.dictPath_};
    dictPath_ = other.dictPath_;
    return *this;
}

/**
 * @brief Dictionary::getFirstMatchingLine
 * Return a string from the dictionary file matching the `word` argument.
 * This is method is meant for testing the class.
 * @param word
 * The starting word to look for.
 * @return
 * The first whole line matching the argument.
 */
std::string Dictionary::getFirstMatchingLine(std::string word)
{
    auto roughOffset = idx.getIndex(word);
    std::string line;
    if (roughOffset < 0){
        ERROR("Could not get dictionary offset for '{}'", word);
        return line;
    }

    dictStream.seekg(roughOffset);
    std::getline(dictStream, line);
    return line;
}

DictionaryEntry::Entry Dictionary::getFirstEntry(std::string word)
{
    DictionaryEntry::Entry ret;
    std::string lineToParse = getFirstMatchingLine(word);
    size_t curPos = 0;

    ret = DictionaryEntry::parseEntry(lineToParse);
    return ret;
}

std::vector<DictionaryEntry::Entry> Dictionary::getEntries(std::string word)
{
    std::vector<DictionaryEntry::Entry> ret;
    int num = 5;
    long startIndex = getBestMatchingIndex(word);

    dictStream.seekg(startIndex);

    std::string tmp;

    while (num > 0 && !dictStream.eof()){
        std::getline(dictStream, tmp);
        if (!tmp.size())
            continue;
        ret.push_back(DictionaryEntry::parseEntry(tmp));
        --num;
    }
    dictStream.clear();
    return ret;
}

long Dictionary::getBestMatchingIndex(std::string word)
{
    word = toLowerCase(word);
    long roughIndex = idx.getIndex(word);

    if (roughIndex < 0){
        ERROR("Could not get dictionary offset for {}", word);
    }

    long lastIndex = roughIndex;
    dictStream.seekg(roughIndex);

    std::string line = "";

    do {
        std::getline(dictStream, line);
        line = toLowerCase(line);
        if (line.starts_with(word)){
            break;
        }
        if (word < line){
            break;
        }
        lastIndex = dictStream.tellg();
    } while (!dictStream.eof());

    dictStream.clear();
    return lastIndex;
}
