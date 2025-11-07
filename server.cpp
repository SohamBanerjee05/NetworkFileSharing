#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    WSADATA wsa;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in server, client;
    int c;
    char buffer[1024];

    cout << "Initializing Winsock..." << endl;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        cout << "Failed. Error Code: " << WSAGetLastError() << endl;
        return 1;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(serverSocket, (struct sockaddr*)&server, sizeof(server));
    listen(serverSocket, 3);
    cout << "Server started. Waiting for connection..." << endl;

    c = sizeof(struct sockaddr_in);
    clientSocket = accept(serverSocket, (struct sockaddr*)&client, &c);
    cout << "Client connected!" << endl;

    ifstream file("data.txt", ios::binary);
    while (!file.eof()) {
        file.read(buffer, sizeof(buffer));
        send(clientSocket, buffer, file.gcount(), 0);
    }
    file.close();
    cout << "File sent successfully!" << endl;

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
