
/*
 * @Author: Neville Studio <2840772674@qq.com>
 * @Date: 2024-11-29 22:31:00
 * @Function: NTP logics(socket).
 */


#define WIN32_LEAN_AND_MEAN
#include "NtpClient.h"
#include <windows.h>
#include <winsock2.h>
//#include <>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <comdef.h>
//#include <fmt/format.h>
#include<time.h>
// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
//using namespace std;

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "123"
#pragma comment(lib, "Ws2_32.lib")
#define RECEIVER_ADDRESS "127.0.0.1"
#define RECEIVER_ADDRESS_IPV6 "::1"
//#define PORT 123

std::wstring pluszero(int s);
unsigned long long NTPtoUTCTimeStamp(unsigned long long ntpTimeStamp);
std::wstring transmitfromFileTime(FILETIME fileTime);
std::wstring transmitToIP(unsigned int ip);
std::wstring ConvertToASCII(unsigned int sourcename);
std::wstring transmitToIPV6(unsigned int ip);
class NTPPackage {
public:
	unsigned char leap = 0;
	unsigned char versionNumber = 4;
	unsigned char mode=3;
	unsigned char statum=0;
	unsigned char poll=0;
	unsigned char precision=0;
	unsigned int rootDelay=0;
	unsigned int rootDescription=0;
	unsigned int referenceIdentifier=0;
	unsigned long long referenceTimestamp=0;
	unsigned long long originateTimestamp=0;
	unsigned long long receiveTimestamp=0;
	unsigned long long transmitTimestamp=0;
    // As of NTP version 4 defination, we added epoch variable. If the Seconds variable is larger than the Others, we will added it.
    // unsigned int epoch = 0;

	int returnPackageData(char* strSource) {
		*strSource = leap << 6 | versionNumber << 3 | mode;
		*(strSource + 1) = statum;
		*(strSource + 2) = poll;
		*(strSource + 3) = precision;
		for(int i = 0;i<4;i++)
			*(strSource + 4+i) = (rootDelay & (0x000000ff<<((3-i)*8)))>>  ((3 - i) * 8);
		for (int i = 0; i < 4; i++)
			*(strSource + 8 + i) = (rootDescription & (0x000000ff << ((3 - i) * 8)))>>  ((3 - i) * 8);
		for (int i = 0; i < 4; i++)
			*(strSource + 12 + i) = (referenceIdentifier & (0x000000ff << ((3 - i) * 8)))>>((3 - i) * 8);
		for (int i = 0; i < 8; i++)
			*(strSource + 16 + i) = (referenceTimestamp & (0x00000000000000ffLL << ((7 - i) * 8)))>> ((7 - i) * 8);
		for (int i = 0; i < 8; i++)
			*(strSource + 24 + i) = (originateTimestamp & (0x00000000000000ffLL << ((7 - i) * 8))) >> ((7 - i) * 8);
		for (int i = 0; i < 8; i++)
			*(strSource + 32 + i) = (receiveTimestamp & (0x00000000000000ffLL << ((7 - i) * 8))) >> ((7 - i) * 8);
        FILETIME ft;
        GetSystemTimeAsFileTime(&ft);
        unsigned long long highTime = ft.dwHighDateTime;
        unsigned long long lowTime = ft.dwLowDateTime;
        unsigned long long sec = ((highTime << 32) + lowTime - 94354848000000000ULL)/10000000;
        unsigned long long lowsec = ((highTime << 32) + lowTime - 94354848000000000ULL) % 10000000;
        transmitTimestamp = (sec<<32) + lowsec*100000/232;
        
		for (int i = 0; i < 8; i++)
			*(strSource + 40 + i) = (transmitTimestamp & (0x00000000000000ffLL << ((7 - i) * 8))) >> ((7 - i) * 8);
		return 0;
	};
    int transLateToUDPPackage(char* result)
    {
        leap = ((unsigned)(*(result)) & 0xC0)>>6;
        versionNumber = ((unsigned)(*(result)) & 0x38 )>> 3;
        mode = *(result) & 0x7;
        statum = (unsigned)*(result + 1);
        poll = (unsigned)*(result + 2);
        precision = (unsigned)*(result + 3);
        rootDelay = 0;
        for (int i = 4; i < 8; i++)
        {
            rootDelay = rootDelay | (((unsigned int) * (result + i)) & 0xff) << ((7 - i) * 8);
        }
        rootDescription = 0;
        for (int i = 8; i < 12; i++)
        {
            rootDescription = rootDescription | (((unsigned int)*(result + i)) & 0xff) << ((11 - i) * 8);
        }
        referenceIdentifier = 0;
        for (int i = 12; i < 16; i++)
        {
            referenceIdentifier = referenceIdentifier | (((unsigned int)*(result + i)) & 0xff) << ((15 - i) * 8);
        }
        //= (unsigned)*(result + 12) << 24 | (unsigned)*(result + 13) << 16 | (unsigned)*(result + 14) << 8 | (unsigned)*(result + 15);
        referenceTimestamp = 0;
        for (int i = 16; i < 24; i++)
        {
            referenceTimestamp = referenceTimestamp | (((unsigned long long)*(result + i))&0xff) << ((23 - i) * 8);
        }
        originateTimestamp = 0;
        for (int i = 24; i < 32; i++)
        {
            originateTimestamp = originateTimestamp | (((unsigned long long) * (result + i)) & 0xff) << ((31 - i) * 8);
        }
        receiveTimestamp=0;
        for (int i = 32; i < 40; i++)
        {
            receiveTimestamp = receiveTimestamp | (((unsigned long long) * (result + i)) & 0xff) << ((39 - i) * 8);
        }
        transmitTimestamp=0;
        for (int i = 40; i < 48; i++)
        {
            transmitTimestamp = transmitTimestamp | (((unsigned long long) * (result + i)) & 0xff)  << ((47 - i) * 8);
        }
        if (max(originateTimestamp >> 32, receiveTimestamp >> 32) - min(originateTimestamp >> 32, receiveTimestamp >> 32) & 0x80000000) // epoch function.
        {
            
        }
        return 0;
        
    };
    NTPPackage() {
       
    }
};

