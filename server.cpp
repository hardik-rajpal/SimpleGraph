
#include"Graph.h"
#include <winsock2.h>
#include <stdio.h>
#include<string>
using namespace std;
ServerSocket::ServerSocket(int port, string addr){
    Port = port;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
    {
        // The WSAGetLastError() function is one of the only functions
        // in the Winsock 2.2 DLL that can be called in the case of a WSAStartup failure
        printf("Server: WSAStartup failed with error %ld.\n", WSAGetLastError());
        // Exit with error
        // return 1;
    }
    else
    {
        printf("Server: The Winsock DLL found!\n");
        printf("Server: The current status is %s.\n", wsaData.szSystemStatus);
    }
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2 )
    {
        //Tell the user that we could not find a usable WinSock DLL
        printf("Server: The dll do not support the Winsock version %u.%u!\n",LOBYTE(wsaData.wVersion),HIBYTE(wsaData.wVersion));
        // Do the clean up
        WSACleanup();
    }
    else
    {
        printf("Server: The dll supports the Winsock version %u.%u!\n", LOBYTE(wsaData.wVersion),HIBYTE(wsaData.wVersion));
        printf("Server: The highest version this dll can support is %u.%u\n",LOBYTE(wsaData.wHighVersion), HIBYTE(wsaData.wHighVersion));
    }
    // Create a new socket to listen for client connections.
    ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    // Check for errors to ensure that the socket is a valid socket.
    if (ListeningSocket == INVALID_SOCKET)
    {
        printf("Server: Error at socket(), error code: %ld.\n", WSAGetLastError());
        // Clean up
        WSACleanup();
    }
    else{
        printf("Server: socket() is OK!\n");
    }
    // Set up a SOCKADDR_IN structure that will tell bind that we
    // want to listen for connections on all interfaces using port 7171.
    // The IPv4 family
    ServerAddr.sin_family = AF_INET;
    // host-to-network byte order
    ServerAddr.sin_port = htons(Port);
    // Listen on all interface, host-to-network byte order
    //Change to addr later.
    ServerAddr.sin_addr.s_addr = inet_addr(addr.c_str());

    if (bind(ListeningSocket, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr))==SOCKET_ERROR)
    {
        printf("Server: bind() failed! Error code: %ld.\n", WSAGetLastError());
        // Close the socket
        closesocket(ListeningSocket);
        // Do the clean up
        WSACleanup();
    }
    else{
        printf("Server: bind() is OK!\n");
    }
}



int ServerSocket::recvTimeOutTCP(SOCKET socket, long sec, long usec)
{
    // Setup timeval variable
    struct timeval timeout;
    struct fd_set fds;
        // assign the second and microsecond variables
    timeout.tv_sec = sec;
    timeout.tv_usec = usec;
    // Setup fd_set structure
    FD_ZERO(&fds);
    FD_SET(socket, &fds);
    // Possible return values:
    // -1: error occurred
    // 0: timed out
    // > 0: data ready to be read
    return select(0, &fds, 0, 0, &timeout);
}

