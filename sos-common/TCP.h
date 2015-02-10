#pragma once
#include "Common.h"

typedef __w64 unsigned int SOCKET;

int initializeWinsock();
int TCPConnectToServer(const char* server, SOCKET* out_s);
int TCPSend(SOCKET s, DataVector& data);
int TCPShutdown(SOCKET s);
int TCPReceive(SOCKET s, DataVector& data);
int TCPSetupServer(SOCKET* listenSocket);
SOCKET TCPAcceptSocket(SOCKET ListenSocket);