int getNTPTime(char* ntpServerName, NTPResult& NTPres) {
    int result = getNTPTime(ntpServerName, NTPres, 4);
	if (result >= 0 && NTPres.status != -1)
	{
		return result;
	}
    result = getNTPTime(ntpServerName, NTPres, 6);
    if (result >= 0 && NTPres.status != -1)
    {
        return result;
    }
    return result;
}

/**
 * @brief Get the NTP Time object
 *
 * @param ntpServerName the remote NTP server name
 * @param NTPres the NTP result object
 * @param IPversion the IP version
 * @return int the status code
 */
int getNTPTime(char * ntpServerName, NTPResult &NTPres, int IPversion)
{
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    NTPPackage ntpbase = NTPPackage();
    ntpbase.versionNumber = 3;
    char sendbuf[49] = {};
    int res = ntpbase.returnPackageData(sendbuf);
    
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;

    // Validate the parameters
   /* if (argc != 2) {
        printf("usage: %s server-name\n", argv[0]);
        return 1;
    }*/

    // Initialize Winsock
    NTPres.serverName = _bstr_t(ntpServerName);
    NTPres.fromIP = L"";
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        //printf("WSAStartup failed with error: %d\n", iResult);
        return iResult;
    }

    ZeroMemory(&hints, sizeof(hints));
	if (IPversion == 6)
		hints.ai_family = AF_INET6;
	else
		hints.ai_family = AF_INET;
    //hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    //hints.ai_protocol = IPPROTO_IPV4;
    hints.ai_protocol = IPPROTO_UDP;

    // Resolve the server address and port
    iResult = getaddrinfo(ntpServerName, "123", &hints, &result);
    if (iResult != 0) {
        //printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return iResult;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            //printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return iResult;
        }
        DWORD timeout = 5000;

        setsockopt(ConnectSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
        setsockopt(ConnectSocket, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof(timeout));
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
        WSACleanup();
        return 1;
    }

    // Send an initial buffer
    iResult = send(ConnectSocket, sendbuf, 48, 0);
    //printf("%ld\n", (int)strlen(sendbuf));
    if (iResult == SOCKET_ERROR) {
        //printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }
    FILETIME startFileTime;
    GetSystemTimeAsFileTime(&startFileTime);
    //printf("Bytes Sent: %ld\n", iResult);

    // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        //printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    // Receive until the peer closes the connection
    //do {
    iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
    if (iResult > 0) {


        FILETIME endFileTime = {};
        GetSystemTimeAsFileTime(&endFileTime);
        NTPPackage ntpTransmit;
        ntpTransmit.transLateToUDPPackage(recvbuf);

        unsigned long long t1 = ((unsigned long long)startFileTime.dwHighDateTime << 32) + ((unsigned long long)startFileTime.dwLowDateTime & 0xffffffff);
        unsigned long long t2 = ((unsigned long long)endFileTime.dwHighDateTime << 32) + ((unsigned long long)endFileTime.dwLowDateTime & 0xffffffff);
        unsigned long long currentTimeStamp = (t2 - t1 + NTPtoUTCTimeStamp(ntpTransmit.transmitTimestamp) - NTPtoUTCTimeStamp(ntpTransmit.receiveTimestamp)) / 2ULL + NTPtoUTCTimeStamp(ntpTransmit.transmitTimestamp);
        FILETIME currentTime = { }; 
        currentTime.dwHighDateTime = currentTimeStamp >> 32;
        //cout << currentTime.dwHighDateTime << endl;
        currentTime.dwLowDateTime = currentTimeStamp & 0xffffffff;
   
           
        NTPres.leap = ntpTransmit.leap;
        NTPres.versionNumber = ntpTransmit.versionNumber;
        if (ntpTransmit.statum > 1) {
            if (IPversion == 4)
                NTPres.fromIP = transmitToIP(ntpTransmit.referenceIdentifier);
            else
                NTPres.fromIP = transmitToIPV6(ntpTransmit.referenceIdentifier);
        }
        else {
            NTPres.fromIP = ConvertToASCII(ntpTransmit.referenceIdentifier);
        }
        NTPres.updateTime = GetTickCount64();
        NTPres.timeStamp = currentTimeStamp;
        NTPres.status = 0;
    }
    else if (iResult == 0)
    {
        closesocket(ConnectSocket);
        WSACleanup();
        NTPres.status = -12;
        return 1;
    }
    else
    {
        NTPres.status = WSAGetLastError();
        closesocket(ConnectSocket);
        WSACleanup();
        return iResult;
    }

    //} while (iResult > 0);

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();
    return 0;
}

