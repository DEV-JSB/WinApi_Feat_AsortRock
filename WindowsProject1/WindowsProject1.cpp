// WindowsProject1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "WindowsProject1.h"

#define MAX_LOADSTRING 100

HWND g_hWnd;

int x, y;
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    SetTimer(g_hWnd, 0, 0, nullptr);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

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

    KillTimer(g_hWnd, 0);
    // 윈도우 메세지 기반 처리 방식을 쓰지 않고 게임을 만들 것 이다.

    return (int) msg.wParam;
}



#include<vector>    

using std::vector;

struct tObjectInfo
{
    POINT g_ptObjectPos;
    POINT g_ptObjectScale;
};

vector<tObjectInfo> g_vecInfo;


// 좌 상단
POINT g_ptLT;

// 우측 하단
POINT g_ptRB;


bool bLbtDown = false;


// 윈도우 헨들 전역



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
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

   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}


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
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }   
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            // 직접 펜과 브러쉬를 만들어서 DC 에 지급
            HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
            HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));

            // 기존 펜과 브러쉬 ID 값을 받아 둠
            HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen);
            HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);

            // 변경된 펜으로 사각형 그림
            if(bLbtDown)
                Rectangle(hdc, g_ptLT.x, g_ptLT.y,g_ptRB.x,g_ptRB.y);
            for (size_t i = 0; i < g_vecInfo.size(); ++i)
            {
                Rectangle(hdc,
                    g_vecInfo[i].g_ptObjectPos.x - g_vecInfo[i].g_ptObjectScale.x * 0.5,
                    g_vecInfo[i].g_ptObjectPos.y - g_vecInfo[i].g_ptObjectScale.y * 0.5,
                    g_vecInfo[i].g_ptObjectPos.x + g_vecInfo[i].g_ptObjectScale.x * 0.5,
                    g_vecInfo[i].g_ptObjectPos.y + g_vecInfo[i].g_ptObjectScale.y * 0.5
                    );
            }
            // 다시 펜과 브러쉬를 되돌림
            SelectObject(hdc, hDefaultPen);
            SelectObject(hdc, hDefaultBrush);

            // 다 쓴 Red 펜 삭제 요청
            // 다 쓴 Blue 브러쉬 삭제 요청
            DeleteObject(hRedPen);
            DeleteObject(hBlueBrush);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_UP:
            //g_ptObjectPos.y -= 10;
            InvalidateRect(hWnd, nullptr, true);
            // 특정 영역을 탐지해서 무효화 영역을 감지해서 변경이 일어난다면 다시 그려라고 하는 함수
            // 2번째 인자로 nullptr 을 넣으면 전체 영역을 탐지한다.
            // 3번째 인자로 기존의 모든 픽셀을 지울 수 있다
            break;
        case VK_DOWN:
           // g_ptObjectPos.y += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case VK_LEFT:
           // g_ptObjectPos.x -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case VK_RIGHT:
          //  g_ptObjectPos.x += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case 'W':

            break;
        }
    }
       break;
    case WM_LBUTTONDOWN:
    {
        g_ptLT.x = LOWORD(lParam);
        g_ptLT.y = HIWORD(lParam);
        bLbtDown = true;
    }
    break;
    case WM_MOUSEMOVE:
        g_ptRB.x = LOWORD(lParam);
        g_ptRB.y = HIWORD(lParam);
        InvalidateRect(hWnd, nullptr, true);
        break;
    case WM_LBUTTONUP:
    {
        g_ptRB.x = LOWORD(lParam);
        g_ptRB.y = HIWORD(lParam);

        tObjectInfo info{};
        info.g_ptObjectPos.x = (g_ptLT.x + g_ptRB.x) * 0.5;
        info.g_ptObjectPos.y = (g_ptLT.y + g_ptRB.y) * 0.5;

        //absorute 절댓값 구하는 함수 abs
        info.g_ptObjectScale.x = abs(g_ptLT.x - g_ptRB.x);
        info.g_ptObjectScale.y = abs(g_ptLT.y - g_ptRB.y);

        g_vecInfo.push_back(info);
        bLbtDown = false;
        InvalidateRect(hWnd, nullptr, true);

    }
        break;
    case WM_TIMER:
    {
        int a = 0;
    }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
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
