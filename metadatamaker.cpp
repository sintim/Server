#include <sstream>
#include "metadatamaker.h"
#include "metadatareader.h"
#include "metadata.h"

std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

DataDefinition createDataDefinition(const std::string &s)
{
    DataDefinition dd;
    std::vector<std::string> values = split(s, '_');

    if (values[0] == strDouble)
        dd.type = Double;
    else if (values[0] == strInt)
        dd.type = Integer;
    else
        dd.type = InvalidType;

    dd.unit = values[1];

    return dd;
}

MetaDataMaker::MetaDataMaker()
{
}

MetaData* MetaDataMaker::MakeMetaData(char* fileName)
{
    MetaDataReader reader(fileName);

    MetaData* md = 0;

    if (reader.CanFileBeOpened())
    {
        // Get the supplementary data definition row.
        //
        std::string supDataDefinition = reader.GetSupplementaryDefinition();
        std::vector<std::string> individualSupDataDefinition = split(supDataDefinition, ',');

        // Get the data definition rows.
        //
        std::vector<std::string> dataDefinitions = reader.GetDefinition();
        int numColumns = split(dataDefinitions[0], ',').size();

        md = new MetaData(individualSupDataDefinition.size(), dataDefinitions.size(), numColumns);

        std::string version = reader.GetVersionLine();
        md->SetVersion(version);

        std::string info = reader.GetInfoLine();
        md->SetSensorInfo(info);

        // Generate data definition for supplementary data.
        //
        for (int i = 0; i < individualSupDataDefinition.size(); i++)
        {
            DataDefinition dd = createDataDefinition(individualSupDataDefinition[i]);
            md->SetSupplementaryDataDefinition(i, dd);
        }

        // Generate data definition for actual data.
        //
        for (int i = 0; i < dataDefinitions.size(); i++)
        {
            std::vector<std::string> individualDataDefinition = split(dataDefinitions[i], ',');

            for (int j = 0; j < individualDataDefinition.size(); j++)
            {
                DataDefinition dd = createDataDefinition(individualDataDefinition[j]);
                md->SetDataDefinition(i, j, dd);
            }
        }

    }
    return md;
}
