#include "multithreadsubstringseekerinfile.h"

MultithreadSubstringSeekerInFile::MultithreadSubstringSeekerInFile(std::unique_ptr<AbstractSubstringSeeker> &&newSeeker)
{
    seeker = std::move(newSeeker);
}

void MultithreadSubstringSeekerInFile::setSeeker(std::unique_ptr<AbstractSubstringSeeker> &&newSeeker)
{
    seeker = std::move(newSeeker);
}

std::vector<FoundSubstringInObjectInfo> MultithreadSubstringSeekerInFile::seek(const std::string &inputFileName, const std::string &mask, const char &anyChar) const
{
    std::ifstream file(inputFileName);
    
    if (!file.is_open()) {
        throw std::runtime_error("MultithreadSubstringSeeker: Error while opening file!");
    }
    
    std::list<std::future<std::vector<FoundSubstringInObjectInfo>>> resultsList = {};
    std::vector<FoundSubstringInObjectInfo> result = {};
    std::string line = "";
    int i = START;
    ThreadPool pool;

    while (std::getline(file, line)) {
        resultsList.push_back(pool.addTask(std::bind(&MultithreadSubstringSeekerInFile::seekInLine, this, line, i, mask, anyChar)));
        i++;

        if ((i - 1) % 100 == 0) {
            moveResultsFromFutureListToVector(resultsList, result);
        }
    }

    moveResultsFromFutureListToVector(resultsList, result);

    return result;
}

std::vector<FoundSubstringInObjectInfo> MultithreadSubstringSeekerInFile::seekInLine(const std::string &line, const int &lineIndex, const std::string &mask, const char &anyChar) const
{
    auto resultsInLine = seeker->seek(line, mask, anyChar);
    std::vector<FoundSubstringInObjectInfo> result(resultsInLine.size());
    for (int i = 0; i < resultsInLine.size(); i++) {
        result[i] = {lineIndex, resultsInLine[i]};
    }
    return result;
}

void MultithreadSubstringSeekerInFile::moveResultsFromFutureListToVector(std::list<std::future<std::vector<FoundSubstringInObjectInfo>>> &list, std::vector<FoundSubstringInObjectInfo> &vector) const
{
    while(!list.empty()) {
        std::vector<FoundSubstringInObjectInfo> resultInLine = list.front().get();
        vector.insert(vector.end(), resultInLine.begin(), resultInLine.end());
        list.erase(list.begin());
    }
}
