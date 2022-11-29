#include <iostream>
#include <string>
#include <Windows.h>
#include <tchar.h>
#include <math.h>
#include "simpleMatrices.h"
#include "graphicsProcessing.h"


// https://learn.microsoft.com/en-us/windows/win32/learnwin32/your-first-windows-program?source=recommendations

bool applyProject(Matrix& obj, int column, Matrix& m);

LRESULT CALLBACK wProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lparam);
float ts = 0.9f;

namespace colour{
    const COLORREF red = 0x000000FF;
    const COLORREF green = 0x0000FF00;
    const COLORREF purple = 0x00FF00FF;
    const COLORREF yellow = 0x0000FFFF;
    const COLORREF white = 0x00FFFFFF;

    COLORREF currentColour = green;
}




BOOL paint(HWND hwnd, HDC hdc, PAINTSTRUCT ps, Matrix& display) {
    HBRUSH brush = CreateSolidBrush(colour::red);
    
    GetClientRect(hwnd, &ps.rcPaint);

    for (int i = 0; i < display.returnRows(); i++) {
        for (int u = 0; u < display.returnColumns(); u++) {
            display.set(i, u) = (int) round(display.get(i, u));
        }
    }
    
    for (int i = 0; i < display.returnColumns(); i++) {
        display.set(0, i) += ps.rcPaint.right / 2;
        display.set(1, i) += ps.rcPaint.bottom / 2;
    }
    
   
    //front
    MoveToEx(hdc, (int)display.get(0, 0), (int)display.get(1, 0), NULL);
    LineTo(hdc, (int)display.get(0, 2), (int)display.get(1, 2));
    LineTo(hdc, (int)display.get(0, 4), (int)display.get(1, 4));
    LineTo(hdc, (int)display.get(0, 1), (int)display.get(1, 1));
    LineTo(hdc, (int)display.get(0, 0), (int)display.get(1, 0));

    //left
    LineTo(hdc, (int)display.get(0, 3), (int)display.get(1, 3));
    LineTo(hdc, (int)display.get(0, 6), (int)display.get(1, 6));
    LineTo(hdc, (int)display.get(0, 2), (int)display.get(1, 2));
    LineTo(hdc, (int)display.get(0, 0), (int)display.get(1, 0));

    //bottom
    LineTo(hdc, (int)display.get(0, 3), (int)display.get(1, 3));
    LineTo(hdc, (int)display.get(0, 5), (int)display.get(1, 5));
    LineTo(hdc, (int)display.get(0, 1), (int)display.get(1, 1));
    LineTo(hdc, (int)display.get(0, 0), (int)display.get(1, 0));


    //back
    MoveToEx(hdc, (int)display.get(0, 7), (int)display.get(1, 7), NULL);
    LineTo(hdc, (int)display.get(0, 6), (int)display.get(1, 6));
    LineTo(hdc, (int)display.get(0, 2), (int)display.get(1, 2));
    LineTo(hdc, (int)display.get(0, 4), (int)display.get(1, 4));
    LineTo(hdc, (int)display.get(0, 7), (int)display.get(1, 7));

    //right
    LineTo(hdc, (int)display.get(0, 5), (int)display.get(1, 5));
    LineTo(hdc, (int)display.get(0, 1), (int)display.get(1, 1));
    LineTo(hdc, (int)display.get(0, 4), (int)display.get(1, 4));
    LineTo(hdc, (int)display.get(0, 7), (int)display.get(1, 7));

    //top
    LineTo(hdc, (int)display.get(0, 4), (int)display.get(1, 4));
    LineTo(hdc, (int)display.get(0, 2), (int)display.get(1, 2));
    LineTo(hdc, (int)display.get(0, 6), (int)display.get(1, 6));
    LineTo(hdc, (int)display.get(0, 7), (int)display.get(1, 7));

    SelectObject(hdc, brush);


    return true;
}


INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, INT nCmdShow) {
	const wchar_t wndName[] = L"Test";
    
    WNDCLASSEX wnd = {};

    wnd.lpfnWndProc = wProc;
    wnd.hInstance = hInstance;
    wnd.lpszClassName = wndName;
    wnd.cbSize = sizeof(WNDCLASSEX);
    
    RegisterClassEx(&wnd);

    HWND hwnd = CreateWindowEx(
    0,
    wndName,
    wndName,
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    NULL,
    NULL,
    hInstance,
    NULL
    );
    

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);



    FILE* fDummy;
    AllocConsole();
    freopen_s(&fDummy, "CONOUT$", "w", stdout);

    
    MSG msg = { };
    SetTimer(hwnd, 0, 50, NULL);
    while (GetMessage(&msg, hwnd, 0, 0) != 0)
    {   
        TranslateMessage(&msg);
        DispatchMessage(&msg);

    }
    return false;
}


LRESULT CALLBACK wProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    switch (msg)
    {
        case WM_CLOSE:
        {
            std::cout << "Test" << std::endl;
            DestroyWindow(hwnd);
            PostQuitMessage(0);
            return true;
        }
        case WM_LBUTTONDOWN:
        {
            std::cout << "Stop touching me!" << std::endl;
            colour::currentColour = colour::red;
            InvalidateRect(hwnd, NULL, true);
            return true;
        }
        case WM_CREATE:
        {   
            return true;
        }
        case WM_LBUTTONUP:
        {
            std::cout << "Thank you!" << std::endl;
            colour::currentColour = colour::green;
            InvalidateRect(hwnd, NULL, true);
            return true;
        }
        case WM_PAINT:
        {
            RECT client = {};
            GetClientRect(hwnd, &client);

            Matrix cube(4, 8);
            cube.set(0, 0) = 0; cube.set(1, 0) = 0; cube.set(2, 0) = 0; cube.set(3, 0) = 1;
            cube.set(0, 1) = 1; cube.set(1, 1) = 0; cube.set(2, 1) = 0; cube.set(3, 1) = 1;
            cube.set(0, 2) = 0; cube.set(1, 2) = 1; cube.set(2, 2) = 0; cube.set(3, 2) = 1; 
            cube.set(0, 3) = 0; cube.set(1, 3) = 0; cube.set(2, 3) = 1; cube.set(3, 3) = 1;
            cube.set(0, 4) = 1; cube.set(1, 4) = 1; cube.set(2, 4) = 0; cube.set(3, 4) = 1;
            cube.set(0, 5) = 1; cube.set(1, 5) = 0; cube.set(2, 5) = 1; cube.set(3, 5) = 1;
            cube.set(0, 6) = 0; cube.set(1, 6) = 1; cube.set(2, 6) = 1; cube.set(3, 6) = 1;
            cube.set(0, 7) = 1; cube.set(1, 7) = 1; cube.set(2, 7) = 1; cube.set(3, 7) = 1;
            

            mTranslate(cube, -0.5, -0.5, 0.5);

            Matrix cube2(4, 8);
            Matrix cube3(4, 8);
            copyMatrixContents(cube, cube2);
            copyMatrixContents(cube, cube3);

            mRotate(cube, 90 * ts, 0, 0);
            mRotate(cube2, 0, 90 * ts, 0);
            mRotate(cube3, 0, 0, 90 * ts);

            mTranslate(cube, 0, 0, -3);
            mTranslate(cube2, -2, 0, -3);
            mTranslate(cube3, 2, 0, -3);

            projectToScreen(cube, client.right, client.bottom);
            projectToScreen(cube2, client.right, client.bottom);
            projectToScreen(cube3, client.right, client.bottom);


            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, CreateSolidBrush(colour::white));

            paint(hwnd, hdc, ps, cube);
            paint(hwnd, hdc, ps, cube2);
            paint(hwnd, hdc, ps, cube3);

            EndPaint(hwnd, &ps);
            return true;
        }
        case WM_TIMER:
        {   
            ts += 0.05f;
            InvalidateRect(hwnd, NULL, true);
            return true;
        }
        default:
        {
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }

        return 0;
    }

    return NULL;
}