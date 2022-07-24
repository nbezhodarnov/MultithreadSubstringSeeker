#include "foundsubstringinobjectinfo.h"

bool FoundSubstringInObjectInfo::operator==(const FoundSubstringInObjectInfo &other) const
{
    return lineIndex == other.lineIndex && info == other.info;
}
