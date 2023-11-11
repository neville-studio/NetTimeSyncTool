#pragma once
#include <vector>
#include "NtpClient.h"
using namespace std;
class GlobalData {
public:
	vector<NTPResult> globalData;
	GlobalData();
};