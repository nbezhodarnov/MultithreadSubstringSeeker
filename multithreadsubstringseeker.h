#ifndef MULTITHREADSUBSTRINGSEEKER_H
#define MULTITHREADSUBSTRINGSEEKER_H


#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "tasksqueue.h"

struct SearchResult {
    int lineIndex;
    int startCharIndex;
    std::string substring;
    
    bool operator==(const SearchResult &other) const;
};

class MultithreadSubstringSeeker
{
public:
    MultithreadSubstringSeeker() = default;
    std::vector<SearchResult> seek(const std::string &inputFileName, const std::string &mask, const char &anyChar) const;

private:
    std::vector<int> makePrefix(const std::string &string) const;
    std::unordered_map<int, int> makeSufficsTable(const std::string &string) const;
    std::vector<SearchResult> seekInLine(const std::string &line, const std::string &mask, const int &lineIndex, const char &anyChar) const;
};

#endif // MULTITHREADSUBSTRINGSEEKER_H
