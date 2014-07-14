#ifndef METADATA_H
#define METADATA_H

#include <string>

const std::string strDouble = "double";
const std::string strInt = "int";

enum ValueType { InvalidType=-1, Double, Integer };

// Used by both supplementary data and data definitions.
//
struct DataDefinition
{
    ValueType type;
    std::string unit;
};

// MetaData class. Defining how incoming data should be interpreted.
//
class MetaData
{
public:
    MetaData(); 

    // Parameters are for initializing data definition arrays.
    MetaData(int supplementaryDataSize, int sizeYDataDefinition, int sizeXDataDefinition);
    ~MetaData();

    void SetVersion(const std::string& version);
    void SetSensorInfo(const std::string& sensorInfo);
    void SetNumOfSupplementaryData(int num);
    void SetSizeXDataDefinition(int num);
    void SetSizeYDataDefinition(int num);
    void SetSupplementaryDataDefinition(int index, const DataDefinition& definition);
    void SetDataDefinition(int row, int column, const DataDefinition& definition);

    const std::string& GetVersion() const;
    const std::string& GetSensorInfo() const;
    const int GetNumOfSupplementaryData() const;
    const int GetSizeXDataDefinition() const;
    const int GetSizeYDataDefinition() const;
    const DataDefinition& GetSupplementaryDataDefinition(int index) const;
    const DataDefinition& GetDataDefinition(int row, int column) const;

private:
    std::string m_version;
    std::string m_sensorInfo;

    int m_numOfSupplementaryData;
    int m_sizeYDataDefinition;
    int m_sizeXDataDefinition;

    // regular array.
    //
    DataDefinition* m_supplementaryData;

    // 2d array
    //
    DataDefinition** m_dataDefinition;

};

#endif // METADATA_H
