//#include <winsock2.h>
//#include <stdio.h>
//#include <iostream>
//using namespace std;
//
//
////winsock2 ��������� ���� ����
//#pragma comment(lib,"ws2_32.lib")
//
//#define PORT 4444
//#define PACKET_SIZE 1024
//#define SERVER_IP "127.0.0.1"
//
//int main() {
//    //���ϸ��鶧 �⺻Ʋ
//    WSADATA wsaData;
//    WSAStartup(MAKEWORD(2, 2), &wsaData);
//
//
//    //IPv4��������ü��,TCP
//    //PF_INET�� ��������ü��, AF_INET�� �ּ�ü��
//    SOCKET hSocket;
//    hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
//
//    //��ü�� ������ ��°���
//    //��������ü�������� ��Ʈ�� ���� ������ ���� ����
//    SOCKADDR_IN tAddr = {};
//    tAddr.sin_family = AF_INET;
//    tAddr.sin_port = htons(PORT);
//    tAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
//
//    //������ ����
//    connect(hSocket, (SOCKADDR*)&tAddr, sizeof(tAddr));
//
//    char cBuffer[PACKET_SIZE] = { };
//    recv(hSocket, cBuffer, PACKET_SIZE, 0);
//    printf("Recv Msg : %s\n", cBuffer);
//
//    char cMsg[] = "Client Send";
//    send(hSocket, cMsg, strlen(cMsg), 0);
//
//    //�������ݾ���
//    closesocket(hSocket);
//
//    WSACleanup();
//    return 0;
//}

#include <iostream>
#include <string>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

//#define PORTs 4444
#define PACKET_SIZE 1024
//#define SERVER_IP "127.0.0.1"

DWORD WINAPI SendThread(LPVOID lpData);


int main()
{
   // string ipAddress = SERVER_IP; //IP Address of the server
   // int port = PORTs;               //Listening port # on the server


    // ���� ���̺귯�� �ʱ�ȭ
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);

    int wsResult = WSAStartup(ver, &wsData);
    char PORT[5], IP[15], ID[20];

    if (wsResult != 0)
    {
        cerr << "������ ������ �� �����ϴ�., Err #" << wsResult << endl;
        return 0;
    }

    // ���� ����
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
    {
        cerr << "������ �����Ҽ������ϴ�., ERR #" <<WSAGetLastError() << endl;
        WSACleanup();
        return SOCKET_ERROR;
    }

    printf("����� IP �ּ� : ");
    scanf("%s", &IP);

    printf("����� ��Ʈ ��ȣ : ");
    scanf("%s", &PORT);

    printf("����� �г��� : ");
    scanf("%s", &ID);

    // ���� �ּ� ����
    sockaddr_in hint = {0};
    hint.sin_family = AF_INET;
    hint.sin_port = htons(atoi(PORT)); // ��Ʈ
    hint.sin_addr.s_addr = inet_addr(IP);

    // ���� ����
    int connResult = connect(sock, (struct sockaddr*)&hint, sizeof(hint));
    if (connResult == SOCKET_ERROR)
    {
        cerr << "������ ���� �Ҽ� �����ϴ�., ERR #" << WSAGetLastError() << endl;
        closesocket(sock);
        WSACleanup();
        return SOCKET_ERROR;
    }

    CreateThread(NULL, 0, SendThread, (LPVOID)sock, 0, NULL);
    // ���� ���
    DWORD dwTmp;
    char text[1024] = "������ ���ӵǾ����ϴ�.\n";
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), text, strlen(text), &dwTmp, NULL);


    //do-while loop to send and receive data
    char buf[4096];
    string userInput;

    // ���� & ���� ��Ǫ
    while (1)
    {
        char buffer[1024] = { 0 };
        int len = recv(sock, buffer, sizeof(buffer), 0);
        if (len <= 0)
        {
            printf("���� ����.");
            break;
        }

        // �޽��� ���
        WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buffer, strlen(buffer), &dwTmp, NULL);
    }
    //���� ����
    closesocket(sock);
    WSACleanup();
    return 0;
}

DWORD WINAPI SendThread(LPVOID lpData)
{
    SOCKET sock = (SOCKET)lpData;
    while (1)
    {
        printf("������ ���� : ");
        DWORD dwTmp;
        char text[1024] = { 0 };
        ReadFile(GetStdHandle(STD_INPUT_HANDLE), text, 1024, &dwTmp, NULL);
        send(sock, text, strlen(text), 0);
    }
    return 0;
}