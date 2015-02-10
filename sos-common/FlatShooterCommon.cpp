#include "FlatShooterCommon.h"
#include <cstdio>
#include <iostream>

int initializeWinsock() {
	WSADATA wsaData;
	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	return iResult;
}

DataVector& operator+=(DataVector& d1, const DataVector& d2){
	for (char c : d2){
		d1.push_back(c);
	}
	return d1;
}

const DataVector operator+(const DataVector& d1, const DataVector& d2){
	DataVector res;
	res += d1;
	res += d2;
	return res;
}

DataVector makeDataVector(const char* cstr){
	return DataVector(cstr, cstr + (int)strlen(cstr));
}

DataVector makeDataVector(const std::string& str){
	return DataVector(str.data(), str.data() + str.size());
}

std::ostream& operator<<(std::ostream& out, const DataVector& d){
	for (auto it = d.begin(); it != d.end(); it++){
		out << *it << " ";
	}
	return out;
}