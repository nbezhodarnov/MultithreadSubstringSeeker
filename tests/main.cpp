#include "substringseekertetser.h"

int main(int argc, char** argv) {
    if (argc < 3 || argc > 4) {
        throw std::runtime_error("Wrong arguments count!");
    }

    char anyChar = '?';
    if (argc == 4) {
        anyChar = argv[3][0];
    }

    SubstringSeekerTetser tester;
    tester.launchTest(argv[1], argv[2], anyChar);

    return 0;
}
