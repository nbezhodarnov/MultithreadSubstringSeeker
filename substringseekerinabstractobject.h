#ifndef SUBSTRINGSEEKERINABSTRACTOBJECT_H
#define SUBSTRINGSEEKERINABSTRACTOBJECT_H


#include <memory>
#include <string>
#include <vector>

#include "foundsubstringinobjectinfo.h"
#include "abstractsubstringseeker.h"

class SubstringSeekerInAbstractObject
{
public:
    SubstringSeekerInAbstractObject() = default;
    virtual void setSeeker(std::unique_ptr<AbstractSubstringSeeker> &&newSeeker) = 0;
    virtual std::vector<FoundSubstringInObjectInfo> seek(const std::string &object, const std::string &mask, const char &anyChar) const = 0;
    virtual ~SubstringSeekerInAbstractObject() = default;
};

#endif // SUBSTRINGSEEKERINABSTRACTOBJECT_H
