#define PROTOBUF_USE_DLLS
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _SCL_SECURE_NO_WARNINGS
#include <WinSock2.h>

// this is our proto of foo
#include "foo.pb.h"

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char **argv)
{
	SOCKET hSocket;
	SOCKADDR_IN addr;

	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(5555);

	// initialise a foo and set some properties
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	prototest::Foo foo;
	foo.set_id(4);
	foo.set_bar("narf");

	// serialise to string, this one is obvious ; )
	std::string buf;
	foo.SerializeToString(&buf);

	hSocket = socket(PF_INET, SOCK_DGRAM, 0);

	if (connect(hSocket, (SOCKADDR *)&addr, sizeof(addr)) == SOCKET_ERROR)
		printf("connect() error!");
	   send(hSocket, buf.data(), buf.size(), 0);

    closesocket(hSocket);

    return 0;
}