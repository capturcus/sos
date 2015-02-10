#pragma once

#define NOMINMAX //tak kazali

#include "Common.h"
#include "TCP.h"
#include <Windows.h>

#ifndef NDEBUG
#define assert(x) if(!(x))__debugbreak();
#else
#define assert(x) if(!(x)){throw new FlatException();}
#endif

DataVector& operator+=(DataVector& d1, const DataVector& d2);
const DataVector operator+(const DataVector& d1, const DataVector& d2);
DataVector makeDataVector(const char* cstr);
DataVector makeDataVector(const std::string& str);
std::ostream& operator<<(std::ostream&, const DataVector& d);