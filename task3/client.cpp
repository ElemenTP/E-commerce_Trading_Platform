#include "global.hpp"
#include "network.hpp"
using std::cerr;
//构造函数，从服务器中读出数据
Page::Page()
{
    ConnectSocket = INVALID_SOCKET;

    WSADATA wsaData;
    int iResult;

    struct sockaddr_in saconnect;

    char *datatemp;
    unsigned long long datalen;

    // 初始化 Winsock
    cout << "Initializing Winsock" << endl;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        cerr << "WSAStartup failed with error: " << iResult << endl;
        system("pause");
        exit(1);
    }

    cout << "Creating a socket to connect to the server." << endl;
    ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ConnectSocket == INVALID_SOCKET)
    {
        cerr << "ERROR creating socket." << WSAGetLastError() << endl;
        system("pause");
        WSACleanup();
        exit(1);
    }

    cout << "Connecting the server." << endl;
    ZeroMemory(&saconnect, sizeof(saconnect));
    saconnect.sin_family = AF_INET;
    saconnect.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    saconnect.sin_port = htons(PORT);

    iResult = connect(ConnectSocket, (struct sockaddr *)&saconnect, sizeof(saconnect));
    if (iResult)
    {
        cerr << "Failed to connect server " << PORT << ":" << WSAGetLastError() << endl;
        system("pause");
        closesocket(ConnectSocket);
        WSACleanup();
        exit(1);
    }

    iResult = recv(ConnectSocket, (char *)&datalen, sizeof(datalen), 0);
    if (iResult == 0)
    {
        cout << "ERROR: Connection closed." << endl;
        system("pause");
        closesocket(ConnectSocket);
        WSACleanup();
        exit(1);
    }
    else if (iResult == SOCKET_ERROR)
    {
        cout << "recv failed with error: "
             << WSAGetLastError() << endl;
        system("pause");
        closesocket(ConnectSocket);
        WSACleanup();
        exit(1);
    }
    datatemp = new char[datalen];
    iResult = recv(ConnectSocket, datatemp, datalen, 0);
    if (iResult == 0)
    {
        cout << "Connection closed" << endl;
        delete[] datatemp;
        system("pause");
        closesocket(ConnectSocket);
        WSACleanup();
        exit(1);
    }
    else if (iResult == SOCKET_ERROR)
    {
        cout << "recv failed with error: "
             << WSAGetLastError() << endl;
        delete[] datatemp;
        system("pause");
        closesocket(ConnectSocket);
        WSACleanup();
        exit(1);
    }
    else
    {
        string tmp;
        for (int i = 0; i < datalen - 1; i++)
            tmp.push_back(datatemp[i]);
        delete[] datatemp;
        data = json::parse(tmp);
        cout << "Data fetching was successful." << endl;
    }
    system("pause");
    system("cls");
}

void Page::storedata()
{
    if (cur_usr->getUserType() == client)
        *usr_json = *(Client *)cur_usr;
    else if (cur_usr->getUserType() == business)
        *usr_json = *(Business *)cur_usr;

    string send_temp = data.dump(4);
    unsigned long long datalen = send_temp.size() + 1;
    char *datatemp = new char[datalen];

    int iResult = send(ConnectSocket, (char *)&datalen, sizeof(datalen), 0);
    if (iResult == SOCKET_ERROR)
    {
        cerr << "Failed to send data to server: " << WSAGetLastError() << endl;
        system("pause");
        closesocket(ConnectSocket);
        WSACleanup();
        exit(1);
    }

    for (int i = 0; i < datalen - 1; i++)
        datatemp[i] = send_temp[i];
    iResult = send(ConnectSocket, datatemp, datalen, 0);
    if (iResult == SOCKET_ERROR)
    {
        cerr << "Failed to send data to server: " << WSAGetLastError() << endl;
        system("pause");
        closesocket(ConnectSocket);
        WSACleanup();
        exit(1);
    }
    delete[] datatemp;
    cout << "Data successfully sended." << endl;
}

Page::~Page()
{
    cout << "Detaching from the server, shutting down the socket." << endl;

    int iResult = shutdown(ConnectSocket, SD_BOTH);
    if (iResult == SOCKET_ERROR)
    {
        cerr << "Failed to shut down socket: " << WSAGetLastError() << endl;
        system("pause");
        closesocket(ConnectSocket);
        WSACleanup();
        exit(1);
    }

    cout << "Existing program." << endl;
    system("pause");

    closesocket(ConnectSocket);

    WSACleanup();
}
