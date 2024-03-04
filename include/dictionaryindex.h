#ifndef DICTIONARYINDEX_H
#define DICTIONARYINDEX_H

#include <string>
#include <map>

class DictionaryIndex
{
private:
    std::string indexPath;
    std::map<std::string, long> index;

    void loadIndex(const std::string& indexPath);
    bool createIndex(const std::string& filePath);
    void persistIndex(const std::map<std::string, long> indexToPersist);

public:
    explicit DictionaryIndex(const std::string& path);
    long getIndex(const std::string& s);
};

#endif // DICTIONARYINDEX_H
