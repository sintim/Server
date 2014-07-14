#include "xrfdata.h"

const std::string XRFData::name = "XRF";

XRFData::XRFData(int supplementaryDataSize, int numRowInData, int numColumnInData) : BaseData(supplementaryDataSize, numRowInData, numColumnInData)
{

}
const std::string& XRFData::GetName() const
{
    return name;
}
