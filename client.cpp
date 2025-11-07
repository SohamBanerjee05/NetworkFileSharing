#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char buffer[1024];

    cout << "Initializing Winsock..." << endl;
    WSAStartup(MAKEWORD(2,2), &wsa);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // same computer
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);

    connect(sock, (struct sockaddr*)&server, sizeof(server));
    cout << "Connected to server!" << endl;

    ofstream outfile("received.txt", ios::binary);
    int bytes;
    while ((bytes = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
        outfile.write(buffer, bytes);
    }
    outfile.close();
    cout << "File received successfully!" << endl;

    closesocket(sock);
    WSACleanup();
    return 0;
}
