#ifndef SUBSTRINGSEEKERTETSER_H
#define SUBSTRINGSEEKERTETSER_H


#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "multithreadsubstringseekerinfile.h"
#include "boyermooresubstringseeker.h"

class SubstringSeekerTetser
{
public:
    SubstringSeekerTetser() = default;

    void launchTest(const std::string &testFolder, const std::string &mask, const char &anyChar) const;

private:
    std::vector<FoundSubstringInObjectInfo> parseAnswer(const std::string &answerFileName) const;
};

#endif // SUBSTRINGSEEKERTETSER_H
