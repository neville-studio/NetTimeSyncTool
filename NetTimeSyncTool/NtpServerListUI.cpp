#include <Windows.h>
#include <CommCtrl.h>
#include "NtpServerListUI.h"
#include "resource.h"
#include "NtpClient.h"
#include <string>
#include "Time2String.h"
#define ITEM_COUNT   100
#define MAX_LOADSTRING 50
HWND CreateNTPServerList(HINSTANCE hInst, HWND hWnd)
{
    DWORD       dwStyle;
    HWND        hwndListView;
    BOOL        bSuccess = TRUE;

    dwStyle = //WS_TABSTOP |
        WS_CHILD | WS_CLIPCHILDREN |
        WS_BORDER |
        WS_VISIBLE |
         LVS_SINGLESEL|
        LVS_REPORT ;

    hwndListView = CreateWindowEx(LVS_EX_DOUBLEBUFFER ,  // ex style
        WC_LISTVIEW,                     // class name - defined in commctrl.h
        TEXT(""),                        // dummy text
        dwStyle,                         // style
        50,                              // x position
        100,                             // y position
        600,                             // width
        250,                             // height
        hWnd,                            // parent
        (HMENU)110,                       // ID
        hInst,                           // instance
        NULL);                           // no extra data
    ListView_SetExtendedListViewStyleEx(hwndListView, LVS_EX_DOUBLEBUFFER, LVS_EX_DOUBLEBUFFER);    // This code is to enable ListView's Double 
    //ListView_SetBkColor(hwndListView, CLR_NONE);
    //ListView_SetTextBkColor(hwndListView, CLR_NONE);
    return hwndListView;
}

BOOL InitListView(HINSTANCE hInstance,HWND hwndListView)
{
    LV_COLUMN   lvColumn;
    int         i;
    WCHAR ServerNameString[MAX_LOADSTRING];                 
    WCHAR ServerIPString[MAX_LOADSTRING];            
    WCHAR ServerTimeString[MAX_LOADSTRING];                                                            // system time control
    WCHAR ServerStatusString[MAX_LOADSTRING];                                                          // network time string
    LoadStringW(hInstance, IDS_SERVERNAME, ServerNameString, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_IPADDR, ServerIPString, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_TIME, ServerTimeString, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_STATUS, ServerStatusString, MAX_LOADSTRING);
    TCHAR *szString[4] = { ServerNameString, ServerIPString, ServerTimeString,ServerStatusString };

    //empty the list
    ListView_DeleteAllItems(hwndListView);

    //initialize the columns
    lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvColumn.fmt = LVCFMT_LEFT;
    int width[4] = { 150,150,180,120 };
    
    for (i = 0; i < 4; i++)
    {
        lvColumn.cx = width[i];
        lvColumn.pszText = szString[i];
        ListView_InsertColumn(hwndListView, i, &lvColumn);
    }

    InsertListViewItems(hwndListView);

    return TRUE;
}
BOOL InsertListViewItems(HWND hwndListView)
{
    //empty the list
    ListView_DeleteAllItems(hwndListView);

    return TRUE;
}

BOOL InsertNTPViewItem(HWND hWndListView,NTPResult NTPitem)
{
    
    LV_ITEM item;
    WCHAR serverName[256];
    WCHAR serverIP[16]=L"";
    wcscpy_s(serverName,wcslen(NTPitem.serverName.c_str())+1, NTPitem.serverName.c_str());
    //OutputDebugString(to_wstring(NTPitem.fromIP.size()).c_str());
    wcscpy_s(serverIP, NTPitem.fromIP.size()+1, NTPitem.fromIP.c_str());
    item.mask = LVIF_TEXT;
    item.iItem = ListView_GetItemCount(hWndListView);
    item.iSubItem = 0;
    item.pszText = serverName;
    ListView_InsertItem(hWndListView, &item);
    item.iSubItem = 1;
    item.pszText = serverIP;
    ListView_SetItem(hWndListView, &item);
    UpdateWindow(hWndListView);
    return TRUE;
}
BOOL UpdateNTPTime(HWND hWndListView, int num, NTPResult res)
{
    LV_ITEM item;
    item.mask = LVIF_TEXT;
    item.iItem = num;
    item.iSubItem = 2;
    unsigned long long nowt1 = GetTickCount64();
    unsigned long long updateTimeStamp = (nowt1 - res.updateTime)*10000 + res.timeStamp;
    std::wstring systemTimeStr;
    FILETIME filetime;
    filetime.dwLowDateTime = updateTimeStamp & 0xffffffff;
    filetime.dwHighDateTime = updateTimeStamp >>32;
    systemTimeStr = FileTime2SystemTime(filetime);
    

    WCHAR resTime[30] = L"";
    item.pszText = resTime;
    ListView_GetItem(hWndListView, &item);
    if (wcscmp(systemTimeStr.c_str(),resTime))
    {
        wcscpy_s(resTime, systemTimeStr.length() + 1, systemTimeStr.c_str());
        ListView_SetItem(hWndListView, &item);
    }
    return TRUE;
}
BOOL setNTPItem(HWND hWndListView, int num, NTPResult res)
{
    LV_ITEM item;
    item.mask = LVIF_TEXT;
    item.iItem = num;
    item.iSubItem = 0;
    WCHAR serverName[256];
    WCHAR serverIP[16] = L"";
    wcscpy_s(serverName, res.serverName.size() + 1, res.serverName.c_str());
    //OutputDebugString(to_wstring(NTPitem.fromIP.size()).c_str());
    wcscpy_s(serverIP, res.fromIP.size() + 1, res.fromIP.c_str());
    /*WCHAR resTime[30];
    wcscpy_s(resTime, systemTimeStr.size() + 1, systemTimeStr.c_str());*/
    item.pszText = serverName;
    ListView_SetItem(hWndListView, &item);
    item.iSubItem = 1;
    item.pszText = serverIP;
    ListView_SetItem(hWndListView, &item);
    item.iSubItem = 2;
    WCHAR WinTime[64] = {};
    item.pszText = WinTime;
    ListView_SetItem(hWndListView, &item);
    return TRUE;
}
BOOL setItemStatus(HWND hWndListView, int num, wstring status)
{
    LV_ITEM item;
    item.mask = LVIF_TEXT;
    item.iItem = num;
    item.iSubItem = 3;
    WCHAR statusString[256];
    //OutputDebugString(to_wstring(NTPitem.fromIP.size()).c_str());
    wcscpy_s(statusString, status.size() + 1, status.c_str());
    /*WCHAR resTime[30];
    wcscpy_s(resTime, systemTimeStr.size() + 1, systemTimeStr.c_str());*/
    item.pszText = statusString;
    ListView_SetItem(hWndListView, &item);
    return TRUE;
}