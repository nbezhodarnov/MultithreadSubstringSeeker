#include "substringseekertetser.h"

#include <iostream>

void printResult(const std::vector<FoundSubstringInObjectInfo> &result) {
    std::cout << result.size() << std::endl;
    for (const auto &searchResultItem : result) {
        std::cout << searchResultItem.lineIndex << " " << searchResultItem.info.startCharIndex << " " << searchResultItem.info.substring << std::endl;
    }
}

void SubstringSeekerTetser::launchTest(const std::string &testFolder, const std::string &mask, const char &anyChar) const
{
    std::unique_ptr<SubstringSeekerInAbstractObject> seekerInObject(new MultithreadSubstringSeekerInFile(std::unique_ptr<AbstractSubstringSeeker>(new BoyerMooreSubstringSeeker())));
    std::vector<FoundSubstringInObjectInfo> result = seekerInObject->seek(testFolder + "/input.txt", mask, anyChar);

    std::vector<FoundSubstringInObjectInfo> answer = parseAnswer(testFolder + "/answer.txt");

    if (result != answer) {
        printResult(result);
        std::cout << std::endl;
        printResult(answer);
        throw std::logic_error("Wrong answer!");
    }
}

std::vector<FoundSubstringInObjectInfo> SubstringSeekerTetser::parseAnswer(const std::string &answerFileName) const
{
    std::ifstream answerFile(answerFileName);
    if (!answerFile.is_open()) {
        throw std::runtime_error("SubstringSeekerTetser: Error while opening answer file!");
    }
    
    std::string line = "";

    int foundSubstringsCount = 0;
    std::getline(answerFile, line);
    std::istringstream(line) >> foundSubstringsCount;

    std::vector<FoundSubstringInObjectInfo> answer = {};
    FoundSubstringInObjectInfo result = {-1, -1, ""};
    while (std::getline(answerFile, line)) {
        std::istringstream lineStream(line);
        lineStream >> result.lineIndex >> result.info.startCharIndex;
        int nextItemIndex = static_cast<int>(lineStream.tellg()) + 1;
        result.info.substring = line.substr(nextItemIndex, line.size() - nextItemIndex);
        answer.push_back(result);
    }

    return answer;
}
