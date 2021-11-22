#include "..\network.hpp"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main(void)
{
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct sockaddr_in salisten;
	struct sockaddr_in saconnect;
	int saconnect_len = sizeof(saconnect);

	ifstream iptdata; //输入文件
	ofstream optdata; //输出文件
	string datastr;
	char* datatemp;
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

	cout << "Creating the listen socket" << endl;
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET)
	{
		cerr << "ERROR creating socket." << WSAGetLastError() << endl;
		system("pause");
		WSACleanup();
		exit(1);
	}

	cout << "Binding the listen socket to port: " << PORT << endl;
	ZeroMemory(&salisten, sizeof(salisten));
	salisten.sin_family = AF_INET;
	salisten.sin_addr.s_addr = INADDR_ANY;
	salisten.sin_port = htons(PORT);

	iResult = bind(ListenSocket, (struct sockaddr*)&salisten, sizeof(salisten));
	if (iResult)
	{
		cerr << "Failed to bind port " << PORT << ":" << WSAGetLastError() << endl;
		system("pause");
		closesocket(ListenSocket);
		WSACleanup();
		exit(1);
	}

	cout << "Starting to listen" << endl;
	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult)
	{
		cerr << "Failed to start listening: " << WSAGetLastError() << endl;
		system("pause");
		closesocket(ListenSocket);
		WSACleanup();
		exit(1);
	}

	cout << "Waiting for a client to connect" << endl;
	ClientSocket = accept(ListenSocket, (struct sockaddr*)&saconnect, &saconnect_len);
	if (ClientSocket == INVALID_SOCKET)
	{
		cerr << "Failed to connect client: " << WSAGetLastError() << endl;
		system("pause");
		closesocket(ListenSocket);
		WSACleanup();
		exit(1);
	}
	cout << "A client has successfully connected, shutting down listen socket." << endl;
	closesocket(ListenSocket);

	cout << "Sending data to the client." << endl;
	iptdata.open("datafile.json");
	if (iptdata)
		getline(iptdata, datastr, (char)EOF);
	iptdata.close();

	datalen = datastr.size() + 1;
	iResult = send(ClientSocket, (char*)&datalen, sizeof(datalen), 0);
	if (iResult == SOCKET_ERROR)
	{
		cerr << "Failed to send data to client: " << WSAGetLastError() << endl;
		system("pause");
		closesocket(ClientSocket);
		WSACleanup();
		exit(1);
	}

	datatemp = new char[datalen];
	for (int i = 0; i < datalen - 1; i++)
		datatemp[i] = datastr[i];
	iResult = send(ClientSocket, datatemp, datalen, 0);
	if (iResult == SOCKET_ERROR)
	{
		cerr << "Failed to send data to client: " << WSAGetLastError() << endl;
		system("pause");
		closesocket(ClientSocket);
		WSACleanup();
		exit(1);
	}
	delete[] datatemp;
	cout << "Data successfully sended. Start to receive data." << endl;

	do
	{
		iResult = recv(ClientSocket, (char*)&datalen, sizeof(datalen), 0);
		if (iResult == 0)
		{
			cout << "Connection closed" << endl;
			break;
		}
		else if (iResult == SOCKET_ERROR)
		{
			cout << "recv failed with error: "
				<< WSAGetLastError() << endl;
			system("pause");
			closesocket(ClientSocket);
			WSACleanup();
			exit(1);
		}
		datatemp = new char[datalen];
		iResult = recv(ClientSocket, datatemp, datalen, 0);
		if (iResult == 0)
		{
			cout << "Connection closed" << endl;
			delete[] datatemp;
			break;
		}
		else if (iResult == SOCKET_ERROR)
		{
			cout << "recv failed with error: "
				<< WSAGetLastError() << endl;
			delete[] datatemp;
			system("pause");
			closesocket(ClientSocket);
			WSACleanup();
			exit(1);
		}
		else
		{
			optdata.open("datafile.json");
			for (int i = 0; i < datalen - 1; i++)
				optdata << datatemp[i];
			optdata.close();
			delete[] datatemp;
		}
	} while (true);

	cout << "Client disconnected, shutting down socket." << endl;

	iResult = shutdown(ClientSocket, SD_BOTH);
	if (iResult == SOCKET_ERROR)
	{
		cerr << "Failed to shut down socket: " << WSAGetLastError() << endl;
		system("pause");
		closesocket(ClientSocket);
		WSACleanup();
		exit(1);
	}

	cout << "Existing program." << endl;
	system("pause");

	closesocket(ClientSocket);
	WSACleanup();
}