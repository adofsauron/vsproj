#include <windows.h>
//#include <Winsock2.h>
#include <stdio.h>
#include <time.h>

#pragma comment (lib, "ws2_32.lib")

DWORD WINAPI Client(LPVOID pM)
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return -1;
	}


	if (LOBYTE(wsaData.wVersion) != 1 ||
		HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup();
		return -1;
	}


	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

		
	// 发送给服务器
	char sendBuf[100];
	sprintf(sendBuf, "<from client TID=%d>", GetCurrentThreadId());
	send(sockClient, sendBuf, sizeof(sendBuf), 0);



	// 接受服务器端的数据
	char recvBuf[100];
	recv(sockClient, recvBuf, 100, 0);
	printf("<CLIENT> <TID>=[%d] %s\n", GetCurrentThreadId(), recvBuf);

	Sleep(2000);


	closesocket(sockClient);
	WSACleanup();
	
	return 0;
}


DWORD WINAPI Server(LPVOID pM)
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return -1;
	}

	if (LOBYTE(wsaData.wVersion) != 1 ||
		HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup();
		return -1;
	}

	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	listen(sockSrv, 5);

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);

	static int num = 0;
	while (1)
	{
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);

		char sendBuf[100];
		sprintf(sendBuf, "client_ip %s SERVER STID=%d",
			inet_ntoa(addrClient.sin_addr), GetCurrentThreadId());

		send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);

		char recvBuf[100];
		recv(sockConn, recvBuf, 100, 0);
		printf("<SERVER> <TID>=[%d] num=[%d] %s\n", GetCurrentThreadId(),  num++, recvBuf);
		closesocket(sockConn);
	}

	
	return 0;
}


//子线程函数
DWORD WINAPI ThreadFun(LPVOID pM)
{
	printf("子线程的线程ID号为：%d\n\n", GetCurrentThreadId());
	return 0;
}

//主函数，所谓主函数其实就是主线程执行的函数。
int main()
{
	

#if 0
	for (int i = 0; i < 3; i++)
	{
		HANDLE handle = CreateThread(NULL, 0, ThreadFun, NULL, 0, NULL);
		WaitForSingleObject(handle, INFINITE);
		printf("\n");
	}
#endif

	HANDLE handleA = NULL;
//	HANDLE handleB = NULL;


	handleA = CreateThread(NULL, 0,  Server, NULL, 0, NULL);
//	WaitForSingleObject(handleA, INFINITE);

	for (int i = 0; i < 3; i++)
	{
		HANDLE handleB = CreateThread(NULL, 0, Client, NULL, 0, NULL);
	}
		
//	WaitForSingleObject(handleB, INFINITE);

	getchar();
	return 0;
}