std::wstring plusdualzero(int s);


std::wstring transmitfromFileTime(FILETIME fileTime) {
    SYSTEMTIME systemTime = {};
    FILETIME localFileTime = {};
    FileTimeToLocalFileTime(&fileTime, &localFileTime);
    //cout << localFileTime.dwHighDateTime;
    int rrr = FileTimeToSystemTime(&localFileTime, &systemTime);
    //cout << fileTime.dwHighDateTime<<" "<<fileTime.dwLowDateTime<<" " << localFileTime.dwHighDateTime << " " << localFileTime.dwLowDateTime;
    //cout << rrr << endl;
    if (rrr == 0)return std::to_wstring(GetLastError());
    return std::to_wstring(systemTime.wYear) + L"/" + std::to_wstring(systemTime.wMonth) + L"/" + std::to_wstring(systemTime.wDay)
        + L" " + std::to_wstring(systemTime.wHour) + L":" + pluszero(systemTime.wMinute) + L":" + pluszero(systemTime.wSecond)
        + L"." + plusdualzero(systemTime.wMilliseconds);
}
std::wstring NTPResult::pluszero(int s) {
    if (s < 10)return L"0" + std::to_wstring(s);
    else return std::to_wstring(s);
}
std::wstring NTPResult::plusdualzero(int s) {
    if (s < 100)return L"0" + std::to_wstring(s);
    else if(s < 10)return L"00" + std::to_wstring(s);
    else return std::to_wstring(s);
}
unsigned long long NTPtoUTCTimeStamp(unsigned long long ntpTimeStamp) {
    int flag = 0;
    if (((ntpTimeStamp & 0xffffffff00000000ULL) >> 32) < 0x80000000) flag = 1;
    return ((ntpTimeStamp & 0xffffffff00000000ULL) >> 32) * 10000000 + 94354848000000000ULL + (ntpTimeStamp & 0xffffffff) * 232 / 100000 + flag * 0x100000000*10000000 + epoch * 0x100000000*1000;//116444736000000000L - 2208988800* 10000000 ;
}
std::wstring transmitToIP(unsigned int ip) {
    return std::to_wstring((ip & 0xff000000) >> 24) + L"." + std::to_wstring((ip & 0x00ff0000) >> 16) + L"." + std::to_wstring((ip & 0x0000ff00) >> 8) + L"." + std::to_wstring((ip & 0x000000ff));
}
std::wstring transmitToIPV6(unsigned int ip) {
    std::wstringstream wss;
    wss << L"["; // Start of IPv6 address
    wss << std::hex << std::setw(4) << std::setfill(L'0') << ((ip & 0xFF000000) >> 24);
    wss << L":";
    wss << std::hex << std::setw(4) << std::setfill(L'0') << ((ip & 0x00FF0000) >> 16);
    wss << L":...]"; // End of IPv6 address
    return wss.str();
}
std::wstring ConvertToASCII(unsigned int sourcename) {
    std::wstring result;
    result += static_cast<wchar_t>((sourcename & 0xFF000000) >> 24);
    result += static_cast<wchar_t>((sourcename & 0x00FF0000) >> 16);
    result += static_cast<wchar_t>((sourcename & 0x0000FF00) >> 8);
    result += static_cast<wchar_t>(sourcename & 0x000000FF);
    return result;
}

std::wstring NTPResult::getTime() {
    FILETIME filetime;
    filetime.dwHighDateTime = this->timeStamp >> 32;
    filetime.dwLowDateTime = this->timeStamp & 0xffffffff;
    return transmitfromFileTime(filetime);
}
std::wstring NTPResult::getUpdateTime() {
    return std::to_wstring(updateTime/3600000) + L":" + pluszero(updateTime/60000%60) + L":" + pluszero(updateTime/1000%60) + L"." + plusdualzero(updateTime%1000);
}
