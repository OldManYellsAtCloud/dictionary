#ifndef ENTRY_H
#define ENTRY_H

#include <string>
#include <map>


enum class EntryType {
    NAN,
    NOUN,
    VERB,
    ADJECTIVE,
    ADVERB
};

static std::map<std::string, EntryType> entryTypeLookupTable {
    {"", EntryType::NAN},
    {"adj", EntryType::ADJECTIVE},
    {"adv", EntryType::ADVERB},
    {"noun", EntryType::NOUN},
    {"verb", EntryType::VERB}
};

struct Entry {
    std::string original;
    std::string translation;
    EntryType entryType;
    std::string niche;
};

Entry parseEntry(std::string);

#endif // ENTRY_H
