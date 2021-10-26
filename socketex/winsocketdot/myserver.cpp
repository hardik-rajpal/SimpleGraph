#include<string>
#include"sockets.h"
using namespace std;

int main(int argc, char **argv)

{    string host = "127.0.0.1";
     ServerSocket server = ServerSocket(7171, host);
     server.listenForClient();
     string msg = "New Msg!";
     server.sendData(msg);
     Sleep(4000);
     server.closeConnection();
     return 0;

}