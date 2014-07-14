#include "metadata.h"

MetaData::MetaData()
{
    m_numOfSupplementaryData = 0;
    m_sizeYDataDefinition = 0;
    m_sizeXDataDefinition = 0;

    m_supplementaryData = 0;
    m_dataDefinition = 0;
}

MetaData::MetaData(int supplementaryDataSize, int sizeYDataDefinition, int sizeXDataDefinition)
{
    m_numOfSupplementaryData = supplementaryDataSize;
    m_sizeYDataDefinition = sizeYDataDefinition;
    m_sizeXDataDefinition = sizeXDataDefinition;

    // Creating dynamic array for definition for supplementary data.
    //
    m_supplementaryData = new DataDefinition[m_numOfSupplementaryData];

    // Creating 2d dynamic array for data definition.
    //
    m_dataDefinition = new DataDefinition*[m_sizeYDataDefinition];
    for(int i = 0; i < m_sizeYDataDefinition; ++i)
        m_dataDefinition[i] = new DataDefinition[m_sizeXDataDefinition];
}

MetaData::~MetaData()
{
    delete[] m_supplementaryData;

    for(int i = 0; i < m_sizeYDataDefinition; ++i)
    {
        delete [] m_dataDefinition[i];
    }
    delete [] m_dataDefinition;
}


// ********************* Setters ***************************
//
void MetaData::SetVersion(const std::string& version)
{
    m_version = version;
}

void MetaData::SetSensorInfo(const std::string& sensorInfo)
{
    m_sensorInfo = sensorInfo;
}

void MetaData::SetNumOfSupplementaryData(int num)
{
   m_numOfSupplementaryData = num;
}

void MetaData::SetSizeXDataDefinition(int num)
{
    m_sizeXDataDefinition = num;
}

void MetaData::SetSizeYDataDefinition(int num)
{
    m_sizeYDataDefinition = num;
}

void MetaData::SetSupplementaryDataDefinition(int index, const DataDefinition& definition)
{
    if (index < m_numOfSupplementaryData)
        m_supplementaryData[index] = definition;
    else return;
}

void MetaData::SetDataDefinition(int row, int column, const DataDefinition& definition)
{
    if (row < m_sizeYDataDefinition && column < m_sizeXDataDefinition)
        m_dataDefinition[row][column] = definition;
    else return;
}


// ************************** Getters ****************************************
//
const std::string& MetaData::GetVersion() const
{
    return m_version;
}

const std::string& MetaData::GetSensorInfo() const
{
    return m_sensorInfo;
}

const int MetaData::GetNumOfSupplementaryData() const
{
    return m_numOfSupplementaryData;
}

const int MetaData::GetSizeXDataDefinition() const
{
    return m_sizeXDataDefinition;
}

const int MetaData::GetSizeYDataDefinition() const
{
    return m_sizeYDataDefinition;
}

const DataDefinition& MetaData::GetSupplementaryDataDefinition(int index) const
{
   if (index < m_numOfSupplementaryData)
    return m_supplementaryData[index];
   // Todo what to return;
}

const DataDefinition& MetaData::GetDataDefinition(int row, int column) const
{
    if (row < m_sizeYDataDefinition && column <= m_sizeXDataDefinition)
        return m_dataDefinition[row][column];
    // Todo what to return;
}
