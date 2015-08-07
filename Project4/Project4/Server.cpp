#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <time.h>
#include <string>
#include <Filter.h>

using namespace std;

#define InternetAddr "127.0.0.1"
#define iPort 6000

#pragma comment(lib, "ws2_32.lib")

#pragma pack(push, 1)
struct Person
{
	char name[20];
	int age;
};
#pragma pack(pop)


int initWinSock()
{
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(1, 1);
	if (0 == WSAStartup(wVersionRequested, &wsaData))
	{
		cout << "RUN-MSG:Sucess to connect to the lib of socket!" << endl;
		return 0;
	}
	else
	{
		cout << "ERR-MSG:Failed to connect to the lib of socket!" << endl;
		return -1;
	}
	//wVersionRequested是我们要求使用的WinSock的版本。
}

void* ServerThread(void* para)
{
	return NULL;
}

void RecvFromSocket(SOCKET socket)
{

}

int main(int argc, char *argv[])
{
#ifdef _WIN32
	cout << "win32!" << endl;
	if (0 != initWinSock())
		return -1;
#else
	cout << "Linux!" << endl;
#endif

	int sock, client_sock;
	int sock_arr[64];
	static int s_num_socket = 0;
	short sport = iPort;
	string sip = "127.0.0.1";

	if (argc == 2)
		sport = atoi(argv[1]);
	if (argc == 3)
	{
		sport = atoi(argv[1]);
		sip = argv[2];
	}
	cout << "ip is " << sip << ", port is " << sport << endl;

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in sockaddr, client_addr;
	
	int error_code = 0;
	int len, l;
	string strread = "";


	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY); //inet_addr("127.0.0.1");//0;//;//inet_addr(INADDR_ANY);
	sockaddr.sin_port = htons(sport);

	if ((SOCKET_ERROR == bind(sock, (struct sockaddr *)&sockaddr, sizeof(struct sockaddr_in))))
	{
		cout << "ERR-MSG:bind error! :" << error_code << endl;
		cout << WSAGetLastError() << endl;
		system("PAUSE");
		return -2;
	}
	else
		cout << "RUN-MSG:bind sucess!" << endl;


	if (SOCKET_ERROR == (error_code = listen(sock, 20)))
	{
		cout << "ERR-MSG:listen error! :" << error_code << endl;
		system("PAUSE");
		return -3;
	}
	else
		cout << "RUN-MSG:listen success!the port is:" << sport << endl;

	u_long mode = 1;
	ioctlsocket(sock, FIONBIO, &mode);
	// ioctlsocket(sock, FIONBIO,(u_long FAR*) &mode);//设置非阻塞的socket
	char opt = 1;
//	 setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	
	
	sock_arr[s_num_socket++] = sock;
	char buffer[256];
	memset(buffer, 0, 256);
	len = sizeof(struct sockaddr_in);

	int i;
	

	fd_set fd, newfd;
	fd_set writefd, excpfd;

	
	FD_ZERO(&fd);
	FD_ZERO(&writefd);
	FD_ZERO(&excpfd);

	FD_SET(sock, &fd);

	newfd = fd;

	struct timeval tval;
	tval.tv_sec = 0;
	tval.tv_usec = 0;


	while (1)
	{
		int ret = select(0, &newfd, &writefd, &excpfd, &tval);

		if (ret < 0)
		{
			cout << "select error! " << WSAGetLastError() << endl;
			system("PAUSE");
			return -1;
		}

		for (i = 0; i < s_num_socket; i++)
		{

			if (FD_ISSET(sock_arr[i], &newfd))
			{
				cout << "i is " << i << endl;

				if (sock_arr[i] == sock)
				{
					cout << "RUN-MSG:it's me!" << endl;
					if ((client_sock = accept(sock, (struct sockaddr*)&client_addr, &len)) != INVALID_SOCKET)
					{
						cout << "RUM-MSG:a new client!" << endl;
						FD_SET(client_sock, &newfd);
						sock_arr[s_num_socket++] = client_sock;
						memset(buffer, 0x00, 256);
					}
				}
				else
				{
					//cout << "recv..." << endl;

					int ret = recv(sock_arr[i], buffer, 256, 0);
									
					if (ret > 1) // 有数据传送
					{
						Person person;
						memcpy(&person, buffer, sizeof(Person));
						person.age = ntohl(person.age);
						cout << "name:" << person.name << ",age:" << person.age << endl;

						const char* back = "0xAAback0x55\r\n";
						send(client_sock, back, strlen(back), 0);
					}
					else // 其他情况关闭连接
					{
						// Client socket closed
						cout << "RUN-MSG:Client socket " << sock_arr[i] << "has close" << endl;
						if (sock_arr[i] != INVALID_SOCKET)
						{
							FD_CLR(sock_arr[i], &newfd);
							closesocket(sock_arr[i]);
						}
						cout << "RUN-MSG:Remove client socket!" << sock_arr[i] << " success!" << endl;
						sock_arr[i--] = sock_arr[--s_num_socket];
					} 
				}
			}
		}


		FD_ZERO(&newfd);

		//重新置newfd状态；
		for (i = 0; i < s_num_socket; i++)
			FD_SET(sock_arr[i], &newfd);

		Sleep(1000);

		// 在此执行业务逻辑的处理
		cout << "nothing..." << endl;

//		closesocket(sock);
//		WSACleanup();
//		system("PAUSE");
//		return EXIT_SUCCESS;
	}

}
