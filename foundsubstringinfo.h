#ifndef FOUNDSUBSTRINGINFO_H
#define FOUNDSUBSTRINGINFO_H


#include <string>

struct FoundSubstringInfo {
    int startCharIndex;
    std::string substring;

    bool operator==(const FoundSubstringInfo &other) const;
};


#endif // FOUNDSUBSTRINGINFO_H
