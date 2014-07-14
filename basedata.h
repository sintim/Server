#ifndef BASEDATA_H
#define BASEDATA_H

#include <string>

// Pure virtual base class for XRF, EMS and LIBS
//
class BaseData
{
public:

    // Parameters are for initializing data arrays.
    //
    BaseData(int supplementaryDataSize, int numRowInData, int numColumnInData);
    virtual ~BaseData();

    int GetSupplementaryDataSize() const;
    int GetNumRowInData() const;
    int GetNumColumnInData() const;

    void SetTimestamp(const std::string& ts);
    void SetSupplementaryData(int index, const std::string& data);
    void SetData(int row, int column, const std::string& data);

    std::string GenerateStringToWriteToFile() const;

    // Name is different for each sensor.
    //
    virtual const std::string& GetName() const = 0;

private:
    std::string m_timestamp;

    int m_supplementaryDataSize;
    int m_numRowInData;
    int m_numColumnInData;

    // regular array
    //
    std::string* m_supplementaryData;

    // 2d array
    //
    std::string** m_data;

};

#endif // BASEDATA_H
