#ifndef METADATAMAKER_H
#define METADATAMAKER_H

#include <string>

class MetaData;

// Hiding the coupling between reading metadata files and generating metadata objects.
//
class MetaDataMaker
{
public:
    static MetaData* MakeMetaData(char* fileName);
private:
    MetaDataMaker();
};

#endif // METADATAMAKER_H
