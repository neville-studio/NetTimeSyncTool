
#define WIN32_LEAN_AND_MEAN
#include "NtpClient.h"
#include <windows.h>
#include <winsock2.h>
//#include <>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <comdef.h>

#include<time.h>
// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
using namespace std;

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "123"
#pragma comment(lib, "Ws2_32.lib")
#define RECEIVER_ADDRESS "127.0.0.1"
//#define PORT 123

wstring pluszero(int s);
unsigned long long NTPtoUTCTimeStamp(unsigned long long ntpTimeStamp);
wstring transmitfromFileTime(FILETIME fileTime);
wstring transmitToIP(unsigned int ip);
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

	int returnPackageData(char* strSource) {
		*strSource = leap << 6 | versionNumber << 3 | mode;
		*(strSource + 1) = statum;
		*(strSource + 2) = poll;
		*(strSource + 3) = precision;
		for(int i = 0;i<4;i++)
			*(strSource + 4+i) = rootDelay & (0x000000ff<<((3-i)*8));
		for (int i = 0; i < 4; i++)
			*(strSource + 8 + i) = rootDescription & 0x000000ff << ((3 - i) * 8);
		for (int i = 0; i < 4; i++)
			*(strSource + 12 + i) = referenceIdentifier & 0x000000ff << ((3 - i) * 8);
		for (int i = 0; i < 8; i++)
			*(strSource + 16 + i) = referenceTimestamp & 0x00000000000000ffLL << ((7 - i) * 8);
		for (int i = 0; i < 8; i++)
			*(strSource + 24 + i) = originateTimestamp & 0x00000000000000ffLL << ((7 - i) * 8);
		for (int i = 0; i < 8; i++)
			*(strSource + 32 + i) = receiveTimestamp & 0x00000000000000ffLL << ((7 - i) * 8);
		for (int i = 0; i < 8; i++)
			*(strSource + 40 + i) = transmitTimestamp & 0x00000000000000ffLL << ((7 - i) * 8);
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
        return 0;
        
    };
};
//wstring timeStampToSystemTime(unsigned long long timeStamp);
//int main() {
//
//	NTPPackage ntpbase = NTPPackage();
//	ntpbase.versionNumber = 4;
//	char ntpPackage[49] = {};
//	int result = ntpbase.returnPackageData(ntpPackage);
//	WSAData wsadata;
//	SOCKET sendSocket;
//	SOCKADDR_IN receiverAddr;
//	int addrLength = 0;
//	int sendBufLength = 1024;
//	int ret = 0;
//
//	WSAStartup(MAKEWORD(2, 2), &wsadata);
//	sendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
//	if (SOCKET_ERROR == sendSocket) {
//		printf("Create Socket Error!");
//		goto exit;
//	}
//	
//
//
//	
//exit:
//	closesocket(sendSocket);
//	
//	return 0;
//}

