#pragma once
#include <vector>
#include "NtpClient.h"
//using namespace std;
class GlobalData {
public:
	std::vector<NTPResult> globalData;
	GlobalData();
	std::vector <std::string> servers;
	~GlobalData();
};