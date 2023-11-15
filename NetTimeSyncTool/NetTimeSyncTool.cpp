// NetTimeSyncTool.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "NetTimeSyncTool.h"
#include "Time2String.h"
#include "NtpServerListUI.h"
#include "NtpClient.h"
#include <string>
#include <vector>
#include <CommCtrl.h>
#include <windowsx.h>
#include <wchar.h>
#include "GlobalNTPResultData.h"
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
WCHAR szADD[MAX_LOADSTRING];                    // ADD String
WCHAR szEDIT[MAX_LOADSTRING];                    // ADD String
WCHAR szDELETE[MAX_LOADSTRING];                    // ADD String

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Add(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK    Edit(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

HFONT globalFont;
GlobalData ntpServers;
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
    LoadStringW(hInstance, IDS_ADD, szADD, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_EDIT, szEDIT, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_DELETE, szDELETE, MAX_LOADSTRING);
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
static HWND NTPServerList;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HBRUSH hBrush;
    static HWND sysTime, boot,addButton,deleteButton,editButton;
    static HBRUSH  hbrBkgnd;
    
    static NTPResult ntp1;
    static int selectedListId = -1;
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
        sysTime = CreateWindowEx(WS_EX_TRANSPARENT  ,L"static", L"", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_CLIPCHILDREN,
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
        boot = CreateWindowEx(WS_EX_TRANSPARENT , L"static", L"", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_CLIPCHILDREN,
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
        SendMessage(hWnd, WM_SETFONT, (WPARAM)globalFont, NULL);
        SetTimer(hWnd,                  // handle to main window 
            IDT_UPDATETIMER,            // timer identifier 
            10,                         // 10-second interval 
            (TIMERPROC)NULL);           // no timer callback 

        addButton = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            szADD,      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            50,         // x position 
            360,         // y position 
            100,        // Button width
            30,        // Button height
            hWnd,     // Parent window
            (HMENU)12,       // No menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.
        SendMessage(addButton, WM_SETFONT, (WPARAM)globalFont, NULL);
        editButton = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            szEDIT,      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            160,         // x position 
            360,         // y position 
            100,        // Button width
            30,        // Button height
            hWnd,     // Parent window
            (HMENU)13,       // No menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.
        SendMessage(editButton, WM_SETFONT, (WPARAM)globalFont, NULL);
        deleteButton = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            szDELETE,      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            270,         // x position 
            360,         // y position 
            100,        // Button width
            30,        // Button height
            hWnd,     // Parent window
            (HMENU)14,       // No menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.
        SendMessage(deleteButton, WM_SETFONT, (WPARAM)globalFont, NULL);


        /*ListView_*/
        NTPServerList = CreateNTPServerList(hInst, hWnd);
        
        InitListView(hInst,NTPServerList);
        
        /*char baseServer[3][256] = { "ntp.aliyun.com","ntp2.aliyun.com","time.windows.com" };
        for (int i = 0; i < 3; i++) {
            NTPResult ntpresult;
            ntpServers.globalData.push_back(ntpresult);
            int baseServerResult = getNTPTime(baseServer[i], ntpServers.globalData[i]);
            InsertNTPViewItem(NTPServerList, ntpServers.globalData[i]);
            if (baseServerResult) {
                setItemStatus(NTPServerList, i, szERRORs);
            }
            else {
                setItemStatus(NTPServerList, i, szOKs);
            }
        }*/
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
            //int wmId = LOWORD(wParam);
            //// Parse the menu selections:
            //switch (wmId)
            //{
            //default:
            //    return DefWindowProc(hWnd, message, wParam, lParam);
            //}
            if (lParam == (LPARAM)addButton) {
                if (ListView_GetItemCount(NTPServerList) >= 10)
                {
                    int okAdd = MessageBox(hWnd,L"当前列表中有十个及以上的的网络时钟服务器了，如果继续添加，此时间UI会不稳定，是否继续？",L"添加提示",MB_OKCANCEL);
                    if(okAdd == IDCANCEL)return DefWindowProc(hWnd, message, wParam, lParam);
                }
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ADDDIALOG), hWnd, Add);
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
            else if (lParam == (LPARAM)editButton && ListView_GetSelectedCount(NTPServerList))
            {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ADDDIALOG), hWnd, Edit);
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
            else if (lParam == (LPARAM)deleteButton && ListView_GetSelectedCount(NTPServerList)) {
                
                int okDelete = MessageBox(hWnd, L"是否删除此时间服务器？", L"删除提示", MB_OKCANCEL);
                if (okDelete == IDOK) {
                    /*LV_ITEM item;
                    item.iItem = selectedListId;
                    ListView*/
                    ListView_DeleteItem(NTPServerList, selectedListId);
                    ntpServers.globalData.erase(ntpServers.globalData.begin()+selectedListId);
                    selectedListId = -1;
                }
            }
            else{
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_NOTIFY:
    {
        LPNMHDR  lpnmh = (LPNMHDR)lParam;
       
        if (lpnmh->code==NM_CLICK && lpnmh->hwndFrom ==NTPServerList) {
            /*LPNMITEMACTIVATE activeItem;
            activeItem = (LPNMITEMACTIVATE)lParam;*/
            selectedListId = ListView_GetSelectionMark(NTPServerList);
            
        }
        break;
    }
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
                    int i = 0; 
                    for (NTPResult ntp : ntpServers.globalData)
                    {
                        
                        if(!ntp.status)
                        UpdateNTPTime(NTPServerList, i, ntp);
                        i++;
                    }
                    
                    return 0;
            }
        }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK Edit(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

INT_PTR CALLBACK Add(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if ( LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDOK)
        {
            SetWindowText(hDlg, L"请等候5秒，正在获取信息....");
            char servername[256] = {};
            WCHAR dlgItem[256] = {};
            Edit_GetText(GetDlgItem(hDlg,IDC_SERVER),dlgItem,256);
            size_t convertChar = 256;
            wcstombs_s(&convertChar,servername,dlgItem,256);

            NTPResult ntp;
            int res = getNTPTime(servername, ntp);
            ntpServers.globalData.push_back(ntp);
            InsertNTPViewItem(NTPServerList, ntp);
            
            if (res) {
                WCHAR error[64] = L"";
                
                swprintf_s(error,64,szERRORs,ntp.status);
                setItemStatus(NTPServerList, ListView_GetItemCount(NTPServerList)-1, error);
            }
            else {
                setItemStatus(NTPServerList, ListView_GetItemCount(NTPServerList)-1, szOKs);
            }
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;

        }
        break;
    }
    return (INT_PTR)FALSE;
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
