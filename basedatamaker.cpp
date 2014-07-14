#include <string.h>
#include <iostream>
#include <sstream>
#include "basedatamaker.h"
#include "basedata.h"
#include "xrfdata.h"
#include "emsdata.h"
#include "libsdata.h"
#include "metadata.h"

MetaData* BaseDataMaker::XRFMetaData = 0;
MetaData* BaseDataMaker::EMSMetaData = 0;
MetaData* BaseDataMaker::LIBSMetaData = 0;

std::string ConvertIntToString(int value)
{
    std::stringstream ss;
    ss << value;
    std::string str = ss.str();
    return str;
}

std::string ConvertDoubleToString(double value)
{
    std::stringstream ss;
    ss << value;
    std::string str = ss.str();
    return str;
}

bool WriteSupplementaryData(MetaData* md, BaseData* bd, int index, char*& buffer)
{
    std::string resultingString;

    // Looking at the data definition type of the supplementary data.
    //
    if (md->GetSupplementaryDataDefinition(index).type == Double)
    {
        double ddata = 0.0;
        memcpy(&ddata, buffer, sizeof(double));
        buffer = buffer + sizeof(double);
        resultingString = ConvertDoubleToString(ddata);
    }
    else if (md->GetSupplementaryDataDefinition(index).type == Integer)
    {
        int idata = 0;
        memcpy(&idata, buffer, sizeof(int));
        buffer = buffer + sizeof(int);
        resultingString = ConvertIntToString(idata);
    }
    else
    {
        return false;
    }

    // Attach unit.
    //
    resultingString = resultingString + md->GetSupplementaryDataDefinition(index).unit;
    bd->SetSupplementaryData(index, resultingString);
    //printf("%s\n", resultingString.c_str());
    return true;
}


bool WriteData(MetaData* md, BaseData* bd, int row, int column, char*& buffer)
{
    std::string resultingString;

    // Looking at data definition.
    //
    if (md->GetDataDefinition(row, column).type == Double)
    {
        double ddata = 0.0;
        memcpy(&ddata, buffer, sizeof(double));
        buffer = buffer + sizeof(double);
        resultingString = ConvertDoubleToString(ddata);
    }
    else if (md->GetDataDefinition(row, column).type == Integer)
    {
        int idata = 0;
        memcpy(&idata, buffer, sizeof(int));
        buffer = buffer + sizeof(int);
        resultingString = ConvertIntToString(idata);
    }
    else
    {
        return false;
    }

    // Attach unit.
    //
    resultingString = resultingString + md->GetDataDefinition(row, column).unit;
    bd->SetData(row, column, resultingString);
    //printf("%s\n", resultingString.c_str());
    return true;
}


BaseDataMaker::BaseDataMaker()
{
}

BaseData* BaseDataMaker::MakeData(char* buffer)
{
    if (XRFMetaData == 0)
        XRFMetaData = MetaDataMaker::MakeMetaData(".\\XRF.txt");
    if (EMSMetaData == 0)
        EMSMetaData = MetaDataMaker::MakeMetaData(".\\EMS.txt");
    if (LIBSMetaData == 0)
        LIBSMetaData = MetaDataMaker::MakeMetaData(".\\LIBS.txt");

    // Assumption: format of timestamp is YYYYMMDDHHMMSS - length is 14.
    //
    const int timestampLen = 14;
    char ts[timestampLen + 1];
    memset(ts, 0, timestampLen + 1);
    ts[timestampLen] = '\0';
    strncpy(ts, buffer, timestampLen);
    buffer = buffer + timestampLen;

    // SensorType.
    //
    SensorType type = Invalid;
    memcpy(&type, buffer, sizeof(SensorType));
    buffer = buffer + sizeof(SensorType);

    BaseData* bd = 0;
    MetaData* currentMetaData = 0;

    // Building the correct type of object and using the correct metadata to parse.
    //
    if (type == XRF)
    {
        currentMetaData = XRFMetaData;
        bd = new XRFData(XRFMetaData->GetNumOfSupplementaryData(),
                         XRFMetaData->GetSizeYDataDefinition(),
                         XRFMetaData->GetSizeXDataDefinition());
    }

    else if (type == EMS)
    {
        currentMetaData = EMSMetaData;
        bd = new EMSData(EMSMetaData->GetNumOfSupplementaryData(),
                         EMSMetaData->GetSizeYDataDefinition(),
                         EMSMetaData->GetSizeXDataDefinition());
    }
    else if (type == LIBS)
    {
        currentMetaData = LIBSMetaData;
        bd = new LIBSData(LIBSMetaData->GetNumOfSupplementaryData(),
                         LIBSMetaData->GetSizeYDataDefinition(),
                         LIBSMetaData->GetSizeXDataDefinition());
    }
    else
    {
        printf ("Invalid sensor data received.");
        return 0;
    }

    // timestamp.
    //
    std::string tsInString(ts);
    bd->SetTimestamp(tsInString);

    std::cout << bd->GetName() + " data received.\n\n";

    // Supplementary data.
    //
    for (int i = 0; i < bd->GetSupplementaryDataSize(); i++)
    {
        bool writeSuccessful = WriteSupplementaryData(currentMetaData, bd, i, buffer);

        if (!writeSuccessful)
        {
            delete bd;
            return 0;
        }
    }

    // data.
    //
    for (int i = 0; i < bd->GetNumRowInData(); i++)
    {
        for (int j = 0; j < bd->GetNumColumnInData(); j++)
        {
            bool writeSuccessful = WriteData(currentMetaData, bd, i, j, buffer);

            if (!writeSuccessful)
            {
                delete bd;
                return 0;
            }

        }
    }

    return bd;
}

bool BaseDataMaker::GenerateStringForWriting(BaseData* bd, std::string& resultingString)
{
    // Determine type.
    //
    MetaData* currentMetaData = 0;
    if (0 != dynamic_cast<XRFData*>(bd))
        currentMetaData = XRFMetaData;
    else if (0 != dynamic_cast<EMSData*>(bd))
        currentMetaData = EMSMetaData;
    else if (0 != dynamic_cast<LIBSData*>(bd))
        currentMetaData = LIBSMetaData;
    else
        return false;

    resultingString = resultingString + bd->GetName() + "\n";
    resultingString = resultingString + currentMetaData->GetVersion() + "\n";
    resultingString = resultingString + currentMetaData->GetSensorInfo() + "\n";
    resultingString = resultingString + bd->GenerateStringToWriteToFile();

    resultingString = resultingString + "\n";

    return true;
}
