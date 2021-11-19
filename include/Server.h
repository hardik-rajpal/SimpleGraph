#ifndef SERVER_H
#define SERVER_H
#include<bits/stdc++.h>
#include <winsock2.h>
#include <stdio.h>
#include<string>
#include"../include/Graph.h"
using namespace std;
#define MAXBUF 100000
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
     bool showlogs = false;
    /*✅*/ServerSocket(int port, string addr);//constructor
    /*✅*/int recvTimeOutTCP(SOCKET socket, long sec, long usec);//receive time out
    /*✅*/void listenForClient();//wait for client to connect.
    /*✅*/string awaitSignal();//wait for client to say something
    /*✅*/void sendData(string msg);//send data to client
    /*✅*/void closeConnection();//close connection with client


    /*Graph specific functions here*/
    /*✅*/void sendDataARP(string msg, SimpleGraph &g);//send data and wait until told to 'play'
    //ARP stands for awaitReceiveParse
    /*✅*/string awaitRecParse(SimpleGraph &g);//wait indefinitely until told to 'play'

};
#endif