void ServerSocket::listenForClient(){
    while(1){
        if (listen(ListeningSocket, 5) == SOCKET_ERROR)
        {    
            printf("Server: listen(): Error listening on socket %ld.\n", WSAGetLastError());
            // Close the socket
            closesocket(ListeningSocket);
            // Do the clean up
            WSACleanup();
            // Exit with error
            return ;
        }
        else{
            printf("Server: listen() is OK, I'm listening for connections...\n");
        }

        // Set 10 seconds 10 useconds timeout
        SelectTiming = recvTimeOutTCP(ListeningSocket, 100, 100);
        switch (SelectTiming)
        {
            case 0:{
                    // Timed out, do whatever you want to handle this situation
                    printf("\nServer: Timeout lor while waiting you retard client! Retrying...\n");
                    continue;
            }
            case -1:{
            // Error occurred, more tweaking here and the recvTimeOutTCP()...
            printf("\nServer: Some error encountered with code number: %ld\n", WSAGetLastError());
            break;
            }
            default:{
                    // Accept a new connection when available. 'while' always true
                    while(1){
                        // Reset the NewConnection socket to SOCKET_ERROR
                        // Take note that the NewConnection socket in not listening
                        NewConnection = SOCKET_ERROR;
                        // While the NewConnection socket equal to SOCKET_ERROR
                        // which is always true in this case...
                        while(NewConnection == SOCKET_ERROR){
                            // Accept connection on the ListeningSocket socket and assign
                            // it to the NewConnection socket, let the ListeningSocket
                            // do the listening for more connection
                            NewConnection = accept(ListeningSocket, NULL, NULL);
                            printf("\nServer: accept() is OK...\n");
                            printf("Server: New client got connected, ready to receive and send data...\n");
                            return;
                        }
                    }
            }
        }
    }
}
string ServerSocket::awaitSignal(){
        char *resp = new char[1024];
        resp[0]='N';
        resp[1] = 'U';
        resp[2] = 'L';
        resp[3] = 'L';
        resp[4] = '\0';
        // At this point you can do two things with these sockets
        // 1. Wait for more connections by calling accept again
        //    on ListeningSocket (loop)
        // 2. Start sending or receiving data on NewConnection.
        ByteReceived = recv(NewConnection, recvbuff, sizeof(recvbuff), 0);
        // When there is data
        
        if ( ByteReceived > 0 )
        {
            printf("Server: recv() looks fine....\n");
            // Some info on the receiver side...
            getsockname(ListeningSocket, (SOCKADDR *)&ServerAddr,(int *)sizeof(ServerAddr));
            printf("Server: Receiving IP(s) used: %s\n",inet_ntoa(ServerAddr.sin_addr));
            printf("Server: Receiving port used: %d\n", htons(ServerAddr.sin_port));
            // Some info on the sender side
            // Allocate the required resources
            memset(&SenderInfo, 0, sizeof(SenderInfo));
            nlen = sizeof(SenderInfo);
            getpeername(NewConnection, (SOCKADDR *)&SenderInfo, &nlen);
            printf("Server: Sending IP used: %s\n", inet_ntoa(SenderInfo.sin_addr));
            printf("Server: Sending port used: %d\n", htons(SenderInfo.sin_port));
            // Print the received bytes. Take note that this is the total
            // byte received, it is not the size of the declared buffer
            printf("Server: Bytes received: %d\n", ByteReceived);
            // Print what those bytes represent
            printf("Server: Those bytes are: \n");
            // Print the string only, discard other
            // remaining 'rubbish' in the 1024 buffer size
            recvbuff[ByteReceived] = '\0';
            // for(i=0;i < ByteReceived;i++){
            //         printf("%c", recvbuff[i]);
            // }
            ByteReceived = 0;
            printf("\n");
            printf("Here");
            return string(recvbuff);
        }
        else if(ByteReceived == 0 ){
                printf("Server: Connection closed!\n");
                return string("EXIT");
        }
        else{
            printf("Server: recv() failed with error code: %d\n", WSAGetLastError());
            return string("EXIT");
        }
        return string(resp);
        // Clean up all the send/recv communication, get ready for new one
}
void ServerSocket::sendData(string msg){
// Some info on the receiver side...
strcpy(sendbuff,msg.c_str());
getsockname(NewConnection, (SOCKADDR *)&ServerAddr, (int *)sizeof(ServerAddr));
printf("Server: Send IP(s) used: %s\n", inet_ntoa(ServerAddr.sin_addr));
printf("Server: Receiver port used: %d\n", htons(ServerAddr.sin_port));
// Sends some data to server/receiver...
BytesSent = send(NewConnection, sendbuff, strlen(sendbuff), 0);
if(BytesSent == SOCKET_ERROR)
{
    printf("Server: send() error %ld.\n", WSAGetLastError());
}
else
{
    printf("Server: send() is OK - bytes sent: %ld\n", BytesSent);
    // Some info on this sender side...
    // Allocate the required resources
    memset(&SenderInfo, 0, sizeof(SenderInfo));
    nlen = sizeof(SenderInfo);
    getsockname(NewConnection, (SOCKADDR *)&SenderInfo, &nlen);
    printf("Server: Sender IP(s) used: %s\n", inet_ntoa(SenderInfo.sin_addr));
    printf("Server: Sender port used: %d\n", htons(SenderInfo.sin_port));
    // printf("Server: Those bytes represent: \"%s\"\n", sendbuff);
}
}



void ServerSocket::closeConnection(){
    sendbuff[0] = '\0';
    if( shutdown(NewConnection, SD_SEND) != 0){
        printf("\nServer: Well, there is something wrong with the shutdown(). The error code: %ld\n", WSAGetLastError());
    }               
    else{
        printf("\nServer: shutdown() looks OK...\n");
    }
    // Well, if there is no more connection in 15 seconds,
    // just exit this listening loop...
    if( recvTimeOutTCP(ListeningSocket, 15, 0) == 0){
        printf("\nServer: The listening socket is timeout...\n");
        return;
    }

    // When all the data communication and listening finished, close the socket
    if(closesocket(ListeningSocket) != 0){
        printf("Server: Cannot close ListeningSocket socket. Error code: %ld\n", WSAGetLastError());
    }
    else{
        printf("Server: Closing ListeningSocket socket...\n");
    }
    // Finally and optionally, clean up all those WSA setup
    if(WSACleanup() != 0){
        printf("Server: WSACleanup() failed! Error code: %ld\n", WSAGetLastError());
    }
    else{
        printf("Server: WSACleanup() is OK...\n");
    }
}


/*✅*/void ServerSocket::sendDataARP(string msg, SimpleGraph &g){
    sendData(msg);
    awaitRecParse(g);
}
/*✅*/string ServerSocket::awaitRecParse(SimpleGraph &g){
    sendData("paused");
    while(true){
        string resp = awaitSignal();
        if(resp=="EXIT"){
            closeConnection();
            cout<<"\nError fsr\n";
            return "EXIT";
        }
        if(resp.length()>20){
            g.appendRendData(resp);
        }
        else if(resp=="play"){
            return resp;
        }
        else{
            g.parseCommand(resp);
        }
    }
        
    return "OK";
}

// void SimpleGraph::syncGraph(bool pausemain){
//     cout<<"Called";
//     // #ifdef SERVERUSED
//     // cout<<SERVERUSED<<" ";
//     if(server!=NULL){
//         if(pausemain){
//             server->sendDataARP(this->serialize(), *this);
//         }
//         else{
//             server->sendData(this->serialize());
//             this->appendRendData(server->awaitSignal());
//         }
//     }
//     else{
//         cout<<"You need to call initServer(port, host) before sync!\n";
//     }
//     // #endif
// }