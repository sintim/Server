#include <ctime>
#include <sstream>
#include <fstream>
#include "server.h"
#include "basedatamaker.h"

Server* Server::_inst = 0;

std::string intToString(int value)
{
    std::ostringstream convert;   // stream used for the conversion
    convert << value;      // insert the textual representation of 'Number'in the characters in the stream
    std::string stringVal = convert.str(); // set 'Result' to the contents of the stream

    if (stringVal.length() == 1)
        return "0" + stringVal;
    else
        return stringVal;
}

const std::string GenerateTimeStamp()
{
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );

    std::string ts = intToString(now->tm_year + 1900) +
            intToString(now->tm_mon + 1) +
            intToString(now->tm_mday) +
            intToString(now->tm_hour) +
            intToString(now->tm_min) +
            intToString(now->tm_sec) ;

    return ts;
}


Server* Server::GetServerInst()
{
   if (Server::_inst == 0)
       Server::_inst == new Server();

   return Server::_inst;
}


Server::Server(QObject* parent): QObject(parent)
{
  connect(&server, SIGNAL(newConnection()),
    this, SLOT(acceptConnection()));

  printf ("%s\n", "Waiting for connection...");
  server.listen(QHostAddress::Any, 8888);

}

Server::~Server()
{
  server.close();
}

void Server::acceptConnection()
{
  client = server.nextPendingConnection();

  connect(client, SIGNAL(readyRead()),
          this, SLOT(read()));

  printf ("%s\n", "A client is connected.");
}

void Server::read()
{
  // 1024 bytes should be big enough.
  //
  const int bufSize = 1024;
  char buffer[bufSize] = {0};

  client->read(buffer, client->bytesAvailable());

  // Make object based on buffer received.
  //
  BaseData* bd = BaseDataMaker::MakeData(buffer);

  std::string strToWrite("");

  // Generate string to write to file.
  //
  if (!BaseDataMaker::GenerateStringForWriting(bd, strToWrite))
  {
      printf("%s\n", "Failed to generate string to write to file.");
      delete bd;
      return;
  }

  // Write to file.
  //
  std::ofstream myfile (".\\sensorData.txt", std::ios_base::app);

  if (myfile.is_open())
  {
    myfile << strToWrite;
    myfile.close();
  }

  else printf ("%s\n", "Unable to open sensorData.txt.");

  //printf ("%s\n", strToWrite.c_str());
  delete bd;
}
