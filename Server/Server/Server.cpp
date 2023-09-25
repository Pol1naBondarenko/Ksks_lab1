#include <iostream>
#include <winsock2.h>
#include <clocale>
#include <windows.h>
#include <sstream>
#include <vector>
#include <string>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#define BUFLEN 2048
#define PORT 5155

using namespace std;

struct ParsedCommand {
    string command;
    vector<string> parameters;
    string paramStr;
};

ParsedCommand ParseCommand(const string& data) {
    ParsedCommand parsedCommand;

    // ������ ������� ������� '/'
    size_t slashPos = data.find('/');

    if (slashPos != string::npos) {
        // ������� ������� �� '/'
        parsedCommand.command = data.substr(0, slashPos);

        // ������� ��������� ���� '/'
        string paramsStr = data.substr(slashPos + 1);

        // �������� ��������� ��������
        istringstream paramStream(paramsStr);
        string param;
        while (paramStream >> param) {
            parsedCommand.parameters.push_back(param);
        }

        parsedCommand.paramStr = paramsStr;
    }
    else {
        parsedCommand.command = data;
    }
    return parsedCommand;
}

void RecogniseCommand(const ParsedCommand& parsedCommand) {
    cout << "�������� ������� " << parsedCommand.command << " � ����������� " << parsedCommand.paramStr << endl;

    if (parsedCommand.command == "clear display") {
        cout << "������� ������� clear display" << endl;
    }
    else if (parsedCommand.command == "draw pixel") {
        cout << "������� ������� draw pixel" << endl;
    }
    else if (parsedCommand.command == "draw line") {
        cout << "������� ������� draw line" << endl;
    }
    else if (parsedCommand.command == "draw rectangle") {
        cout << "������� ������� draw rectangle" << endl;
    }
    else if (parsedCommand.command == "fill rectangle") {
        cout << "������� ������� fill rectangle" << endl;
    }
    else if (parsedCommand.command == "draw ellipse") {
        cout << "������� ������� draw ellipse" << endl;
    }
    else if (parsedCommand.command == "fill ellipse") {
        cout << "������� ������� fill ellipse" << endl;
    }
    else if (parsedCommand.command == "draw circle") {
        cout << "������� ������� draw circle" << endl;
    }
    else if (parsedCommand.command == "fill circle") {
        cout << "������� ������� fill circle" << endl;
    }
    else if (parsedCommand.command == "draw rounded rectangle") {
        cout << "������� ������� draw rounded rectangle" << endl;
    }
    else if (parsedCommand.command == "fill rounded rectangle") {
        cout << "������� ������� fill rounded rectangle" << endl;
    }
    else if (parsedCommand.command == "draw text") {
        cout << "������� ������� draw text" << endl;
    }
    else if (parsedCommand.command == "draw image") {
        cout << "������� ������� draw image" << endl;
    }
    else {
        cout << "���� ������� �� ����" << endl;
    }
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    sockaddr_in serv, client;

    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        exit(0);
    }

    SOCKET sock_1;
    if ((sock_1 = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        exit(EXIT_FAILURE);
    }

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(PORT);

    if (bind(sock_1, (sockaddr*)&serv, sizeof(serv)) == SOCKET_ERROR) {
        exit(EXIT_FAILURE);
    }

    while (true) {
        fflush(stdout);
        char buffer[BUFLEN] = {};
        int slen = sizeof(sockaddr_in);

        if (recvfrom(sock_1, buffer, BUFLEN, 0, (sockaddr*)&client, &slen) == SOCKET_ERROR) {
            exit(0);
        }

        string receivedData(buffer);

        ParsedCommand parsedCommand = ParseCommand(receivedData);
        RecogniseCommand(parsedCommand);
    }

    closesocket(sock_1);
    WSACleanup();
    return 0;
}
