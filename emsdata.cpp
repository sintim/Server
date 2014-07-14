#include "emsdata.h"

const std::string EMSData::name = "EMS";

EMSData::EMSData(int supplementaryDataSize, int numRowInData, int numColumnInData) : BaseData(supplementaryDataSize, numRowInData, numColumnInData)
{
}

const std::string& EMSData::GetName() const
{
    return name;
}
