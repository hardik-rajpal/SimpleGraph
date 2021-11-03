#ifndef SERVER_H
#define SERVER_H
#include<bits/stdc++.h>
#include <winsock2.h>
#include <stdio.h>
#include<string>
#include"Graph.h"
using namespace std;
#define MAXBUF 1000000
class SimpleGraph;
/*✅*/class ServerSocket{
     public:
     WSADATA            wsaData;
     SOCKET             ListeningSocket, NewConnection;
     SOCKADDR_IN        ServerAddr, SenderInfo;
     int                Port;
     // Receiving part
     char          recvbuff[MAXBUF], sendbuff[MAXBUF];
     int                ByteReceived, BytesSent,i, nlen, SelectTiming;
    /*✅*/ServerSocket(int port, string addr);
    /*✅*/int recvTimeOutTCP(SOCKET socket, long sec, long usec);
    /*✅*/void listenForClient();
    /*✅*/string awaitSignal();
    /*✅*/void sendData(string msg);
    /*✅*/void closeConnection();


    /*Graph specific functions here*/
    /*✅*/void sendDataARP(string msg, SimpleGraph &g);
    /*✅*/string awaitRecParse(SimpleGraph &g);

};
#endif