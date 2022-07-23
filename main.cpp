#include <iostream>

#include "multithreadsubstringseeker.h"

int main(int argc, char** argv) {
    if (argc < 3 || argc > 4) {
        throw std::runtime_error("Wrong arguments count!");
    }

    char anyChar = '?';
    if (argc == 4) {
        anyChar = argv[3][0];
    }

    MultithreadSubstringSeeker seeker;
    std::vector<SearchResult> result = seeker.seek(argv[1], argv[2], anyChar);
    
    std::cout << result.size() << std::endl;
    for (auto searchResultItem : result) {
        std::cout << searchResultItem.lineIndex << " " << searchResultItem.startCharIndex << " " << searchResultItem.substring << std::endl;
    }

    return 0;
}
