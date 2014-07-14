#include <stdio.h>
#include <iostream>
#include "metadatareader.h"

MetaDataReader::MetaDataReader()
{
}

MetaDataReader::MetaDataReader(char* fileName)
{
    m_metaDataFile.open(fileName);
}

MetaDataReader::~MetaDataReader()
{
    if (m_metaDataFile.is_open())
        m_metaDataFile.close();
}

bool MetaDataReader::CanFileBeOpened()
{
    return m_metaDataFile.is_open();
}

std::string MetaDataReader::GetVersionLine()
{
    m_metaDataFile.clear();
    m_metaDataFile.seekg(0, m_metaDataFile.beg);

    std::string line;
    getline(m_metaDataFile, line);

    return line;
}

std::string MetaDataReader::GetInfoLine()
{
    m_metaDataFile.clear();
    m_metaDataFile.seekg(0, m_metaDataFile.beg);

    std::string line;
    getline(m_metaDataFile, line);
    getline(m_metaDataFile, line);

    return line;
}

std::string MetaDataReader::GetSupplementaryDefinition()
{
    m_metaDataFile.clear();
    m_metaDataFile.seekg(0, m_metaDataFile.beg);

    std::string line;
    getline(m_metaDataFile, line);
    getline(m_metaDataFile, line);
    getline(m_metaDataFile, line);

    return line;
}

std::vector<std::string> MetaDataReader::GetDefinition()
{
    m_metaDataFile.clear();
    m_metaDataFile.seekg(0, m_metaDataFile.beg);

    std::string line;
    getline(m_metaDataFile, line);
    getline(m_metaDataFile, line);
    getline(m_metaDataFile, line);

    std::vector<std::string> vectorOfLines;

    while (getline(m_metaDataFile, line))
    {
        vectorOfLines.push_back(line);
    }

    return vectorOfLines;
}
