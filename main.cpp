#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>

int main(int argc, char const* argv[]) {
    // segmentation fault if argc < 3
    if(argc < 3) {
        std::cout << "Usage: " << argv[0] << " <ipv4_address> <port_number>" << std::endl;
        return 0;
    }
    // initialize ip address and port number
    struct sockaddr_in server_address;
    int server_port = atoi(argv[2]);

    server_address.sin_family = AF_INET;


    // convert ip address from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &server_address) < 0) {
        std::cerr << "Invalid Ipv4 address.\n";
        return -1;
    }
    

    // convert port (int) from host-byte order to network-byte order (big endian)
    server_address.sin_port = htons(server_port);


    // create socket
    int sock = 0, connection_fd;
    if(socket(AF_INET, SOCK_STREAM, 0) < 0) {
        std::cerr << "Failed to create socket.\n";
        return -2;
    }


    // bind socket to port
    bind(sock, (sockaddr*)&server_address, sizeof(server_address));

    // connect
    if(connection_fd = connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Failed to connect.\n";
        return -3;
    }
    

    // send
    char* message = "Hello, world!";
    send(sock, message, strlen(message), 0);
}