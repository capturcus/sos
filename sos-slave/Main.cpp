#include <iostream>
#include "..\sos-common\FlatShooterCommon.h"

#pragma comment(lib, "..\\sos\\Debug\\sos-common.lib")

int main() {

	initializeWinsock();

	SOCKET s;
	TCPConnectToServer("localhost", &s);
	TCPSend(s, makeDataVector("planet of the apes"));
	DataVector v;
	TCPReceive(s, v);
	std::cout << v;
}