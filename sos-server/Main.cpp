#include <iostream>

#include "..\sos-common\FlatShooterCommon.h"

#pragma comment(lib, "..\\sos\\Debug\\sos-common.lib")

int main() {

	initializeWinsock();

	SOCKET s;
	TCPSetupServer(&s);

	while (true)
	{
		SOCKET ClientSocket = TCPAcceptSocket(s);
		DataVector v;
		TCPReceive(ClientSocket, v);
		DataVector v2 = makeDataVector(" in my ass");
		v += v2;
		TCPSend(ClientSocket, v);
	}
}