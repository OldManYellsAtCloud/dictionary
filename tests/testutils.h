#ifndef TESTUTILS_H
#define TESTUTILS_H

#include <string>
#include <unistd.h>


std::string getFilePath(std::string fileName);
void cleanUpIndexFile(std::string fileName);

#endif // TESTUTILS_H
