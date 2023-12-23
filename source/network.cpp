#include "entry.hpp"

namespace zjy
{
    int test_winsocket_tcp_server(Message& msg)
    {
        int res = 0;
        WSADATA wsa_data;
        SOCKET client_socket;
        SOCKET server_socket;
        sockaddr_in client_addr;
        sockaddr_in server_addr;
        int client_addr_len = sizeof(client_addr);

        // Initialize Winsock
        res = WSAStartup(MAKEWORD(2, 2), &wsa_data);
        if (res != 0) 
        {
            std::cerr << "WSAStartup failed\n";
            return 0;
        }

        // create a tcp socket
        server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (server_socket == INVALID_SOCKET)
        {
            std::cerr << "Error creating socket: " << WSAGetLastError() << "\n";
            WSACleanup();
            return 0;
        }

        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
        server_addr.sin_port = htons(14000);

        res = bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr));
        if (res == SOCKET_ERROR)
        {
            std::cerr << "Bind failed: " << WSAGetLastError() << "\n";
            WSACleanup();
            return 0;
        }

        // listen for incoming connections
        res = listen(server_socket, SOMAXCONN);
        if (res == SOCKET_ERROR)
        {
            std::cerr << "listen failed: " << WSAGetLastError() << "\n";
            WSACleanup();
            return 0;
        }

        std::cerr << "Server listening on port 14000...\n";

        // accept a client connection
        client_socket = accept(server_socket, (sockaddr*)&client_addr, &client_addr_len);
        if (client_socket == INVALID_SOCKET)
        {
            std::cerr << "accept failed: " << WSAGetLastError() << "\n";
            WSACleanup();
            return 0;
        }

        std::cerr << "client connected\n";

        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received == SOCKET_ERROR)
        {
            std::cerr << "received failed: " << WSAGetLastError() << "\n";
        }
        else if (bytes_received == 0)
        {
            std::cerr << "client disconnected\n";
        }
        else 
        {   
            buffer[bytes_received] = '\0';
            std::cerr << "received message from client: " << buffer  << "\n";
            const char* response_msg = "message received successfully";
            send(client_socket, response_msg, strlen(response_msg), 0);
        }

        closesocket(client_socket);
        closesocket(server_socket);
        WSACleanup();

        return 1;
    }

    int test_winsocket_tcp_client(Message& msg)
    {
        int res = 0;
        WSADATA wsa_data;
        SOCKET client_socket;
        SOCKET server_socket;
        sockaddr_in client_addr;
        sockaddr_in server_addr;
        int client_addr_len = sizeof(client_addr);

        // Initialize Winsock
        res = WSAStartup(MAKEWORD(2, 2), &wsa_data);
        if (res != 0) 
        {
            std::cerr << "WSAStartup failed\n";
            return 0;
        }

        // create a tcp socket
        client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (client_socket == INVALID_SOCKET)
        {
            std::cerr << "Error creating socket: " << WSAGetLastError() << "\n";
            WSACleanup();
            return 0;
        }

        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
        server_addr.sin_port = htons(14000);

        res = connect(client_socket, (sockaddr*)&server_addr, sizeof(server_addr));
        if (res == SOCKET_ERROR)
        {
            std::cerr << "connection failed: " << WSAGetLastError() << "\n";
            WSACleanup();
            return 0;
        }
        std::cerr << "connected to server" << "\n";

        const char* send_msg = "hello, tcp server!";
        int bytes_send = send(client_socket, send_msg, strlen(send_msg), 0);
        std::cerr << "whole send data bytes: " << strlen(send_msg) << "\n"
                  << "sended data bytes: " << bytes_send << "\n";

        char buffer[1024];
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        buffer[bytes_received] = '\0';
        std::cerr << "received data from tcp server: " << buffer << "\n";

        closesocket(client_socket);
        WSACleanup();
        return 1;
    }

    int network_unit(Message& msg)
    {
        std::map<std::string, std::function<int(Message&)>> cmd_map = 
        {
            {"--test-win-socket-tcp-server", test_winsocket_tcp_server},
            {"--test-winsocket-tcp-client", test_winsocket_tcp_client}
        };

        auto it = cmd_map.find(msg.msg_pool.at(2));
        if (it != cmd_map.end())
        {
            it->second(msg);
        }
        else 
        {
            std::cerr << "invalid command: " << msg.msg_pool.at(2) << "\n";
        }

        return 1;
    }
}