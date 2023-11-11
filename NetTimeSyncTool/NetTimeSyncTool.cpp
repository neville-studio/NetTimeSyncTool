// NetTimeSyncTool.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "NetTimeSyncTool.h"
#include "Time2String.h"
#include "NtpServerListUI.h"
#include "NtpClient.h"
#include <string>
#include <CommCtrl.h>
#define MAX_LOADSTRING 100
#define IDT_UPDATETIMER 1001
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
WCHAR szSYSTEMTIME[MAX_LOADSTRING];             // system time control
WCHAR szNETWORKTIMESTRING[MAX_LOADSTRING];      // network time string
WCHAR szBOOTTIMESTRING[MAX_LOADSTRING];         // boot time string
WCHAR szOKs[MAX_LOADSTRING];                    // OK String
WCHAR szERRORs[MAX_LOADSTRING];                 // Error String

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HFONT globalFont;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_NETTIMESYNCTOOL, szWindowClass, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_SYSTEM_TIME_STRING, szSYSTEMTIME, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_NETWORKTIMESTATIC, szNETWORKTIMESTRING, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_OPENTIME, szBOOTTIMESTRING, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_OK, szOKs, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_ERROR, szERRORs, MAX_LOADSTRING);

    MyRegisterClass(hInstance);
    globalFont = CreateFont(-16/*高*/, -8/*宽*/, 0, 0, 400 /*400表示正常字体*/,
        FALSE/*斜体?*/, FALSE/*下划线?*/, FALSE/*删除线?*/, DEFAULT_CHARSET,
        OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
        FF_DONTCARE, TEXT("Microsoft Yahei")
    );
    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NETTIMESYNCTOOL));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = NULL;// CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NETTIMESYNCTOOL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    //wcex.hbrBackground  = NULL;
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_NETTIMESYNCTOOL);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowExW(NULL,szWindowClass, szTitle, (WS_OVERLAPPEDWINDOW ^ WS_SIZEBOX ^ WS_MAXIMIZE ^ WS_MAXIMIZEBOX) | WS_CLIPCHILDREN,
      CW_USEDEFAULT, 0, 750, 500, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}





