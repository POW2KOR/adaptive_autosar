#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <cstring>
#include <string>
#include <iostream>
#include <array>

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

namespace test
{

constexpr uint8_t index_for_response_code = 12;
constexpr uint8_t positive_response_code_for_routing_activation = 0x10;
constexpr uint8_t server_busy_response_code = 0x7f;

class Communication {
public:
    bool OpenConnectionWithDiagnosticManager();
    void InitiateRoutingActivation();
    uint8_t InitiateSerivceReadDataByIdentifier(uint32_t& did);

private:
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    const char* server_ip = "127.0.0.1";
    const std::uint16_t port = 13400;
    int server_sock_fd = -1;
};
}

#endif  //COMMUNICATION_H
