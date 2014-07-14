#ifndef LIBSDATA_H
#define LIBSDATA_H

#include "basedata.h"
class LIBSData : public BaseData
{
public:
    LIBSData(int supplementaryDataSize, int numRowInData, int numColumnInData);
    const std::string& GetName() const;

private:
    const static std::string name;

};

#endif // LIBSDATA_H
