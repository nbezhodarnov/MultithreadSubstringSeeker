#include "foundsubstringinfo.h"

bool FoundSubstringInfo::operator==(const FoundSubstringInfo &other) const
{
    return startCharIndex == other.startCharIndex && substring == other.substring;
}
