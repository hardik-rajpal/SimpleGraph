#include <windows.h>
#include <winsock.h>
#include<iostream>
SOCKET s;
WSADATA w;

//LISTENONPORT – Listens on a specified port for incoming connections 
//or data
int ListenOnPort(int portno)
{
    int error = WSAStartup (0x0202, &w);  // Fill in WSA info

    if (error)
    {
        return false;                     //For some reason we couldn't start Winsock
    }

    if (w.wVersion != 0x0202)             //Wrong Winsock version?
    {
        WSACleanup ();
        return false;
    }

    SOCKADDR_IN addr;                     // The address structure for a TCP socket

    addr.sin_family = AF_INET;            // Address family
    addr.sin_port = htons (portno);       // Assign port to this socket

    //Accept a connection from any IP using INADDR_ANY
    //You could pass inet_addr("0.0.0.0") instead to accomplish the 
    //same thing. If you want only to watch for a connection from a 
    //specific IP, specify that            //instead.
    addr.sin_addr.s_addr = htonl (INADDR_ANY);  

    s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); // Create socket

    if (s == INVALID_SOCKET)
    {
        return false;                     //Don't continue if we couldn't create a //socket!!
    }

    if (bind(s, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
       //We couldn't bind (this will happen if you try to bind to the same  
       //socket more than once)
        return false;
    }

    //Now we can start listening (allowing as many connections as possible to  
    //be made at the same time using SOMAXCONN). You could specify any 
    //integer value equal to or lesser than SOMAXCONN instead for custom 
    //purposes). The function will not    //return until a connection request is 
    //made
    int *a = new int;
    *a = 1;
    listen(s, SOMAXCONN);
    accept(s, (LPSOCKADDR)&addr,a);
    std::cout<<addr.sin_addr.S_un.S_addr<<" ";
    Sleep(60000);
    return 0;
    //Don't forget to clean up with CloseConnection()!
}
int main(){
    std::cout<<"Doing";
    ListenOnPort(3000);
    
    std::cout<<"Done";
}