#include "include/communication.h"
#include <cstring>

using namespace test;

bool Communication::OpenConnectionWithDiagnosticManager()
{
    server_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock_fd == -1) {
        std::cerr << "socket creation failed...\n";
        return false;
    } else {
        std::cout << "Socket successfully created..\n";
    }
    bzero(&server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    server_addr.sin_port = htons(port);

    if (connect(server_sock_fd, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr)) != 0) {
        std::cerr << "Connection with the server failed...\n";
        return false;
    } else {
        std::cout << "Connected to the server..\n";
    }
}

void Communication::InitiateRoutingActivation()
{
    std::array<uint8_t, 15> routing_data;
    routing_data.fill(0);

    std::array<uint8_t, 40> routing_response;
    routing_response.fill(0);

    routing_data[0] = 0x02; // Protocol Version
    routing_data[1] = 0xFD; // Protocol Inversion
    routing_data[2] = 0x00; // 2 Bytes indicatesPayload type:0x0005 is For Routing Acrivation,
    routing_data[3] = 0x05;
    routing_data[4] = 0x00; // 4 bytes, Indicates Length of payload
    routing_data[5] = 0x00;
    routing_data[6] = 0x00;
    routing_data[7] = 0x07;
    routing_data[8] = 0x10;// 2 bytes Source Address
    routing_data[9] = 0x01;
    routing_data[10] = 0x00; // 5 Bytes Reserved by Standard
    routing_data[11] = 0x00;
    routing_data[12] = 0x00;
    routing_data[13] = 0x00;
    routing_data[14] = 0x00;


    write(server_sock_fd, routing_data.data(), routing_data.size());

    read(server_sock_fd, routing_response.data(), routing_response.size());

    if (routing_response[index_for_response_code] == positive_response_code_for_routing_activation){
        std::cout << "Received Positive Response For Routing Activation... \n";
        //retun true;
    }else{
        std::cerr << "Received Negative Response For Routing Activation... \n";
        //retun false;
    }
}

uint8_t Communication::InitiateSerivceReadDataByIdentifier(uint32_t& did)
{
    std::array<uint8_t, 15> uds_data;
    uds_data.fill(0);

    std::array<uint8_t, 100> response_from_ecu;
    response_from_ecu.fill(0);

    uds_data[0] = 0x02; // Protocol Version
    uds_data[1] = 0xFD; // Protocol Inversion
    uds_data[2] = 0x80; // Payload type : 0x8001 is For UDS message,
    uds_data[3] = 0x01;
    uds_data[4] = 0x00; // 4 bytes, Lemgh of payload of UDS message
    uds_data[5] = 0x00;
    uds_data[6] = 0x00;
    uds_data[7] = 0x07;
    uds_data[8] = 0x10; // 2 bytes Source Address
    uds_data[9] = 0x01;
    uds_data[10] = 0x00; //2 bytes Destination Address. 0x0001 comes from our NCD , Target Address
    uds_data[11] = 0x01;
    uds_data[12] = 0x22;// ID for Read, Service ID. 0x22 is for Read Data Idenfitier

    uds_data[13] = static_cast<uint8_t>((did >> 8) & 0xFF) ;    // DID to read
    uds_data[14] = static_cast<uint8_t>(did & 0xFF);

    write(server_sock_fd, uds_data.data(), uds_data.size());

    //First Read is always for reading the DoIP Acknowledgement
    read(server_sock_fd, response_from_ecu.data(), response_from_ecu.size());

    //Second Read is for the Resposnse from ECU
    size_t n = read(server_sock_fd, response_from_ecu.data(), response_from_ecu.size());
    if (response_from_ecu[index_for_response_code] == server_busy_response_code){
        std::cerr << "Server is Busy, Please Read again... \n";

        n = read(server_sock_fd, response_from_ecu.data(), response_from_ecu.size());

        return response_from_ecu[index_for_response_code];
    }

    return 0x00;    //Dummy return
}
