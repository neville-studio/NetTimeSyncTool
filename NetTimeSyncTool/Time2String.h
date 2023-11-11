#pragma once
#include <string>
#include <Windows.h>
std::wstring FileTime2SystemTime(FILETIME fileTime);
std::wstring TimeStamp2HMS(unsigned long long timestamp);