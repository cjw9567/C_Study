#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <thread> //멀티쓰레드를 사용하기위한!!!

#pragma comment (lib, "ws2_32.lib")

using namespace std;

#define MAX_SOCKET  10 // 최대 접속 가능한 소켓의 갯수!
#define PACKET_SIZE 1024
#define SERVER_IP "127.0.0.1"


int main()
{
    // 소켓 라이브러리 초기화
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);

    int wsOk = WSAStartup(ver, &wsData);

    if (wsOk != 0)
    {
        cerr << "Can't Initialize winsock! Quitting" << endl;
        return 0;
    }

    //사용할 포트번호
    char PORT[5];

    // 소켓 배열   다중 클라이언트 접속을 하기위해 배열을 사용.
    SOCKET socket_arry[MAX_SOCKET] = { 0 };   //최대값은 위에서 정의해줌.
    HANDLE hEvent_arry[MAX_SOCKET] = { 0 };

    // 대기용 소켓 생성
    socket_arry[0] = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_arry[0] == INVALID_SOCKET)
    {
        cerr << "Can't create a socket! Quitting" << endl;
        return -1;
    }


    printf("사용하려는 포트번호 : ");
    scanf("%s", &PORT);

    /// 소켓 주소 정보 작성
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(atoi(PORT)); // 포트 번호를 받아서 사용.
    hint.sin_addr.S_un.S_addr = INADDR_ANY; 

    // 소켓 바인드
    if(bind(socket_arry[0], (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR)
    {
        closesocket(socket_arry[0]);
        return -1;
    }


    // 소켓 대기
    if(listen(socket_arry[0], SOMAXCONN) == SOCKET_ERROR)
    {
        closesocket(socket_arry[0]);
        //printf("listen() Error");
        return -1;
    }

    // 이벤트 핸들 생성
    for (int i = 0; i < MAX_SOCKET; i++)
    {
        hEvent_arry[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
        if (hEvent_arry[i] == INVALID_HANDLE_VALUE)
        {
            closesocket(socket_arry[0]);
            printf("서버 이벤트 생성 실패");
            return SOCKET_ERROR;
        }
    }


    // 대기 소켓 이벤트 핸들 설정
    if (WSAEventSelect(socket_arry[0], hEvent_arry[0], FD_ACCEPT) == SOCKET_ERROR)
    {
        closesocket(socket_arry[0]);
        CloseHandle(hEvent_arry[0]);
        printf("서버 이벤트 설정 실패");
        return SOCKET_ERROR;
    }

    // 상태 출력
    DWORD dwTmp;
    //char* pText = "클라이언트 접속을 기다리고 있습니다.\n";
    printf("클라이언트 접속을 기다리고 있습니다.\n");

    // 설정된 이벤트 핸들 갯수
    int clinet = 1;

    // 접속 루푸
    while (1)
    {
        // 소켓 접속 대기
        DWORD dwObject = WaitForMultipleObjectsEx(clinet, hEvent_arry, FALSE, INFINITE, 0);
        if (dwObject == INFINITE) continue;

        if (dwObject == WAIT_OBJECT_0)
        {
            // 클라이언트 소켓 생성
            SOCKADDR_IN clntAddr;
            int clntLen = sizeof(clntAddr);
            SOCKET socket_client = accept(socket_arry[0], (SOCKADDR*)&clntAddr, &clntLen);

            // 빈 배열 검색
            int index = -1;
            for (int c = 1; c < MAX_SOCKET; c++)
            {
                if (socket_arry[c] == 0)
                {
                    index = c;
                    break;
                }
            }

            if (index > 0)  //하나라도 접속
            {
                // 클라이언트 이벤트 핸들 설정
                if (WSAEventSelect(socket_client, hEvent_arry[index], FD_READ | FD_CLOSE) == SOCKET_ERROR)
                {
                    DWORD dwTmp;
                    printf("클라이언트 이벤트 설정 실패 하였습니다.\n");
                    continue;
                }

                char buffer[1024] = { 0 };

                printf("%d번 -> 클라이언트 접속\n", index);

                // 배열에 소켓 저장
                socket_arry[index] = socket_client;
                clinet = max(clinet, index + 1);
            }
            else  //허용 소켓 초과
            {
                DWORD dwTmp;
                printf("더이상 서버에 접속 할수 없습니다..\n");
                closesocket(socket_client);
            }
        }
        else
        {
            int index = (dwObject - WAIT_OBJECT_0);

            DWORD dwTmp;
            char buffer[1024] = { 0 };
            wsprintfA(buffer, "%d번 사용자 : ", index);
            WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buffer, strlen(buffer), &dwTmp, NULL);



            // 메시지 수신
            memset(buffer, 0, sizeof(buffer));
            int cnt = recv(socket_arry[index], buffer, sizeof(buffer), 0);
            if (cnt <= 0)
            {
                // 클라이언트 접속 종료
                closesocket(socket_arry[index]);
                printf("클라이언트 접속 종료..\n");

                // 배열에 소켓 제거
                socket_arry[index] = 0;
                continue;
            }
            // 메시지 출력
            WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buffer, cnt, &dwTmp, NULL);

            // 애코 처리
            char send_buffer[1024] = { 0 };
            wsprintfA(send_buffer, "%d 번 사용자 : %s", index, buffer);

            for (int c = 1; c < MAX_SOCKET; c++)
            {
                if (socket_arry[c] != 0 && c != index)
                {
                    // 수신받은 클라이언트 제외 하고 애코 처리
                    send(socket_arry[c], send_buffer, strlen(send_buffer), 0);
                }
            }
        }

    }

    // 서버 소켓 해제
    closesocket(socket_arry[0]);
    CloseHandle(hEvent_arry[0]);
    return 0;

    //Cleanup winsock
    WSACleanup();
    return 0;
}