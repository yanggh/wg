// client program
#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/Timestamp.h"
#include <iostream>

int testUdpClient(const char* ip, const int port)
{
    Poco::Net::SocketAddress sa(ip, port);
    Poco::Net::DatagramSocket dgs(Poco::Net::IPAddress::IPv4);
    dgs.connect(sa);

    std::string syslogMsg;
    while(1)
    {
       Poco::Timestamp now;
       syslogMsg = Poco::DateTimeFormatter::format(now, "<14>%w %f %H:%M:%S Hello,world!");
       dgs.sendBytes(syslogMsg.data(), syslogMsg.size());
    } 
    return 0;
}
 
int testDatagramSocket(const char* ip, const int port)
{
    Poco::Net::SocketAddress sa(ip, port);
    Poco::Net::DatagramSocket dgs(sa);
    char buffer[1024]; // 1K byte
    
    while(1)
    {
        Poco::Net::SocketAddress sender;
        int n = dgs.receiveFrom(buffer, sizeof(buffer)-1, sender);
        buffer[n] = '\0';
        std::cout << sender.toString() << ":" << buffer << std::endl;
    }
 
    return 0;
}
 
int main(int argc, char** argv)
{
    testUdpClient(argv[1], atoi(argv[2]));
    testDatagramSocket(argv[1], atoi(argv[2]));
    return 0;
}
