#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "jsonrpc.h"

using namespace std;

int main(int argc, char **argv)
{
    cout << "\nrpc-client v0.1\n\n";

    Json::Rpc::TcpClient tcpClient(std::string("127.0.0.1"), 8000);
    Json::Value query;
    Json::FastWriter writer;
    std::string queryStr;
    std::string responseStr;

    if(!networking::init())
    {
      std::cerr << "Networking initialization failed" << std::endl;
      exit(EXIT_FAILURE);
    }

    if(!tcpClient.Connect())
    {
      std::cerr << "Cannot connect to remote peer!" << std::endl;
      exit(EXIT_FAILURE);
    }

    // curl -d '{"id":1,method:"sum",params:[22,33]}' 127.0.0.1:8000
    Json::Value arr_value(Json::arrayValue);
    Json::Value sum1(1);
    Json::Value sum2(2);

    arr_value.append(&sum1);
    arr_value.append(&sum2);

    /* build JSON-RPC query */
    query["jsonrpc"] = "2.0";
    query["id"] = 1;
    query["method"] = "sum";
    query["params"] = arr_value;

    queryStr = writer.write(query);
    std::cout << "Query is: " << queryStr << std::endl;

    if(tcpClient.Send(queryStr) == -1)
    {
      std::cerr << "Error while sending data!" << std::endl;
      exit(EXIT_FAILURE);
    }

    /* wait the response */
    if(tcpClient.Recv(responseStr) != -1)
    {
      std::cout << "Received: " << responseStr << std::endl;
    }
    else
    {
      std::cerr << "Error while receiving data!" << std::endl;
    }

    tcpClient.Close();
    networking::cleanup();





    cout << "Exiting client\n\n";
    return 0;
}
