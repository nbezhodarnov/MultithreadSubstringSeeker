#include "substringseekertetser.h"

#include <iostream>

void printResult(const std::vector<SearchResult> &result) {
    std::cout << result.size() << std::endl;
    for (auto searchResultItem : result) {
        std::cout << searchResultItem.lineIndex << " " << searchResultItem.startCharIndex << " " << searchResultItem.substring << std::endl;
    }
}

void SubstringSeekerTetser::launchTest(const std::string &testFolder, const std::string &mask, const char &anyChar) const
{
    MultithreadSubstringSeeker seeker;
    std::vector<SearchResult> result = seeker.seek(testFolder + "/input.txt", mask, anyChar);

    std::vector<SearchResult> answer = parseAnswer(testFolder + "/answer.txt");

    if (result != answer) {
        printResult(result);
        std::cout << std::endl;
        printResult(answer);
        throw std::logic_error("Wrong answer!");
    }
}

std::vector<SearchResult> SubstringSeekerTetser::parseAnswer(const std::string &answerFileName) const
{
    std::ifstream answerFile(answerFileName);
    if (!answerFile.is_open()) {
        throw std::runtime_error("SubstringSeekerTetser: Error while opening answer file!");
    }
    
    std::string line = "";

    int foundSubstringsCount = 0;
    std::getline(answerFile, line);
    std::istringstream(line) >> foundSubstringsCount;

    std::vector<SearchResult> answer = {};
    SearchResult result = {-1, -1, ""};
    while (std::getline(answerFile, line)) {
        std::istringstream lineStream(line);
        lineStream >> result.lineIndex >> result.startCharIndex;
        int nextItemIndex = static_cast<int>(lineStream.tellg()) + 1;
        result.substring = line.substr(nextItemIndex, line.size() - nextItemIndex);
        answer.push_back(result);
    }

    return answer;
}
