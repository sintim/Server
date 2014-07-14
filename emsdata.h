#ifndef EMSDATA_H
#define EMSDATA_H

#include "basedata.h"

class EMSData : public BaseData
{
public:
    EMSData(int supplementaryDataSize, int numRowInData, int numColumnIn);
    const std::string& GetName() const;

private:
    const static std::string name;

};

#endif // EMSDATA_H
