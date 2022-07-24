#include "multithreadsubstringseeker.h"

const int START = 1;

bool SearchResult::operator==(const SearchResult &other) const
{
    return lineIndex == other.lineIndex && startCharIndex == other.startCharIndex && substring == other.substring;
}

std::vector<SearchResult> MultithreadSubstringSeeker::seek(const std::string &inputFileName, const std::string &mask, const char &anyChar) const
{
    std::ifstream file(inputFileName);
    
    if (!file.is_open()) {
        throw std::runtime_error("MultithreadSubstringSeeker: Error while opening file!");
    }
    
    std::list<std::future<std::vector<SearchResult>>> resultsList;
    std::vector<SearchResult> result = {};
    std::string line = "";
    int i = START;
    ThreadPool pool;
    while (std::getline(file, line)) {
        resultsList.push_back(pool.addTask(std::bind(&MultithreadSubstringSeeker::seekInLine, this, line, mask, i, anyChar)));
        i++;
        
        if ((i - 1) % 100 == 0) {
            while(!resultsList.empty()) {
                std::vector<SearchResult> resultInLine = resultsList.front().get();
                result.insert(result.end(), resultInLine.begin(), resultInLine.end());
                resultsList.erase(resultsList.begin());
            }
        }
    }
    
    while(!resultsList.empty()) {
        std::vector<SearchResult> resultInLine = resultsList.front().get();
        result.insert(result.end(), resultInLine.begin(), resultInLine.end());
        resultsList.erase(resultsList.begin());
    }
    
    return result;
}

std::vector<int> MultithreadSubstringSeeker::makePrefix(const std::string &string) const
{
    std::vector<int> prefix(string.length());

    int j = 0;
    prefix[0] = 0;
    for (int i = 1; i < string.length(); ++i) {
        while (j > 0 && string[j] != string[i]) {
            j = prefix[j - 1];
        }
        if (string[j] == string[i]) {
            j++;
        }
        prefix[i] = j;
    }
    
    return prefix;
}

std::unordered_map<int, int> MultithreadSubstringSeeker::makeSufficsTable(const std::string &string) const
{
    std::unordered_map<int, int> sufficsTable;

    std::string reversedString(string.rbegin(), string.rend());
    std::vector<int> stringPrefix = makePrefix(string), reversedStringPrefix = makePrefix(reversedString);
    for (int i = 0; i < string.length() + 1; i++) {
        sufficsTable[i] = string.length() - stringPrefix.back();
    }

    for (int i = 1; i < string.length(); i++) {
        int j = reversedStringPrefix[i];
        sufficsTable[j] = std::min(sufficsTable[j], i - reversedStringPrefix[i] + 1);
    }
    
    return sufficsTable;
}

std::vector<SearchResult> MultithreadSubstringSeeker::seekInLine(const std::string &line, const std::string &mask, const int &lineIndex, const char &anyChar) const
{
    if (line.size() < mask.size() || mask.empty()) {
        return {};
    }
    
    std::unordered_map<char, int> stopTable = {};
    for (int i = 0; i < mask.size(); i++) {
        if (mask[i] != anyChar) {
            stopTable[mask[i]] = i;
        }
    }
    
    std::unordered_map<int, int> sufficsTable = makeSufficsTable(mask);
    
    int charsCountFromEndToLastAnyChar = 0;
    while (charsCountFromEndToLastAnyChar < mask.size() && mask[mask.size() - 1 - charsCountFromEndToLastAnyChar] != anyChar) {
        charsCountFromEndToLastAnyChar++;
    }

    std::vector<SearchResult> result = {};
    for (int shift = 0; shift <= line.size() - mask.size();) {
        int maskIndex = mask.size() - 1;
        
        bool stringFound = false;
        while(mask[maskIndex] == line[maskIndex + shift] || mask[maskIndex] == anyChar) {
            if (maskIndex <= 0) {
                result.push_back({lineIndex, shift + START, line.substr(shift, mask.size())});
                stringFound = true;
                break;
            }
            maskIndex--;
        }
        
        if (stringFound) {
            shift += mask.size();
            continue;
        }
        
        if (maskIndex == mask.size() - 1) {
            auto stopSymbol = stopTable.find(line[maskIndex + shift]);
            int stopSymbolAddValue = stopSymbol != stopTable.end() ? mask.size() - 1 - stopSymbol->second : charsCountFromEndToLastAnyChar;
            shift += stopSymbolAddValue;
        } else {
            shift += sufficsTable[mask.length() - maskIndex - 1];
        }
    }
    
    return result;
}
