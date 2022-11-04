#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include<iostream>

/*
Linux & Mac version
*/

class simple_udp{
    int sock;
    struct sockaddr_in addr;        // struct for connection side information

public:
    simple_udp(std::string address, int port){
        sock = socket(AF_INET, SOCK_DGRAM, 0);      // define socket(AF_INET: IPv4, SOCK_DGRAM: no guaranteed com, PROTOCOL: 0) 
        addr.sin_family = AF_INET;                  // fixed to AF_INET 
        addr.sin_addr.s_addr = inet_addr(address.c_str());  // IP address
        addr.sin_port = htons(port);                // Port number
    }
    void udp_send(std::string word){
        sendto(sock, word.c_str(), word.length(), 0, (struct sockaddr *)&addr, sizeof(addr));
        // int sendto(int socket, char *buffer, int length, int flags,
        //   struct sockaddr *address, int address_len);
    }

    void udp_bind(){
        bind(sock, (const struct sockaddr *)&addr, sizeof(addr));
        // Barclay socket bind
    }
    std::string udp_recv(){
        #define BUFFER_MAX 400          // define rcv buffer
        char buf[BUFFER_MAX];
        memset(buf, 0, sizeof(buf));    // initialise the buffer
        recv(sock, buf, sizeof(buf), 0);
        return std::string(buf);
    }
    void udp_recv(char *buf, int size){ // set parameter as arguments
        memset(buf, 0, size);
        recv(sock, buf, size, 0);
    }

    ~simple_udp(){
        close(sock);
    }
};
