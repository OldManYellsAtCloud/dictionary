#include <gtest/gtest.h>
#include "utils.h"

TEST(MiscSuite, GetNextToken_BaseTest){
    std::string basicText = "aaa-bbb-ccc-ddd";
    size_t curPos = 0;

    std::string res = getNextToken(basicText, "-", curPos);
    EXPECT_EQ(res, "aaa");

    res = getNextToken(basicText, "-", curPos);
    EXPECT_EQ(res, "bbb");

    res = getNextToken(basicText, "-", curPos);
    EXPECT_EQ(res, "ccc");

    res = getNextToken(basicText, "-", curPos);
    EXPECT_EQ(res, "ddd");

    res = getNextToken(basicText, "-", curPos);
    EXPECT_EQ(res, "");

    EXPECT_EQ(curPos, basicText.length());
}

TEST(MiscSuite, GetNextToken_EmptyString){
    std::string emptyText = "";
    size_t curPos = 0;

    std::string res = getNextToken(emptyText, "-", curPos);
    EXPECT_EQ(res, "");
    EXPECT_EQ(curPos, res.length());
}

TEST(MiscSuite, GetNextToken_DuplicatedDelimited){
    std::string text = "aaa\t\tbbb\t\tccc";
    size_t curPos = 0;
    std::string res = getNextToken(text, "\t", curPos);
    EXPECT_EQ(res, "aaa");

    res = getNextToken(text, "\t", curPos);
    EXPECT_EQ(res, "");

    res = getNextToken(text, "\t", curPos);
    EXPECT_EQ(res, "bbb");

    res = getNextToken(text, "\t", curPos);
    EXPECT_EQ(res, "");

    res = getNextToken(text, "\t", curPos);
    EXPECT_EQ(res, "ccc");

    EXPECT_EQ(curPos, text.length());
}

TEST(MiscSuite, GetNextToken_DelimiterAtEnd){
    std::string text = "aaa!bbb!";
    size_t curPos = 0;

    std::string res = getNextToken(text, "!", curPos);
    EXPECT_EQ(res, "aaa");

    res = getNextToken(text, "!", curPos);
    EXPECT_EQ(res, "bbb");

    EXPECT_EQ(curPos, text.length());
}

TEST(MiscSuite, GetNextToken_NoDelimiter){
    std::string text = "aaa";
    size_t curPos = 0;

    std::string res = getNextToken(text, "-", curPos);
    EXPECT_EQ(res, "aaa");
    EXPECT_EQ(curPos, text.length());
}

TEST(MiscSuite, GetNextToken_OnlyDelimiter){
    std::string text = "---";
    size_t curPos = 0;

    std::string res = getNextToken(text, "-", curPos);
    EXPECT_EQ(res, "");
    EXPECT_EQ(curPos, 1);

    res = getNextToken(text, "-", curPos);
    EXPECT_EQ(res, "");
    EXPECT_EQ(curPos, 2);

    res = getNextToken(text, "-", curPos);
    EXPECT_EQ(res, "");
    EXPECT_EQ(curPos, text.length());
}

TEST(MiscSuite, ParseEntryType_NAN){
    std::string s = "";
    DictionaryEntry::EntryType et = parseEntryType(s);
    EXPECT_EQ(et, DictionaryEntry::EntryType::NAN);

    s = "NON_EXISTENT";
    EXPECT_EQ(et, DictionaryEntry::EntryType::NAN);
}

TEST(MiscSuite, ParseEntryType_ADJ){
    std::string s = "adj";
    DictionaryEntry::EntryType et = parseEntryType(s);
    EXPECT_EQ(et, DictionaryEntry::EntryType::ADJECTIVE);

    s = "adj_xxx";
    et = parseEntryType(s);
    EXPECT_EQ(et, DictionaryEntry::EntryType::NAN);
}

TEST(MiscSuite, ParseEntryType_ADV){
    std::string s = "adv";
    DictionaryEntry::EntryType et = parseEntryType(s);
    EXPECT_EQ(et, DictionaryEntry::EntryType::ADVERB);

    s = "adv_xxx";
    et = parseEntryType(s);
    EXPECT_EQ(et, DictionaryEntry::EntryType::NAN);
}

TEST(MiscSuite, ParseEntryType_NOUN){
    std::string s = "noun";
    DictionaryEntry::EntryType et = parseEntryType(s);
    EXPECT_EQ(et, DictionaryEntry::EntryType::NOUN);

    s = "noun_xxx";
    et = parseEntryType(s);
    EXPECT_EQ(et, DictionaryEntry::EntryType::NAN);
}

TEST(MiscSuite, ParseEntryType_VERB){
    std::string s = "verb";
    DictionaryEntry::EntryType et = parseEntryType(s);
    EXPECT_EQ(et, DictionaryEntry::EntryType::VERB);

    s = "verb_xxx";
    et = parseEntryType(s);
    EXPECT_EQ(et, DictionaryEntry::EntryType::NAN);
}

TEST(MiscSuite, ToLower){
    std::string s = "AAAA";
    s = toLowerCase(s);
    EXPECT_EQ(s, "aaaa");

    s = "!!!!aaa";
    s = toLowerCase(s);
    EXPECT_EQ(s, "!!!!aaa");

    s = "ÁÁ";
    s = toLowerCase(s);
    EXPECT_EQ(s, "áá");
}
