#ifndef XRFDATA_H
#define XRFDATA_H

#include "basedata.h"

class XRFData : public BaseData
{
public:
    XRFData(int supplementaryDataSize, int numRowInData, int numColumnInData);

    const std::string& GetName() const;

private:
    const static std::string name;
};

#endif // XRFDATA_H
