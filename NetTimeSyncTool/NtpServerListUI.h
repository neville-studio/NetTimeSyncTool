#pragma once
#include <Windows.h>
#include "NtpClient.h"
HWND CreateNTPServerList(HINSTANCE hInst, HWND hWnd);
BOOL InitListView(HINSTANCE hInstance, HWND hwndListView);
BOOL InsertListViewItems(HWND hwndListView);
BOOL InsertNTPViewItem(HWND hWndListView, NTPResult NTPitem);
BOOL UpdateNTPTime(HWND hWndListView, int num, NTPResult res);
BOOL setItemStatus(HWND hWndListView, int num, std::wstring status);
BOOL setNTPItem(HWND hWndListView, int num, NTPResult res);