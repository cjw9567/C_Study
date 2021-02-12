//#include <winsock2.h>
//#include <stdio.h>
//#include <iostream>
//using namespace std;
//
//
////winsock2 헤더파일을 위한 설정
//#pragma comment(lib,"ws2_32.lib")
//
//#define PORT 4444
//#define PACKET_SIZE 1024
//#define SERVER_IP "127.0.0.1"
//
//int main() {
//    //소켓만들때 기본틀
//    WSADATA wsaData;
//    WSAStartup(MAKEWORD(2, 2), &wsaData);
//
//
//    //IPv4프로토콜체계,TCP
//    //PF_INET은 프로토콜체계, AF_INET은 주소체계
//    SOCKET hSocket;
//    hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
//
//    //개체의 정보를 담는공간
//    //프로토콜체계정보와 포트에 대한 정보를 넣은 공간
//    SOCKADDR_IN tAddr = {};
//    tAddr.sin_family = AF_INET;
//    tAddr.sin_port = htons(PORT);
//    tAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
//
//    //서버에 연결
//    connect(hSocket, (SOCKADDR*)&tAddr, sizeof(tAddr));
//
//    char cBuffer[PACKET_SIZE] = { };
//    recv(hSocket, cBuffer, PACKET_SIZE, 0);
//    printf("Recv Msg : %s\n", cBuffer);
//
//    char cMsg[] = "Client Send";
//    send(hSocket, cMsg, strlen(cMsg), 0);
//
//    //소켓을닫아줌
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


    // 소켓 라이브러리 초기화
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);

    int wsResult = WSAStartup(ver, &wsData);
    char PORT[5], IP[15], ID[20];

    if (wsResult != 0)
    {
        cerr << "윈속을 실행할 수 없습니다., Err #" << wsResult << endl;
        return 0;
    }

    // 소켓 생성
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
    {
        cerr << "소켓을 생성할수없습니다., ERR #" <<WSAGetLastError() << endl;
        WSACleanup();
        return SOCKET_ERROR;
    }

    printf("사용할 IP 주소 : ");
    scanf("%s", &IP);

    printf("사용할 포트 번호 : ");
    scanf("%s", &PORT);

    printf("사용할 닉네임 : ");
    scanf("%s", &ID);

    // 소켓 주소 정보
    sockaddr_in hint = {0};
    hint.sin_family = AF_INET;
    hint.sin_port = htons(atoi(PORT)); // 포트
    hint.sin_addr.s_addr = inet_addr(IP);

    // 소켓 접속
    int connResult = connect(sock, (struct sockaddr*)&hint, sizeof(hint));
    if (connResult == SOCKET_ERROR)
    {
        cerr << "서버에 접속 할수 없습니다., ERR #" << WSAGetLastError() << endl;
        closesocket(sock);
        WSACleanup();
        return SOCKET_ERROR;
    }

    CreateThread(NULL, 0, SendThread, (LPVOID)sock, 0, NULL);
    // 상태 출력
    DWORD dwTmp;
    char text[1024] = "서버에 접속되었습니다.\n";
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), text, strlen(text), &dwTmp, NULL);


    //do-while loop to send and receive data
    char buf[4096];
    string userInput;

    // 전송 & 수신 루푸
    while (1)
    {
        char buffer[1024] = { 0 };
        int len = recv(sock, buffer, sizeof(buffer), 0);
        if (len <= 0)
        {
            printf("접속 종료.");
            break;
        }

        // 메시지 출력
        WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buffer, strlen(buffer), &dwTmp, NULL);
    }
    //소켓 해제
    closesocket(sock);
    WSACleanup();
    return 0;
}

DWORD WINAPI SendThread(LPVOID lpData)
{
    SOCKET sock = (SOCKET)lpData;
    while (1)
    {
        printf("전송할 내용 : ");
        DWORD dwTmp;
        char text[1024] = { 0 };
        ReadFile(GetStdHandle(STD_INPUT_HANDLE), text, 1024, &dwTmp, NULL);
        send(sock, text, strlen(text), 0);
    }
    return 0;
}