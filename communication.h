#ifndef COMMUNICTAION_H
#define COMMUNICTAION_H
#include <iostream>

#define PORT 7777

using namespace std;




class Communication
{
public:
    Communication();
    ~Communication();
    void run();
    void send();
    void receive();
    bool init();
    static void waitForMessages(int socket);
    bool reconfigureServer(int port = PORT);

private:
    int m_theSocket;
    string m_theIP;
    int m_thePort;


    //Data m_theData;
    //Controller m_theController();

};

#endif // COMMUNICATION_H