int getNTPTime(char * ntpServerName, NTPResult &NTPres)
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
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        //printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;

    // Resolve the server address and port
    iResult = getaddrinfo(ntpServerName, "123", &hints, &result);
    if (iResult != 0) {
        //printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            //printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
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
    NTPres.serverName = _bstr_t(ntpServerName);
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {


            FILETIME endFileTime = {};
            GetSystemTimeAsFileTime(&endFileTime);
            //printf("Bytes received: %d\n", iResult);
            ///* for (int i = 0; i < 48; i++)
            // {
            //     printf("%x ", *(recvbuf + i));
            // }*/
            //printf("\n");
            NTPPackage ntpTransmit;
            ntpTransmit.transLateToUDPPackage(recvbuf);
       /*     printf("leap : %d\n", ntpTransmit.leap);
            printf("VersionNumber: %d\n", ntpTransmit.versionNumber);
            printf("mode: %d\n", ntpTransmit.mode);
            printf("statum: %d\n", ntpTransmit.statum);
            printf("poll: %d\n", ntpTransmit.poll);
            printf("precision: %u\n", ntpTransmit.precision);
            printf("rootDelay:%u\n", ntpTransmit.rootDelay);
            printf("rootDescription:%u\n", ntpTransmit.rootDescription);
            printf("referenceIdentifier:%u\n", ntpTransmit.referenceIdentifier);
            printf("referenceTimestamp: %llu\n", ntpTransmit.receiveTimestamp);
            printf("originateTimestamp: %llu\n", ntpTransmit.originateTimestamp);
            printf("receiveTimestamp: %llu\n", ntpTransmit.receiveTimestamp);
            printf("transmitTimestamp: %llu\n", ntpTransmit.transmitTimestamp);*/
            //time_t now;
            //wstring s = timeStampToSystemTime(ntpTransmit.receiveTimestamp);
            /*FILETIME t1 = { NTPtoUTCTimeStamp(ntpTransmit.receiveTimestamp)>>32, NTPtoUTCTimeStamp(ntpTransmit.receiveTimestamp) &&0xffffffff };
            FILETIME t2 = { NTPtoUTCTimeStamp(ntpTransmit.transmitTimestamp) >> 32, NTPtoUTCTimeStamp(ntpTransmit.transmitTimestamp) && 0xffffffff };*/
            unsigned long long t1 = ((unsigned long long)startFileTime.dwHighDateTime << 32) + ((unsigned long long)startFileTime.dwLowDateTime & 0xffffffff);
            unsigned long long t2 = ((unsigned long long)endFileTime.dwHighDateTime << 32) + ((unsigned long long)endFileTime.dwLowDateTime & 0xffffffff);
            unsigned long long currentTimeStamp = (t2 - t1 + NTPtoUTCTimeStamp(ntpTransmit.transmitTimestamp) - NTPtoUTCTimeStamp(ntpTransmit.receiveTimestamp)) / 2ULL + NTPtoUTCTimeStamp(ntpTransmit.transmitTimestamp);
            FILETIME currentTime = { }; 
            currentTime.dwHighDateTime = currentTimeStamp >> 32;
            //cout << currentTime.dwHighDateTime << endl;
            currentTime.dwLowDateTime = currentTimeStamp & 0xffffffff;
            
            
            /*cout << currentTimeStamp<<" "<<endFileTime.dwHighDateTime<<" "<<t2 << " " << t1 << " " << endl;
            cout << "From IP: " << transmitToIP(ntpTransmit.referenceIdentifier)<<endl;
            cout << "Final Time: " << transmitfromFileTime(currentTime) << endl;*/
           
            NTPres.leap = ntpTransmit.leap;
            NTPres.versionNumber = ntpTransmit.versionNumber;
            NTPres.fromIP = transmitToIP(ntpTransmit.referenceIdentifier);
            NTPres.updateTime = GetTickCount64();
            NTPres.timeStamp = currentTimeStamp;
            NTPres.status = 0;
            
            //time(&now);
            //printf("time:%lld", now);


        }
        else if (iResult == 0)
        {
            printf("Connection closed\n");
            closesocket(ConnectSocket);
            WSACleanup();
            NTPres.status = -12;
            return 1;
        }
        else
        {
            printf("recv failed with error: %d\n", WSAGetLastError());
            
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

wstring plusdualzero(int s);

//wstring timeStampToSystemTime(unsigned long long timeStamp)
//{
//    FILETIME fileTime = {};
//    FILETIME localFileTime = {};
//    unsigned long long utcTimeStamp = NTPtoUTCTimeStamp(timeStamp);
//    //unsigned long long utcTimeStamp = ((timeStamp & 0xffffffff00000000) >> 32) * 10000000 + 94354848000000000 + (timeStamp & 0xffffffff) * 232 / 100000;//116444736000000000L - 2208988800* 10000000 ;
//    fileTime.dwHighDateTime = (utcTimeStamp & 0xffffffff00000000)>>32;
//    fileTime.dwLowDateTime = (utcTimeStamp & 0xffffffff);
//    cout <<endl<<utcTimeStamp<<" " << fileTime.dwHighDateTime << " " << fileTime.dwLowDateTime << endl;
//    SYSTEMTIME systemTime = {};
//    FileTimeToLocalFileTime(&fileTime, &localFileTime);
//    int rrr = FileTimeToSystemTime(&localFileTime, &systemTime);
//    cout << rrr<<endl;
//    return to_wstring(systemTime.wYear) + "/" + to_wstring(systemTime.wMonth) + "/" + to_wstring(systemTime.wDay) 
//        +" " + to_wstring(systemTime.wHour) + ":" + pluszero(systemTime.wMinute) + ":" + pluszero(systemTime.wSecond)
//        +"." + plusdualzero(systemTime.wMilliseconds);
//
//}
wstring transmitfromFileTime(FILETIME fileTime) {
    SYSTEMTIME systemTime = {};
    FILETIME localFileTime = {};
    FileTimeToLocalFileTime(&fileTime, &localFileTime);
    //cout << localFileTime.dwHighDateTime;
    int rrr = FileTimeToSystemTime(&localFileTime, &systemTime);
    //cout << fileTime.dwHighDateTime<<" "<<fileTime.dwLowDateTime<<" " << localFileTime.dwHighDateTime << " " << localFileTime.dwLowDateTime;
    //cout << rrr << endl;
    if (rrr == 0)return to_wstring(GetLastError());
    return to_wstring(systemTime.wYear) + L"/" + to_wstring(systemTime.wMonth) + L"/" + to_wstring(systemTime.wDay)
        + L" " + to_wstring(systemTime.wHour) + L":" + pluszero(systemTime.wMinute) + L":" + pluszero(systemTime.wSecond)
        + L"." + plusdualzero(systemTime.wMilliseconds);
}
wstring NTPResult::pluszero(int s) {
    if (s < 10)return L"0" + to_wstring(s);
    else return to_wstring(s);
}
wstring NTPResult::plusdualzero(int s) {
    if (s < 100)return L"0" + to_wstring(s);
    else if(s < 10)return L"00" + to_wstring(s);
    else return to_wstring(s);
}
unsigned long long NTPtoUTCTimeStamp(unsigned long long ntpTimeStamp) {
    return ((ntpTimeStamp & 0xffffffff00000000ULL) >> 32) * 10000000 + 94354848000000000ULL + (ntpTimeStamp & 0xffffffff) * 232 / 100000;//116444736000000000L - 2208988800* 10000000 ;
}
wstring transmitToIP(unsigned int ip) {
    return to_wstring((ip & 0xff000000) >> 24) + L"." + to_wstring((ip & 0x00ff0000) >> 16) + L"." + to_wstring((ip & 0x0000ff00) >> 8) + L"." + to_wstring((ip & 0x000000ff));
}

wstring NTPResult::getTime() {
    FILETIME filetime;
    filetime.dwHighDateTime = this->timeStamp >> 32;
    filetime.dwLowDateTime = this->timeStamp & 0xffffffff;
    return transmitfromFileTime(filetime);
}
wstring NTPResult::getUpdateTime() {
    return to_wstring(updateTime/3600000) + L":" + pluszero(updateTime/60000%60) + L":" + pluszero(updateTime/1000%60) + L"." + plusdualzero(updateTime%1000);
}