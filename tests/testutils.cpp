#include "testutils.h"
#include <format>
#include <filesystem>

std::string getFilePath(std::string fileName){
    char cwd[256];
    getcwd(cwd, 256);

    std::string ret = std::format("{}/{}", cwd, fileName);
    return ret;
}

void cleanUpIndexFile(std::string fileName){
    std::string filePath = getFilePath(fileName);
    std::string indexPath = filePath + ".idx";
    std::filesystem::remove(indexPath);
}
