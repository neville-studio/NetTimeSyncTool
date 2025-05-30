#pragma once
#include <string>
//using namespace std;
const unsigned int epoch = 0;
class NTPResult {
public:
	std::wstring fromIP;
	std::wstring serverName;
	unsigned long long timeStamp = 0;
	int status = -1;
	int versionNumber = 3;
	int leap = 0;
	unsigned long long updateTime = 0;
	std::wstring getTime();
	std::wstring getUpdateTime();
	std::wstring pluszero(int s);
	std::wstring plusdualzero(int s);
	
};
int getNTPTime(char* ntpServerName, NTPResult& NTPres);
int getNTPTime(char* ntpServerName, NTPResult& NTPres, int IPversion);
