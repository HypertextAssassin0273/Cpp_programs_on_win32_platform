// win32lesson1.cpp : Defines the entry point for the application.
#include "framework.h"
#include "win32lesson1.h"

#define MAX_LOADSTRING 100
/*Declaring condition variables for GDI Tools (START)*/
bool gbDrawLine = false;
bool gbDrawEllipse = false;
/*Declaring condition variables for GDI Tools (END)*/
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
    LoadStringW(hInstance, IDC_WIN32LESSON1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32LESSON1));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32LESSON1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32LESSON1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

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
    /*Detecting Keyboard Keys (START)*/
    case WM_KEYDOWN:
    {
        switch (wParam) {
        case VK_LEFT:
        {
            ::MessageBox(hWnd, _T("Left Arrow"), _T("Key Pressed"), MB_OK);
            break;
        }
        case 'X':
        {
            ::MessageBox(hWnd, _T("X"), _T("Key Pressed"), MB_OK);
            break;
        }
        }
        break;
    }
    case WM_CHAR:
    {
        switch (wParam) {
        case _T('a'):
        {
            ::MessageBox(hWnd, _T("a"), _T("Key Pressed"), MB_OK);
            break;
        }
        case _T('A'):
        {
            ::MessageBox(hWnd, _T("A"), _T("Key Pressed"), MB_OK);
            break;
        }
        }
        break;
    }
    case WM_KEYUP:
    {
        switch (wParam) {
        case VK_UP:
        {
            ::MessageBox(hWnd, _T("Up Arrow"), _T("Key Released"), MB_OK);
            break;
        }
        }
        break;
    }
    /*Detecting Keyboard Keys (END)*/
    /*Detecting Mouse Keys (START)*/
    case WM_LBUTTONDOWN:
    {
        int iPosX = LOWORD(lParam);
        int iPosY = HIWORD(lParam);
        wchar_t waCoord[20];
        wsprintf(waCoord, _T("(%i, %i)"), iPosX, iPosY);
        ::MessageBox(hWnd, waCoord, _T("LMB Click"), MB_OK);
        break;
    }
    case WM_RBUTTONDOWN:
    {
        int iPosX = LOWORD(lParam);
        int iPosY = HIWORD(lParam);
        wchar_t waCoord[20];
        wsprintf(waCoord, _T("(%i, %i)"), iPosX, iPosY);
        ::MessageBox(hWnd, waCoord, _T("RMB Click"), MB_OK);
        break;
    }
    /*Detecting Mouse Keys (END)*/
    case WM_COMMAND:
        {   
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
            {
                //DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About); //default dialog-box
                /*Adding Message Boxes with diff. styles (START)*/
                int iMessage = ::MessageBox(hWnd, _T("Play again?"), _T("Game Over"), MB_YESNO | MB_ICONQUESTION);
                /*Notes:-
                1) Here,scope resolution operator indicates that this function is global
                2) _T converts ASCII to UNI Codes
                3) Always specify window handlers in first arg box in ::MessageBox() to make sure that unauthorized calls are neglected*/
                switch (iMessage) {
                case IDYES:
                {
                    ::MessageBox(hWnd, _T("Yes"), _T(""), MB_ICONEXCLAMATION);
                    break;
                }
                case IDNO:
                {
                    ::MessageBox(hWnd, _T("No"), _T(""), MB_ICONHAND);
                    break;
                }
                }
                break;
                /*Adding Message Boxes with diff. styles (START)*/
            }
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            /*Adding Menu Items (START)*/
            case IDM_LINE:
                gbDrawLine = !gbDrawLine;
                InvalidateRect(hWnd, 0, TRUE);
                break;
            case IDM_ELLIPSE:
                gbDrawEllipse = !gbDrawEllipse;
                InvalidateRect(hWnd, 0, TRUE);
                break;
            /*Adding Menu Items (END)*/
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            /*Using GDI Tools (START)*/
            HPEN hPenOld;

            if (gbDrawLine) {
                // Draw a red line
                HPEN hLinePen;
                COLORREF qLineColor;
                qLineColor = RGB(255, 0, 0);
                hLinePen = CreatePen(PS_SOLID, 7, qLineColor);
                hPenOld = (HPEN)SelectObject(hdc, hLinePen);

                MoveToEx(hdc, 100, 100, NULL);
                LineTo(hdc, 500, 250);

                SelectObject(hdc, hPenOld);
                DeleteObject(hLinePen);
            }

            if (gbDrawEllipse) {
                // Draw a blue ellipse
                HPEN hEllipsePen;
                COLORREF qEllipseColor;
                qEllipseColor = RGB(0, 0, 255);
                hEllipsePen = CreatePen(PS_SOLID, 3, qEllipseColor);
                hPenOld = (HPEN)SelectObject(hdc, hEllipsePen);

                Arc(hdc, 100, 100, 500, 250, 0, 0, 0, 0);

                SelectObject(hdc, hPenOld);
                DeleteObject(hEllipsePen);
            }
            /*Using GDI Tools (END)*/
            EndPaint(hWnd, &ps);
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