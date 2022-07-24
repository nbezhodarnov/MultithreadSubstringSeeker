#ifndef MULTITHREADSUBSTRINGSEEKERINFILE_H
#define MULTITHREADSUBSTRINGSEEKERINFILE_H


#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <list>

#include "substringseekerinabstractobject.h"
#include "abstractsubstringseeker.h"
#include "threadpool.h"

class MultithreadSubstringSeekerInFile : public SubstringSeekerInAbstractObject
{
public:
    MultithreadSubstringSeekerInFile(std::unique_ptr<AbstractSubstringSeeker> &&newSeeker);
    void setSeeker(std::unique_ptr<AbstractSubstringSeeker> &&newSeeker) override;
    std::vector<FoundSubstringInObjectInfo> seek(const std::string &inputFileName, const std::string &mask, const char &anyChar) const override;

private:
    std::unique_ptr<AbstractSubstringSeeker> seeker;

    std::vector<FoundSubstringInObjectInfo> seekInLine(const std::string &line, const int &lineIndex, const std::string &mask, const char &anyChar) const;
    void moveResultsFromFutureListToVector(std::list<std::future<std::vector<FoundSubstringInObjectInfo>>> &list, std::vector<FoundSubstringInObjectInfo> &vector) const;
};

#endif // MULTITHREADSUBSTRINGSEEKERINFILE_H
