#include <winsock2.h>
#include <stdio.h>
#include<string>
#define MAXBUF 1024
using namespace std;
class ServerSocket{
     public:
     WSADATA            wsaData;
     SOCKET             ListeningSocket, NewConnection;
     SOCKADDR_IN        ServerAddr, SenderInfo;
     int                Port;
     // Receiving part
     char          recvbuff[MAXBUF], sendbuff[MAXBUF];
     int                ByteReceived, BytesSent,i, nlen, SelectTiming;
    ServerSocket(int port, string addr);
    int recvTimeOutTCP(SOCKET socket, long sec, long usec);
    void listenForClient();
    string awaitSignal();
    void sendData(string msg);
    void closeConnection();
};