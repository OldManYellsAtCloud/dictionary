#include "testutils.h"
#include <format>
#include <filesystem>
#include <loglibrary.h>

std::string getFilePath(std::string fileName){
    char cwd[256];
    getcwd(cwd, 256);

    std::string ret = std::format("{}/{}", cwd, fileName);
    return ret;
}

void cleanUpIndexFile(std::string fileName){
    std::string indexPath = fileName + ".idx";
    std::filesystem::path pathToDelete{indexPath};
    std::error_code ec;
    if (!std::filesystem::remove(pathToDelete, ec))
        ERROR("Could not delete {}. Error code: {}, message: {}", indexPath, ec.value(), ec.message());
}