//HWND CreateListView(HINSTANCE hInstance, HWND hwndParent)
//{
//    DWORD       dwStyle;
//    HWND        hwndListView;
//    BOOL        bSuccess = TRUE;
//
//    dwStyle = WS_TABSTOP |
//        WS_CHILD |
//        WS_BORDER |
//        WS_VISIBLE |
//        LVS_AUTOARRANGE |
//        LVS_REPORT |
//        LVS_OWNERDATA;
//
//    hwndListView = CreateWindowEx(WS_EX_CLIENTEDGE,          // ex style
//        WC_LISTVIEW,               // class name - defined in commctrl.h
//        TEXT(""),                        // dummy text
//        dwStyle,                   // style
//        0,                         // x position
//        0,                         // y position
//        0,                         // width
//        0,                         // height
//        hwndParent,                // parent
//        (HMENU)ID_LISTVIEW,        // ID
//        g_hInst,                   // instance
//        NULL);                     // no extra data
//
//    if (!hwndListView)
//        return NULL;
//
//    ResizeListView(hwndListView, hwndParent);
//
//    //set the image lists
//    himlSmall = ImageList_Create(16, 16, ILC_COLORDDB | ILC_MASK, 1, 0);
//    himlLarge = ImageList_Create(32, 32, ILC_COLORDDB | ILC_MASK, 1, 0);
//
//    if (himlSmall && himlLarge)
//    {
//        HICON hIcon;
//
//        //set up the small image list
//        hIcon = LoadImage(g_hInst, MAKEINTRESOURCE(IDI_DISK), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
//        ImageList_AddIcon(himlSmall, hIcon);
//
//        //set up the large image list
//        hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_DISK));
//        ImageList_AddIcon(himlLarge, hIcon);
//
//        ListView_SetImageList(hwndListView, himlSmall, LVSIL_SMALL);
//        ListView_SetImageList(hwndListView, himlLarge, LVSIL_NORMAL);
//    }
//
//    return hwndListView;
//}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HBRUSH hBrush;
    static HWND sysTime, boot;
    static HBRUSH  hbrBkgnd;
    static HWND NTPServerList;
    static NTPResult ntp1;
    switch (message)
    {
    case WM_CREATE:
    {
        SendMessage(hWnd, WM_SETFONT, (WPARAM)globalFont, NULL);
        HWND systemTime = CreateWindowEx(WS_EX_TRANSPARENT,L"static", szSYSTEMTIME, WS_CHILD  | WS_VISIBLE  | SS_LEFT ,
            50 /*X坐标*/, 10, 125, 25,
            hWnd,		 //父窗口句柄
            (HMENU)1,	 //为控件指定一个唯一标识符
            hInst,		 //当前程序实例句柄
            NULL);
        SendMessage(systemTime, WM_SETFONT, (WPARAM)globalFont, NULL);
        sysTime = CreateWindowEx(WS_EX_TRANSPARENT  ,L"static", L"", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_CLIPSIBLINGS ,
            175 /*X坐标*/, 10, 300, 25,
            hWnd,		 //父窗口句柄
            (HMENU)1,	 //为控件指定一个唯一标识符
            hInst,		 //当前程序实例句柄
            NULL);
        SendMessage(sysTime, WM_SETFONT, (WPARAM)globalFont, NULL);
        HWND bootTime = CreateWindowEx(WS_EX_TRANSPARENT, L"static", szBOOTTIMESTRING, WS_CHILD | WS_VISIBLE | SS_LEFT,
            50 /*X坐标*/, 40, 125, 25,
            hWnd,		 //父窗口句柄
            (HMENU)1,	 //为控件指定一个唯一标识符
            hInst,		 //当前程序实例句柄
            NULL);
        SendMessage(bootTime, WM_SETFONT, (WPARAM)globalFont, NULL);
        boot = CreateWindowEx(WS_EX_TRANSPARENT , L"static", L"", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_CLIPSIBLINGS,
            175 /*X坐标*/, 40, 125, 25,
            hWnd,		 //父窗口句柄
            (HMENU)1,	 //为控件指定一个唯一标识符
            hInst,		 //当前程序实例句柄
            NULL);
        SendMessage(boot, WM_SETFONT, (WPARAM)globalFont, NULL);
        HWND netTime = CreateWindowEx(WS_EX_TRANSPARENT, L"static", szNETWORKTIMESTRING, WS_CHILD | WS_VISIBLE | SS_LEFT,
            50 /*X坐标*/, 70, 125, 25,
            hWnd,		 //父窗口句柄
            (HMENU)1,	 //为控件指定一个唯一标识符
            hInst,		 //当前程序实例句柄
            NULL);
        SendMessage(netTime, WM_SETFONT, (WPARAM)globalFont, NULL);
        SetTimer(hWnd,                  // handle to main window 
            IDT_UPDATETIMER,            // timer identifier 
            10,                         // 10-second interval 
            (TIMERPROC)NULL);           // no timer callback 
        /*ListView_*/
        NTPServerList = CreateNTPServerList(hInst, hWnd);
        InitListView(hInst,NTPServerList);
        
        char baseServer[256] = "ntp2.aliyun.com";
        
        int baseServerResult = getNTPTime(baseServer, ntp1);
        InsertNTPViewItem(NTPServerList, ntp1);
        if (baseServerResult) {
            setItemStatus(NTPServerList, 0, szERRORs);
        }
        else {
            setItemStatus(NTPServerList, 0, szOKs);
        }
    }   
    break;
    case WM_ERASEBKGND:
    {
        if ((WPARAM)NTPServerList == wParam||hWnd==NTPServerList)
            OutputDebugString(L"ERASING\n");
            return TRUE;

        return DefWindowProc(hWnd, WM_ERASEBKGND, wParam, lParam);
    }
    case WM_CTLCOLORSTATIC:
    {
        //if ((HWND)lParam == boot || (HWND)lParam == sysTime) {
            HDC hdcStatic = (HDC)wParam;
            SetTextColor(hdcStatic, RGB(0, 0, 0));
            SetBkColor(hdcStatic, RGB(0, 0, 0));
            SetBkMode(hdcStatic, TRANSPARENT);

            /*RECT rect;
            rect.left = 175; rect.right = 475;
            rect.top = 10; rect.bottom = 35;
            InvalidateRect((HWND)lParam, &rect, false);*/
            /*if (hbrBkgnd == NULL)
            {
                hbrBkgnd = CreateSolidBrush(RGB(255, 255, 255));
            }*/
        //}
        return (INT_PTR)hbrBkgnd;
    }
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
        
            PAINTSTRUCT ps;
            HDC hdc_old = BeginPaint(hWnd, &ps);
            
            HDC hdc = CreateCompatibleDC(hdc_old);
            RECT clientRect;
            GetClientRect(hWnd, &clientRect);
            HBITMAP hBmp = CreateCompatibleBitmap(hdc_old, clientRect.right, clientRect.bottom);
            SelectObject(hdc, GetSysColorBrush(COLOR_3DFACE)); //设置刷子颜色 - Rectangle()的填充色
            BitBlt(hdc_old, 0, 0, clientRect.right, clientRect.bottom, hdc, 0, 0, SRCCOPY);
            DeleteObject(hBmp);

            DeleteDC(hdc);
            if (hWnd == NTPServerList)
                OutputDebugString(L"NTP Server List\n");
            ReleaseDC(hWnd, hdc); //释放 
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_TIMER:
        switch (wParam)
        {
            case IDT_UPDATETIMER: 
            {
                // process the 10-second timer 
                FILETIME fileTime;
                GetSystemTimeAsFileTime(&fileTime);
                std::wstring systemTimeStr;
            
                    systemTimeStr = FileTime2SystemTime(fileTime);
                    WCHAR compareTime[64];
                    GetWindowText(sysTime, compareTime, 64);
                    if(wcscmp(compareTime,systemTimeStr.c_str()))
                    SetWindowText(sysTime, systemTimeStr.c_str());
                    //OutputDebugString(L"Updating...\n");
                    std::wstring bootTimeStr = TimeStamp2HMS(GetTickCount64());
                    GetWindowText(boot, compareTime, 64);
                    if (wcscmp(compareTime, bootTimeStr.c_str()))
                    SetWindowText(boot, bootTimeStr.c_str());
                   
                    UpdateNTPTime(NTPServerList, 0, ntp1);
                    return 0;
            }
        }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
