#include "basedata.h"

BaseData::BaseData(int supplementaryDataSize, int numRowInData, int numColumnInData)
{
    m_supplementaryDataSize = supplementaryDataSize;
    m_numRowInData = numRowInData;
    m_numColumnInData = numColumnInData;

    // Creating dynamic array for supplementary data.
    //
    m_supplementaryData = new std::string[m_supplementaryDataSize];

    // Creating 2d dynamic array for data.
    //
    m_data = new std::string*[m_numRowInData];
    for(int i = 0; i < m_numRowInData; ++i)
        m_data[i] = new std::string[m_numColumnInData];

}

BaseData::~BaseData()
{
    delete[] m_supplementaryData;

    for(int i = 0; i < m_numRowInData; ++i)
    {
        delete [] m_data[i];
    }
    delete [] m_data;
}

int BaseData::GetSupplementaryDataSize() const
{
    return m_supplementaryDataSize;
}

int BaseData::GetNumRowInData() const
{
    return m_numRowInData;
}

int BaseData::GetNumColumnInData() const
{
    return m_numColumnInData;
}

void BaseData::SetTimestamp(const std::string& ts)
{
    m_timestamp = ts;
}

void BaseData::SetSupplementaryData(int index, const std::string& data)
{
    m_supplementaryData[index] = data;
}

void BaseData::SetData(int row, int column, const std::string& data)
{
    m_data[row][column] = data;
}

std::string BaseData::GenerateStringToWriteToFile() const
{ 
    std::string str("");

    // Timestamp.
    //
    str = str + m_timestamp + "\n";

    // Supplementary data.
    //
    for (int i = 0; i < m_supplementaryDataSize; i++)
    {
        str = str + m_supplementaryData[i] + " ";
    }

    str = str + "\n";

    // Data.
    //
    for (int i = 0; i < m_numRowInData; i++)
    {
        for (int j = 0; j < m_numColumnInData; j++)
        {
            str = str + m_data[i][j] + " ";
        }
        str = str + "\n";
    }

    return str;
}
