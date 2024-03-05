#include <gtest/gtest.h>
#include <unistd.h>
#include <loglibrary.h>
#include <dictionaryindex.h>
#include <fstream>

#include "testutils.h"

TEST(DictionaryIndexSuite, LoadIndex1){

    std::string filePath = getFilePath("simple_input_1");
    cleanUpIndexFile(filePath);

    // look up the index of two random words in
    // the newly created index
    DictionaryIndex di {filePath};
    auto indexOfCity = di.getIndex("ci");
    auto indexOfRibbon = di.getIndex("ri");

    std::fstream fs {filePath, std::ios_base::in};
    fs.seekg(indexOfCity);

    std::string line;
    std::getline(fs, line);
    EXPECT_EQ(line, "city") << "incorrect index for the word 'city'";

    fs.seekg(indexOfRibbon);
    std::getline(fs, line);
    EXPECT_EQ(line, "ribbon") << "incorrect index for the word 'ribbon'";
}

TEST(DictionaryIndexSuite, LoadUnicodeIndex1){
    std::string filePath = getFilePath("unicode_input");
    cleanUpIndexFile(filePath);

    // look up the index of two random words in
    // the newly created index
    DictionaryIndex di {filePath};
    auto indexOfZahne = di.getIndex("Zä");
    auto indexOfSpitz = di.getIndex("Sp");

    std::string line;
    std::fstream fs {filePath, std::ios_base::in};

    fs.seekg(indexOfSpitz);
    std::getline(fs, line);
    EXPECT_EQ(line, "Spitze") << "incorrect index for the word 'Spitze'";

    fs.seekg(indexOfZahne);
    std::getline(fs, line);
    EXPECT_EQ(line, "Zähnen") << "incorrect index for the word 'Zähnen'";
}

TEST(DictionaryIndexSuite, LoadIndex_Non_existing_Lookup){
    std::string filePath = getFilePath("simple_input_1");
    cleanUpIndexFile(filePath);

    DictionaryIndex di {filePath};
    auto nonExistentIndex = di.getIndex("kk");
    EXPECT_EQ(nonExistentIndex, -1) << "It found a non-existent index...";
}

TEST(DictionaryIndexSuite, QuitOnNonExistentInput){
    std::string filePath = "/tmp/hopefully_this_does_not_exist";
    EXPECT_DEATH({DictionaryIndex di{filePath};}, "");
}

TEST(DictionaryIndexSuite, ParseEmptyInput){
    std::string filePath = getFilePath("empty_input");
    cleanUpIndexFile(filePath);

    DictionaryIndex di {filePath};

    std::string indexPath = filePath + ".idx";
    struct stat indexFileInfo;
    stat(indexPath.c_str(), &indexFileInfo);
    EXPECT_EQ(indexFileInfo.st_size, 0) << "Index file generated from empty input should be also empty!";
}
