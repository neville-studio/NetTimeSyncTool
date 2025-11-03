/*
 * @Author: Neville Studio <2840772674@qq.com>
 * @Date: 2024-11-29 22:27:06
 * @Function: to convert time to string, include time stamp and file time.
 */
#include <string>
#include <Windows.h>
//#include <iostream>
using namespace std;
wstring pluszero(int s) {
    if (s < 10)return L"0" + to_wstring(s);
    else return to_wstring(s);
}
wstring plusdualzero(int s) {
    if (s < 100)return L"0" + to_wstring(s);
    else if (s < 10)return L"00" + to_wstring(s);
    else return to_wstring(s);
}
/**
 * @brief Convert FILETIME to SYSTEMTIME string
 *
 * @param fileTime the input FILETIME
 * @return wstring the converted SYSTEMTIME string format. format: YYYY/MM/DD HH:MM:SS (TIMEZONE UTC+00:00)
 */
wstring FileTime2SystemTime(FILETIME fileTime) {
    
    SYSTEMTIME systemTime = {};
    FILETIME localFileTime = {};
    SYSTEMTIME localSystemTime = {};
	FileTimeToSystemTime(&fileTime, &systemTime);                                // UTC time
	SystemTimeToTzSpecificLocalTime(NULL, &systemTime, &localSystemTime);         // Local time
	TIME_ZONE_INFORMATION timeZoneInfo = {};
	INT timeZoneResult = GetTimeZoneInformation(&timeZoneInfo);
    wstring timezoneInforesult;
    if (timeZoneResult == TIME_ZONE_ID_UNKNOWN || timeZoneResult == TIME_ZONE_ID_STANDARD)    // Standard Time Zone
    {
		wstring biasSign = timeZoneInfo.Bias <= 0 ? L"+" : L"-";
		int biasHours = abs(timeZoneInfo.Bias / 60);
		int biasMinutes = abs(timeZoneInfo.Bias % 60);
		timezoneInforesult = L"( UTC" + biasSign + pluszero(biasHours) + L":" + pluszero(biasMinutes) + L" " + timeZoneInfo.StandardName + L" )";
    }
    else if (timeZoneResult == TIME_ZONE_ID_DAYLIGHT)
	{
        wstring biasSign = timeZoneInfo.Bias <= 0 ? L"+" : L"-";
        int biasHours = abs(timeZoneInfo.Bias / 60);
        int biasMinutes = abs(timeZoneInfo.Bias % 60);
        timezoneInforesult = L"( UTC" + biasSign + pluszero(biasHours) + L":" + pluszero(biasMinutes) + L" " + timeZoneInfo.DaylightName + L" )";
    }
    else {
        timezoneInforesult = L"";
	}

    


    return to_wstring(localSystemTime.wYear) + L"/" + to_wstring(localSystemTime.wMonth) + L"/" + to_wstring(localSystemTime.wDay)
        + L" " + to_wstring(localSystemTime.wHour) + L":" + pluszero(localSystemTime.wMinute) + L":" + pluszero(localSystemTime.wSecond)
		+ L" " + timezoneInforesult;
        ;// +L"." + pluszero(systemTime.wMilliseconds / 10);
}

wstring TimeStamp2HMS(unsigned long long timestamp) {
    return to_wstring(timestamp / 3600000) + L":" + pluszero(timestamp / 60000 % 60) + L":" + pluszero(timestamp / 1000 % 60);// +L"." + pluszero(timestamp / 10 % 100);
}
        
