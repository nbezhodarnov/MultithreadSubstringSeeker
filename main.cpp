#include <iostream>

#include "multithreadsubstringseekerinfile.h"
#include "boyermooresubstringseeker.h"

int main(int argc, char** argv) {
    if (argc < 3 || argc > 4) {
        throw std::runtime_error("Wrong arguments count!");
    }

    char anyChar = '?';
    if (argc == 4) {
        anyChar = argv[3][0];
    }

    std::unique_ptr<SubstringSeekerInAbstractObject> seekerInObject(new MultithreadSubstringSeekerInFile(std::unique_ptr<AbstractSubstringSeeker>(new BoyerMooreSubstringSeeker())));
    std::vector<FoundSubstringInObjectInfo> result = seekerInObject->seek(argv[1], argv[2], anyChar);
    
    std::cout << result.size() << std::endl;
    for (const auto &searchResultItem : result) {
        std::cout << searchResultItem.lineIndex << " " << searchResultItem.info.startCharIndex << " " << searchResultItem.info.substring << std::endl;
    }

    return 0;
}
