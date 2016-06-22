#include "communication.h"
#include <iostream>
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include <unistd.h>
#include <fstream>
#include <thread>

using namespace std;

#define ZUPA true
#define MESSAGE_LENGTH 2000

Communication::Communication()
    :m_theSocket(0)
    ,m_theIP("")
    ,m_thePort(PORT)
{
    cout<<"CTOR Communication"<<endl;
}
Communication::~Communication()
{
    cout<<"DTOR Communication"<<endl;
}

void Communication::run()
{
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    int c = sizeof(struct sockaddr_in);
    struct sockaddr_in client;
    while(1)
    {
        cout << "awaiting connection" << endl;
        //accept connection from an incoming client
        int client_sock = accept(m_theSocket, (struct sockaddr *)&client, (socklen_t*)&c);
        if (client_sock < 0)
        {
            perror("accept failed");
            return;
        }
        puts("Connection accepted");
        thread currenThread(waitForMessages, client_sock);
        currenThread.detach();
        cout << "done accepting" << endl;
    }
}


void Communication::send()
{
    cout<<"init Communication"<<endl;


}


void Communication::receive()
{
    cout<<"receive Communication"<<endl;
}


bool Communication::init()
{

    int socket_desc;
    struct sockaddr_in server;

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
        return false;
    }
    puts("Socket created");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( m_thePort );

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return false;
    }
    puts("bind done");

    //Listen
    listen(socket_desc , 3);

    m_theSocket = socket_desc;
    return ZUPA;
}

void Communication::waitForMessages(int client_sock)
{
    cout << "thread created" << endl;
    char client_message[MESSAGE_LENGTH];

    while( (recv(client_sock , client_message , MESSAGE_LENGTH , 0)) > 0 )
    {
        cout << (client_message) << endl;
        write(client_sock , "recieved" , 8);
    }
}


bool Communication::reconfigureServer(int port)
{
    m_thePort=port;
    return init();
}
