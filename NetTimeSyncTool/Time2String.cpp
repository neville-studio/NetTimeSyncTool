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
wstring FileTime2SystemTime(FILETIME fileTime) {
    SYSTEMTIME systemTime = {};
    FILETIME localFileTime = {};
    FileTimeToLocalFileTime(&fileTime, &localFileTime);
    //cout << localFileTime.dwHighDateTime;
    int rrr = FileTimeToSystemTime(&localFileTime, &systemTime);
    return to_wstring(systemTime.wYear) + L"/" + to_wstring(systemTime.wMonth) + L"/" + to_wstring(systemTime.wDay)
        + L" " + to_wstring(systemTime.wHour) + L":" + pluszero(systemTime.wMinute) + L":" + pluszero(systemTime.wSecond)
        ;// +L"." + pluszero(systemTime.wMilliseconds / 10);
}

wstring TimeStamp2HMS(unsigned long long timestamp) {
    return to_wstring(timestamp / 3600000) + L":" + pluszero(timestamp / 60000 % 60) + L":" + pluszero(timestamp / 1000 % 60);// +L"." + pluszero(timestamp / 10 % 100);
}
        
