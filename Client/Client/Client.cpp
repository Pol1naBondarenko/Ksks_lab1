#include <iostream>
#include <winsock2.h>
#include <clocale>
#include <windows.h>
#include <sstream>
#include <vector>
#include <string>

#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)

#define SERVER_IP "127.0.0.1"
#define PORT 5155

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Доступні команди:" << endl;
    cout << "clear display (color)" << endl;
    cout << "draw pixel (x y color)" << endl;
    cout << "draw line (x0 y0 x1 y1 color)" << endl;
    cout << "draw rectangle (x0 y0 width height color)" << endl;
    cout << "fill rectangle (x0 y0 width height color)" << endl;
    cout << "draw ellipse (x0 y0 radius_x radius_y color)" << endl;
    cout << "fill ellipse (x0 y0 radius_x radius_y color)" << endl;
    cout << "draw circle (x0 y0 radius color)" << endl;
    cout << "fill circle (x0 y0 radius color)" << endl;
    cout << "draw rounded rectangle (x0 y0 width height radius color)" << endl;
    cout << "fill rounded rectangle (x0 y0 width height radius color)" << endl;
    cout << "draw text (x0 y0 color font_number length text)" << endl;
    cout << "draw image (x0 y0 width height data)" << endl << endl;

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "Failed to initialize Winsock." << endl;
        return 1;
    }

    SOCKET sock;
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        cout << "Failed to create socket." << endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    while (true) {
        string command;
        cout << "Введіть команду: ";
        getline(cin, command);

        string parameters;
        cout << "Введіть параметри: ";
        getline(cin, parameters);

        string fullCommand = command + "/" + parameters;

        if (sendto(sock, fullCommand.c_str(), fullCommand.length(), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            cout << "Failed to send data." << endl;
            closesocket(sock);
            WSACleanup();
            return 1;
        }
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
