#ifndef BOYERMOORESUBSTRINGSEEKER_H
#define BOYERMOORESUBSTRINGSEEKER_H


#include <unordered_map>

#include "abstractsubstringseeker.h"

class BoyerMooreSubstringSeeker : public AbstractSubstringSeeker
{
public:
    BoyerMooreSubstringSeeker() = default;
    std::vector<FoundSubstringInfo> seek(const std::string &string, const std::string &mask, const char &anyChar) const;

private:
    std::vector<int> makePrefix(const std::string &string) const;
    std::unordered_map<char, int> makeStopTable(const std::string &string, const std::string &mask, const char &anyChar) const;
    std::unordered_map<int, int> makeSufficsTable(const std::string &string) const;
    int calculateCharsCountFromEndToLastAnyChar(const std::string &mask, const char &anyChar) const;
};

#endif // BOYERMOORESUBSTRINGSEEKER_H
