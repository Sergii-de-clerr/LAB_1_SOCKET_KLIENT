#include <winsock2.h>
#include <stdio.h>
#include <time.h>
#pragma comment(lib, "wsock32.lib")
#pragma warning(disable: 4996)

void UDP_Conecting();
void TCP_Conecting();

int main(int argc, char* argv[])
{
    UDP_Conecting();
    //TCP_Conecting();
}

void UDP_Conecting()
{
    WSADATA WsaData;
    WSAStartup(MAKEWORD(2, 2), &WsaData) == NO_ERROR;
    int handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (handle <= 0)
    {
        printf("failed to create socket\n");
        WSAStartup(MAKEWORD(2, 2), &WsaData) == NO_ERROR;
        return 0;
    }

    SOCKADDR_IN address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons((unsigned short)1111);

    if (bind(handle, (const SOCKADDR*)&address, sizeof(SOCKADDR_IN)) < 0)
    {
        printf("failed to bind socket\n");
        return 0;
    }

    /*DWORD nonBlocking = 1;
    if (ioctlsocket(handle, FIONBIO, &nonBlocking) != 0)
    {
        printf("failed to set non-blocking socket\n");
        return 0;
    }*/

    int num_of_recv_Sock = 0;

    //const int NUM_OF_PACKETS = 1000000;
    //const int SIZE_OF_PACKETS = 256;

    clock_t Cur_Time_Start, Cur_Time_Final;

    unsigned char packet_data[65500];
    unsigned int maximum_packet_size = sizeof(packet_data);
    clock_t Cur_Check_Time_Start = clock(), Cur_Check_Time_Final = clock();

    while (1)
    {
        Cur_Check_Time_Final = clock();
        typedef int socklen_t;
        SOCKADDR_IN from;
        socklen_t fromLength = sizeof(from);
        int received_bytes = recvfrom(handle, (char*)packet_data, maximum_packet_size,
            0, (SOCKADDR*)&from, &fromLength);
        if (received_bytes <= 0)
        {
            //break;
        }
        else
        {
            num_of_recv_Sock++;
            Cur_Check_Time_Start = clock();
            /*printf("%s \n", packet_data);
            printf("%i \n", num_of_recv_Sock);*/
        }
        if ((double)(Cur_Check_Time_Final - Cur_Check_Time_Start) / CLOCKS_PER_SEC > 1)
        {
            break;
        }
        if (num_of_recv_Sock == 1)
        {
            Cur_Time_Start = clock();
            DWORD nonBlocking = 1;
            if (ioctlsocket(handle, FIONBIO, &nonBlocking) != 0)
            {
                printf("failed to set non-blocking socket\n");
                return 0;
            }
        }
    }
    printf("%i \n", num_of_recv_Sock);

    double res = (double)(Cur_Check_Time_Start - Cur_Time_Start) / CLOCKS_PER_SEC;

    printf("%f \n", res);

    system("pause");
}

void TCP_Conecting()
{
    ADDRESS_FAMILY Type_of_socket = AF_INET;
    WSADATA wsadata;
    clock_t Cur_Time_Start, Cur_Time_Final;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsadata) != 0)
    {
        return 1;
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = Type_of_socket;

    SOCKET Connection = socket(Type_of_socket, SOCK_STREAM, IPPROTO_TCP);
    if (connect(Connection, (SOCKADDR*)&addr, sizeofaddr) != 0)
    {
        printf("Error 2");
    }
    else
    {
        printf("Connected!\n");
        //char msg[256];

        /*char msg = "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333";*/
            //char msg = "0";

        char msg[65536];

        Cur_Time_Start = clock();

        int num_of_recv_Sock = 0;

        clock_t Cur_Check_Time_Start = clock(), Cur_Check_Time_Final = clock();

        while(1)
        {
            Cur_Check_Time_Final = clock();
            //printf("%s \n", msg);
            if (recv(Connection, msg, sizeof(msg), NULL) == SOCKET_ERROR)
            {
                //break;
            }
            else
            {
                num_of_recv_Sock++;
                Cur_Check_Time_Start = clock();
            }
            if (num_of_recv_Sock == 1)
            {
                DWORD nonBlocking = 1;
                if (ioctlsocket(Connection, FIONBIO, &nonBlocking) != 0)
                {
                    printf("failed to set non-blocking socket\n");
                    return 0;
                }
            }
            if ((double)(Cur_Check_Time_Final - Cur_Check_Time_Start) / CLOCKS_PER_SEC > 1)
            {
                break;
            }
        }

        /*recvfrom(Connection, msg, sizeof(msg), NULL, (SOCKADDR*)&addr, sizeofaddr);*/

        /*if (recv(Connection, msg, sizeof(msg), NULL) != SOCKET_ERROR)
        {
            printf("It's con!\n");
        }*/

        /*for (int i = 0; i < 1; i++)
        {
            send(Connection, msg, sizeof(msg), NULL);
        }*/

        Cur_Time_Final = clock();

        double res = (double)(Cur_Check_Time_Start - Cur_Time_Start) / CLOCKS_PER_SEC;

        printf("%f \n", res);
        printf("%i \n", num_of_recv_Sock);
    }

    system("pause");
}