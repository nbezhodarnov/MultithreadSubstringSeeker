#ifndef ABSTRACTSUBSTRINGSEEKER_H
#define ABSTRACTSUBSTRINGSEEKER_H


#include <string>
#include <vector>

#include "foundsubstringinfo.h"

const int START = 1;

class AbstractSubstringSeeker
{
public:
    AbstractSubstringSeeker() = default;
    virtual std::vector<FoundSubstringInfo> seek(const std::string &string, const std::string &mask, const char &anyChar) const = 0;
    virtual ~AbstractSubstringSeeker() = default;
};

#endif // ABSTRACTSUBSTRINGSEEKER_H
