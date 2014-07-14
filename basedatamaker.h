#ifndef BASEDATAMAKER_H
#define BASEDATAMAKER_H

#include "metadatamaker.h"

class BaseData;
class MetaData;

// Responsible for hiding the coupling between metadata and the actual data during the object creation process.
//
class BaseDataMaker
{
public:    
    // Given a buffer from the socket, create a data object.
    //
    static BaseData* MakeData(char* buffer);

    // Generate string to write to file based on the data object.
    //
    static bool GenerateStringForWriting(BaseData* bd, std::string& resultingString);
private:
    BaseDataMaker();
    enum SensorType { Invalid=-1, XRF, EMS, LIBS};

    static MetaData* XRFMetaData;
    static MetaData* EMSMetaData;
    static MetaData* LIBSMetaData;


};

#endif // BASEDATAMAKER_H
