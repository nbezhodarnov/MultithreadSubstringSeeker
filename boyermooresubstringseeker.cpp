#include "boyermooresubstringseeker.h"

std::vector<FoundSubstringInfo> BoyerMooreSubstringSeeker::seek(const std::string &string, const std::string &mask, const char &anyChar) const
{
    if (string.size() < mask.size() || mask.empty()) {
        return {};
    }

    std::unordered_map<char, int> stopTable = makeStopTable(string, mask, anyChar);
    std::unordered_map<int, int> sufficsTable = makeSufficsTable(mask);
    int charsCountFromEndToLastAnyChar = calculateCharsCountFromEndToLastAnyChar(mask, anyChar);
    std::vector<FoundSubstringInfo> result = {};

    for (int shift = 0; shift <= string.size() - mask.size();) {
        int maskIndex = mask.size() - 1;

        bool stringFound = false;
        while(mask[maskIndex] == string[maskIndex + shift] || mask[maskIndex] == anyChar) {
            if (maskIndex <= 0) {
                result.push_back({shift + START, string.substr(shift, mask.size())});
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
            auto stopSymbol = stopTable.find(string[maskIndex + shift]);
            int stopSymbolAddValue = stopSymbol != stopTable.end() ? mask.size() - 1 - stopSymbol->second : charsCountFromEndToLastAnyChar;
            shift += stopSymbolAddValue;
        } else {
            shift += sufficsTable[mask.length() - maskIndex - 1];
        }
    }

    return result;
}

std::vector<int> BoyerMooreSubstringSeeker::makePrefix(const std::string &string) const
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

std::unordered_map<char, int> BoyerMooreSubstringSeeker::makeStopTable(const std::string &string, const std::string &mask, const char &anyChar) const
{
    std::unordered_map<char, int> stopTable = {};
    for (int i = 0; i < mask.size(); i++) {
        if (mask[i] != anyChar) {
            stopTable[mask[i]] = i;
        }
    }

    return stopTable;
}

std::unordered_map<int, int> BoyerMooreSubstringSeeker::makeSufficsTable(const std::string &string) const
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

int BoyerMooreSubstringSeeker::calculateCharsCountFromEndToLastAnyChar(const std::string &mask, const char &anyChar) const
{
    int charsCountFromEndToLastAnyChar = 0;
    while (charsCountFromEndToLastAnyChar < mask.size() && mask[mask.size() - 1 - charsCountFromEndToLastAnyChar] != anyChar) {
        charsCountFromEndToLastAnyChar++;
    }

    return charsCountFromEndToLastAnyChar;
}
