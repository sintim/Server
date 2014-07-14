#ifndef METADATAREADER_H
#define METADATAREADER_H

#include <fstream>
#include <string>
#include <vector>

// Open and read metadata files.
//
class MetaDataReader
{
public:
    MetaDataReader();
    MetaDataReader(char* fileName);
    ~MetaDataReader();
    bool CanFileBeOpened();

    // Read 1 line.
    //
    std::string GetVersionLine();

    // Read 1 line.
    //
    std::string GetInfoLine();

    // Read 1 line.
    //
    std::string GetSupplementaryDefinition();

    // Read 1 or more line.
    //
    std::vector<std::string>GetDefinition();

private:
    std::ifstream m_metaDataFile;
};

#endif // METADATAREADER_H
