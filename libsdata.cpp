#include "libsdata.h"

const std::string LIBSData::name = "LIBS";

LIBSData::LIBSData(int supplementaryDataSize, int numRowInData, int numColumnInData) : BaseData(supplementaryDataSize, numRowInData, numColumnInData)
{
}

const std::string& LIBSData::GetName() const
{
    return name;
}
