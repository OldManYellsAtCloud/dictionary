#include <gtest/gtest.h>
#include "testutils.h"
#include "dictionary.h"


TEST(DictionarySuite, LookupWord){
    std::string filePath = getFilePath("simple_input_2");
    Dictionary d{filePath};

    std::string expected1 = "Devens grew up in Essex, 45 minutes north of Boston.";
    std::string expected2 = "She attended Shore Country Day School in Beverly, Massachusetts from kindergarten through grade 9.";
    std::string expected3 = "In junior high, Devens was the captain of the boys' hockey team.";

    std::string res = d.getFirstMatchingLine("Devens");
    EXPECT_EQ(res, expected1);
    res = d.getFirstMatchingLine("She");
    EXPECT_EQ(res, expected2);
    res = d.getFirstMatchingLine("In");
    EXPECT_EQ(res, expected3);
    res = d.getFirstMatchingLine("Devens");
    EXPECT_EQ(res, expected1);
}

TEST(DictionarySuite, LookupNonexistentWord){
    std::string filePath = getFilePath("simple_input_2");
    Dictionary d{filePath};

    std::string expected = "";
    std::string res = d.getFirstMatchingLine("doesn't exist");
    EXPECT_EQ(res, expected);
}

TEST(DictionarySuite, ParseEntry){
    std::string filePath = getFilePath("de_dict_sample");
    Dictionary d{filePath};
    auto res = d.getFirstEntry("Gö");
    EXPECT_EQ(res.original, "Gödelnumerierung {f} [alt]");
    EXPECT_EQ(res.translation, "Gödel numbering [also: Goedel numbering]");
    EXPECT_EQ(res.entryType, EntryType::NOUN);
    EXPECT_EQ(res.niche, "[math.] ");
}

TEST(DictionarySuite, ParseEntry_MissingElements){
    std::string filePath = getFilePath("de_dict_sample");
    Dictionary d{filePath};
    auto res = d.getFirstEntry("jd");
    EXPECT_EQ(res.original, "jd. verdunkelt");
    EXPECT_EQ(res.translation, "sb. dims");
    EXPECT_EQ(res.entryType, EntryType::NAN);
    EXPECT_EQ(res.niche, "");
}

