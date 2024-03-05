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
    auto fileOffset = idx.getIndex(word);
    std::string line;
    if (fileOffset < 0){
        ERROR("Could not get dictionary offset for '{}'", word);
        return line;
    }

    dictStream.seekg(fileOffset);
    std::getline(dictStream, line);
    return line;
}

Entry Dictionary::getEntries(std::string word)
{
    Entry ret;
    std::string lineToParse = getFirstMatchingLine(word);
    size_t curPos = 0;

    ret.original = getNextToken(lineToParse, "\t", curPos);
    ret.translation = getNextToken(lineToParse, "\t", curPos);

    return ret;
}

