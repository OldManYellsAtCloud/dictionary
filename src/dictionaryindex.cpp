#include "dictionaryindex.h"
#include <fstream>
#include <filesystem>
#include <loglibrary.h>

#include "utils.h"

/**
 * @brief DictionaryIndex::createIndex
 * Create index file from `filePath`
 * @param filePath
 * Path to the file that needs to be indexed. The file expected to be sorted alphabetically.
 * @return
 * True, in case the index creation was successful. False otherwise.
 */
void DictionaryIndex::loadIndex(const std::string &indexPath)
{
    if (!std::filesystem::exists(indexPath)){
        ERROR("{} does not exist!", indexPath);
        exit(1);
    }

    std::fstream indexFile {indexPath, std::ios_base::in};
    std::string indexKey;
    long indexVal;


    while (!indexFile.eof()){
        indexFile >> indexKey;
        indexFile >> indexVal;
        index[indexKey] = indexVal;
    }
    indexFile.close();
}

/**
 * @brief DictionaryIndex::createIndex
 * Create index file from an input text file.
 * The index is saved in the class' indexPath path.
 * @param filePath
 * The file to extract the index from.
 * @return
 * True in case of success.
 */
bool DictionaryIndex::createIndex(const std::string &filePath)
{
    if (!std::filesystem::exists(filePath)){
        ERROR("{} does not exist, can't create an index!", filePath);
        return false;
    }

    std::map<std::string, long> tmpIndex;
    std::fstream inputFile {filePath, std::ios_base::in};

    std::string fullLine;
    std::string comment = "# ";
    std::string firstCharsOfLine;
    std::string lastIndex = comment;

    while (!inputFile.eof()) {
        std::getline(inputFile, fullLine);
        firstCharsOfLine = getUnicodeSubstring(fullLine, 3, 0);

        if (firstCharsOfLine.starts_with(lastIndex)) // we have seen this, skip
            continue;

        if (firstCharsOfLine.starts_with(comment))
            continue;

        if (firstCharsOfLine.length() == 0)
            continue;

        lastIndex = getUnicodeSubstring(firstCharsOfLine, 2, 0);

        // store if it doesn't exist yet
        if (tmpIndex.count(lastIndex) == 0){
            tmpIndex[lastIndex] = (long(inputFile.tellp()) - fullLine.length() - 1);
        }
    }

    inputFile.close();
    persistIndex(tmpIndex);

    return true;
}

/**
 * @brief DictionaryIndex::persistIndex
 * Store the index from the argument in the indexFile specified in this class.
 * @param indexToPersist
 * The index to store.
 */
void DictionaryIndex::persistIndex(const std::map<std::string, long> indexToPersist)
{
    std::fstream indexFile {indexPath, std::ios_base::out | std::ios_base::trunc};

    for (auto [key, value]: indexToPersist)
        indexFile << key << " " << value << std::endl;

    indexFile.close();
}

/**
 * @brief DictionaryIndex::DictionaryIndex
 * Load an index file belonging to the file specified as path.
 * If the index does not exist, it is first created.
 * @param path
 * The path for the text file that he index belongs to.
 */
DictionaryIndex::DictionaryIndex(const std::string& path): indexPath{path + ".idx"} {
    if (!std::filesystem::exists(indexPath)){
        LOG("Index for {} does not exist. Trying to create it.", path);

        bool res = createIndex(path);
        if (!res) {
            ERROR("Could not create index for {}, exiting!", path);
            exit(1);
        }
    }
    loadIndex(indexPath);
}

/**
 * @brief DictionaryIndex::getIndex
 * Return the offset of the dictionary file where the entries starting
 * with `s` start.
 * @param s
 * The start of the text that should be looked up in the dictionary file.
 * @return
 * The offset in file. If the index can't be found, -1 is returned.
 */
long DictionaryIndex::getIndex(const std::string &s)
{
    std::string tmp {s};
    long res;
    if (s.length() > 2)
        tmp = s.substr(0, 2);

    if (index.contains(tmp))
        return index[tmp];

    DEBUG("{} can't be found in index file!", tmp);

    tmp = s.substr(0, 1);
    if (index.contains(tmp))
        return index[tmp];

    return -1;
}
