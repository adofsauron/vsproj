#include <Winsock2.h>
#include <stdio.h>

#pragma comment (lib, "ws2_32.lib")


#define iPort 6000

#pragma pack(push, 1)
struct Person
{
	char	name[20];
	int		age;
};
#pragma pack(pop)

void main()
{
	Person person;
	memset(&person, 0x00, sizeof(Person));
	char* sn = "Jame";
	memcpy(person.name, sn, strlen(sn));
	person.age = 14;


	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return;
	}


	if (LOBYTE(wsaData.wVersion) != 1 ||
		HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup();
		return;
	}

	// socket
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(iPort);

	// connect
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	

	char* str = new char(sizeof(Person));

	person.age = htonl(person.age);

	memcpy(str, &person, sizeof(Person));

	// send

	// send(sockClient,(const char*) &person, sizeof(Person), 0);

	for (int i = 0; i < 3; i++)
	{
		send(sockClient, str, sizeof(Person), 0);
		printf("name:%s, age:%d\n", person.name, ntohl(person.age));

		Sleep(1000);

	}

	// recv
	char recvBuf[100] = {0};
	recv(sockClient, recvBuf, 100, 0);
	printf("%s\n", recvBuf);

	closesocket(sockClient);
	WSACleanup();

	getchar();
}
