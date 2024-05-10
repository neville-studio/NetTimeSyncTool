#pragma once
#include <string>
using namespace std;
const unsigned int epoch = 0;
class NTPResult {
public:
	wstring fromIP;
	wstring serverName;
	unsigned long long timeStamp = 0;
	int status = -1;
	int versionNumber = 3;
	int leap = 0;
	unsigned long long updateTime = 0;
	wstring getTime();
	wstring getUpdateTime();
	wstring pluszero(int s);
	wstring plusdualzero(int s);
	
};
int getNTPTime(char* ntpServerName, NTPResult& NTPres);
