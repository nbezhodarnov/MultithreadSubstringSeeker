#ifndef FOUNDSUBSTRINGINOBJECTINFO_H
#define FOUNDSUBSTRINGINOBJECTINFO_H

#include "foundsubstringinfo.h"

struct FoundSubstringInObjectInfo
{
    int lineIndex;
    FoundSubstringInfo info;

    bool operator==(const FoundSubstringInObjectInfo &other) const;
};

#endif // FOUNDSUBSTRINGINOBJECTINFO_H
