#include "TCP.h"
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")

int TCPConnectToServer(_In_ const char* server, _Out_ SOCKET* out_s){
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	int iResult;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(server, DEFAULT_TCP_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			return 1;
		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		return 1;
	}

	(*out_s) = ConnectSocket;

	return 0;
}

int TCPSend(SOCKET s, DataVector& data){
	int iResult = 0;
	size_t size = data.size();
	iResult = send(s, (const char*)&size, sizeof(size), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		return 0;
	}
	iResult = send(s, data.data(), data.size(), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		return 0;
	}
	return iResult;
}

int TCPShutdown(SOCKET s){
	int iResult = shutdown(s, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(s);
		return 1;
	}
	return 0;
}

int TCPReceive(SOCKET s, DataVector& data){
	int iResult = 0;
	size_t size = 0;
	iResult = recv(s, (char*)&size, sizeof(size), 0);
	if (iResult <= 0){
		return 1;
	}
	char* buf = new char[size];
	iResult = recv(s, buf, size, 0);
	if (iResult <= 0){
		return 1;
	}
	data.clear();
	for (int i = 0; i < size; i++)
	{
		data.push_back(buf[i]);
	}
	delete[] buf;
	return 0;
}

int TCPSetupServer(_Out_ SOCKET* listenSocket){

	SOCKET ListenSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	int iResult = getaddrinfo(NULL, DEFAULT_TCP_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		return 1;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		return 1;
	}

	*listenSocket = ListenSocket;
	return 0;
}

SOCKET TCPAcceptSocket(SOCKET ListenSocket){
	// Accept a client socket
	SOCKET ClientSocket = INVALID_SOCKET;
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		return INVALID_SOCKET;
	}
	return ClientSocket;
}