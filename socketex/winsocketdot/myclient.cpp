#include <winsock2.h>
#include<string>
using namespace std;
#include <stdio.h>
class ClientSocket{
    public:
    WSADATA              wsaData;
    SOCKET               SendingSocket;
    // Server/receiver address
    SOCKADDR_IN          ServerAddr, ThisSenderInfo;
    // Server/receiver port to connect to
    unsigned int         Port = 7171;
    int  RetCode;
    // Be careful with the array bound, provide some checking mechanism...
    char sendbuf[1024] = "This is a test string from sender", recvbuff[1024];
    int BytesSent, ByteReceived, nlen;
    ClientSocket(int port, string addr){
        Port = port;
        WSAStartup(MAKEWORD(2,2), &wsaData);
        printf("Client: Winsock DLL status is %s.\n", wsaData.szSystemStatus);
        // Create a new socket to make a client connection.
        // AF_INET = 2, The Internet Protocol version 4 (IPv4) address family, TCP protocol

        SendingSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if(SendingSocket == INVALID_SOCKET)
        {
            printf("Client: socket() failed! Error code: %ld\n", WSAGetLastError());
            // Do the clean up
            WSACleanup();
        }
        else
        {
            printf("Client: socket() is OK!\n"); 
        }
        // Set up a SOCKADDR_IN structure that will be used to connect
        // to a listening server on port 5150. For demonstration
        // purposes, let's assume our server's IP address is 127.0.0.1 or localhost
        // IPv4
        ServerAddr.sin_family = AF_INET;
        // Port no.
        ServerAddr.sin_port = htons(Port);
        // The IP address
        ServerAddr.sin_addr.s_addr = inet_addr(addr.c_str());
        // Make a connection to the server with socket SendingSocket.
        RetCode = connect(SendingSocket, (SOCKADDR *) &ServerAddr, sizeof(ServerAddr));

        if(RetCode != 0)
        {
            printf("Client: connect() failed! Error code: %ld\n", WSAGetLastError());
            // Close the socket
            closesocket(SendingSocket);
            // Do the clean up
            WSACleanup();
        }
        else
        {
            printf("Client: connect() is OK, got connected...\n");
            printf("Client: Ready for sending and/or receiving data...\n");
        }
    }
    void sendData(string msg){
        // Some info on the receiver side...
        getsockname(SendingSocket, (SOCKADDR *)&ServerAddr, (int *)sizeof(ServerAddr));
        printf("Client: Receiver IP(s) used: %s\n", inet_ntoa(ServerAddr.sin_addr));
        printf("Client: Receiver port used: %d\n", htons(ServerAddr.sin_port));
        // Sends some data to server/receiver...
        strcpy(sendbuf, msg.c_str());
        BytesSent = send(SendingSocket, sendbuf, strlen(sendbuf), 0);
        if(BytesSent == SOCKET_ERROR)
        {
            printf("Client: send() error %ld.\n", WSAGetLastError());
        }
        else
        {
          printf("Client: send() is OK - bytes sent: %ld\n", BytesSent);
          // Some info on this sender side...
          // Allocate the required resources
          memset(&ThisSenderInfo, 0, sizeof(ThisSenderInfo));
          nlen = sizeof(ThisSenderInfo);
          getsockname(SendingSocket, (SOCKADDR *)&ThisSenderInfo, &nlen);
          printf("Client: Sender IP(s) used: %s\n", inet_ntoa(ThisSenderInfo.sin_addr));
          printf("Client: Sender port used: %d\n", htons(ThisSenderInfo.sin_port));
          printf("Client: Those bytes represent: \"%s\"\n", sendbuf);
        }
    }



         string awaitSignal(){
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
               ByteReceived = recv(SendingSocket, recvbuff, sizeof(recvbuff), 0);
               // When there is data
               
               if ( ByteReceived > 0 )
               {
                    printf("Server: recv() looks fine....\n");
                    // Some info on the receiver side...
                    getsockname(SendingSocket, (SOCKADDR *)&ServerAddr,(int *)sizeof(ServerAddr));
                    printf("Server: Receiving IP(s) used: %s\n",inet_ntoa(ServerAddr.sin_addr));
                    printf("Server: Receiving port used: %d\n", htons(ServerAddr.sin_port));
                    // Some info on the sender side
                    // Allocate the required resources
                    memset(&ThisSenderInfo, 0, sizeof(ThisSenderInfo));
                    nlen = sizeof(ThisSenderInfo);
                    getpeername(SendingSocket, (SOCKADDR *)&ThisSenderInfo, &nlen);
                    printf("Server: Sending IP used: %s\n", inet_ntoa(ThisSenderInfo.sin_addr));
                    printf("Server: Sending port used: %d\n", htons(ThisSenderInfo.sin_port));
                    // Print the received bytes. Take note that this is the total
                    // byte received, it is not the size of the declared buffer
                    printf("Server: Bytes received: %d\n", ByteReceived);
                    // Print what those bytes represent
                    printf("Server: Those bytes are: \n");
                    // Print the string only, discard other
                    // remaining 'rubbish' in the 1024 buffer size
                    recvbuff[ByteReceived] = '\0';
                    for(int i=0;i<ByteReceived;i++){
                         printf("%c", recvbuff[i]);
                    }
                    ByteReceived = 0;
                    printf("\n");
                    return string(recvbuff);
               }
               else if ( ByteReceived == 0 ){
                         printf("Server: Connection closed!\n");
                         // continue;
               }
               else{
                    printf("Server: recv() failed with error code: %d\n", WSAGetLastError());
               }
               return string(resp);
               // Clean up all the send/recv communication, get ready for new one
     }
    void shutDown(){
        if( shutdown(SendingSocket, SD_SEND) != 0)
        {
            printf("Client: Well, there is something wrong with the shutdown(). The error code: %ld\n", WSAGetLastError());
        }
        else
        {
            printf("Client: shutdown() looks OK...\n");
        }
        // When you are finished sending and receiving data on socket SendingSocket,
        // you should close the socket using the closesocket API. We will
        // describe socket closure later in the chapter.
        if(closesocket(SendingSocket) != 0){
            printf("Client: Cannot close \"SendingSocket\" socket. Error code: %ld\n", WSAGetLastError());
        }
        else{
            printf("Client: Closing \"SendingSocket\" socket...\n");
        }
        // When your application is finished handling the connection, call WSACleanup.
        if(WSACleanup() != 0){
            printf("Client: WSACleanup() failed!...\n");
        }
        else
        {
            printf("Client: WSACleanup() is OK...\n");
        }
        return ;
        }
};
 

int main(int argc, char **argv)
{   string host = "127.0.0.1";
    char a[2] = "1";
    ClientSocket c = ClientSocket(7171, host);
    string msg = "Hi!";
    while(1)
    {    string resp = c.awaitSignal();
    }
    c.shutDown();
}