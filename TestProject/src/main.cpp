#include <iostream>
#include <string>
#include <Windows.h>
#include <tchar.h>
#include "simpleMatrices.h"


// https://learn.microsoft.com/en-us/windows/win32/learnwin32/your-first-windows-program?source=recommendations

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

BOOL paint(HWND hwnd, Matrix &display) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    HBRUSH brush = CreateSolidBrush(colour::red);
    FillRect(hdc, &ps.rcPaint, CreateSolidBrush(colour::white));

    GetClientRect(hwnd, &ps.rcPaint);

    for (int i = 0; i < 8; i++){
    //front
    MoveToEx(hdc, display.get(0, 0), display.get(1, 0), NULL);
    LineTo(hdc, display.get(0, 2), display.get(1, 2));
    LineTo(hdc, display.get(0, 4), display.get(1, 4));
    LineTo(hdc, display.get(0, 1), display.get(1, 1));
    LineTo(hdc, display.get(0, 0), display.get(1, 0));

    //left
    LineTo(hdc, display.get(0, 3), display.get(1, 3));
    LineTo(hdc, display.get(0, 6), display.get(1, 6));
    LineTo(hdc, display.get(0, 2), display.get(1, 2));
    LineTo(hdc, display.get(0, 0), display.get(1, 0));
    
    //bottom
    LineTo(hdc, display.get(0, 3), display.get(1, 3));
    LineTo(hdc, display.get(0, 5), display.get(1, 5));
    LineTo(hdc, display.get(0, 1), display.get(1, 1));
    LineTo(hdc, display.get(0, 0), display.get(1, 0));

    
    //back
    MoveToEx(hdc, display.get(0, 7), display.get(1, 7), NULL);
    LineTo(hdc, display.get(0, 6), display.get(1, 6));
    LineTo(hdc, display.get(0, 2), display.get(1, 2));
    LineTo(hdc, display.get(0, 4), display.get(1, 4));
    LineTo(hdc, display.get(0, 7), display.get(1, 7));
    
    //right
    LineTo(hdc, display.get(0, 5), display.get(1, 5));
    LineTo(hdc, display.get(0, 1), display.get(1, 1));
    LineTo(hdc, display.get(0, 4), display.get(1, 4));
    LineTo(hdc, display.get(0, 7), display.get(1, 7));
    
    //top
    LineTo(hdc, display.get(0, 4), display.get(1, 4));
    LineTo(hdc, display.get(0, 2), display.get(1, 2));
    LineTo(hdc, display.get(0, 6), display.get(1, 6));
    LineTo(hdc, display.get(0, 7), display.get(1, 7));
    }
    EndPaint(hwnd, &ps);

    return 1;
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
    SetTimer(hwnd, 0, 5, NULL);
    while (GetMessage(&msg, hwnd, 0, 0) != 0)
    {   
        TranslateMessage(&msg);
        DispatchMessage(&msg);

    }
    return 0;
}


LRESULT CALLBACK wProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    switch (msg)
    {
        case WM_CLOSE:
        {
            std::cout << "Test" << std::endl;
            DestroyWindow(hwnd);
            PostQuitMessage(0);
            return 1;
        }
        case WM_LBUTTONDOWN:
        {
            std::cout << "Stop touching me!" << std::endl;
            colour::currentColour = colour::red;
            InvalidateRect(hwnd, NULL, true);
            return 1;
        }
        case WM_CREATE:
        {   
            return 1;
        }
        case WM_LBUTTONUP:
        {
            std::cout << "Thank you!" << std::endl;
            colour::currentColour = colour::green;
            InvalidateRect(hwnd, NULL, true);
            return 1;
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

            cube.display();
            
            Matrix projection(4, 4);
            float fNear = 0.1f;
            float fFar = 1000.0f;
            float fFov = 90.0f;
            float fAspectRatio = (float) client.bottom / (float) client.right;
            std::cout << fAspectRatio << std::endl;
            float fFOVRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159265359f);

            projection.set(0, 0) = fAspectRatio * fFOVRad;
            projection.set(1, 1) = fFOVRad;
            projection.set(2, 2) = -((fFar + fNear) / (fFar - fNear));
            projection.set(2, 3) = -(2 * (fNear * fFar) / (fFar - fNear));
            projection.set(3, 2) = -1;

            std::cout << "projection" << std::endl;
            projection.display();

            Matrix translate(4, 4);
            translate.set(0, 3) = 1.0f;
            translate.set(1, 3) = 1.0f;
            translate.set(2, 3) = 3.0f;

            translate.set(1, 1) = 1;
            translate.set(0, 0) = 1;
            translate.set(2, 2) = 1;
            translate.set(3, 3) = 1;

            std::cout << "translate" << std::endl;
            translate.display();

            Matrix yRotation(4, 4);

            yRotation.set(0, 0) = cos(1.0f * ts);
            yRotation.set(1, 1) = 1;
            yRotation.set(0, 2) = sin(1.0f * ts);
            yRotation.set(2, 2) = cos(1.0f * ts);
            yRotation.set(2, 1) = -sin(1.0f * ts);
            yRotation.set(3, 3) = 1;

            Matrix xRotation(4, 4);

            xRotation.set(0, 0) = 1;
            xRotation.set(1, 1) = cos(1.0f * ts);
            xRotation.set(2, 1) = sin(1.0f * ts);
            xRotation.set(2, 2) = cos(1.0f * ts);
            xRotation.set(1, 2) = -sin(1.0f * ts);
            xRotation.set(3, 3) = 1;

            //xRotation.set(0, 3) = 30.0f;
            //xRotation.set(1, 3) = 10.0f;

            Matrix scale(4, 4);
            scale.set(0, 0) += 1;
            scale.set(1, 1) += 1;
            scale.set(0, 0) *= 0.1f * client.right;
            scale.set(1, 1) *= 0.1f * client.bottom;

            scale.set(2, 2) = 1;
            scale.set(3, 3) = 1;

            Matrix txCube(4, 8);
            Matrix xCube(4, 8);
            mDotP(translate, cube, txCube);

            translate.set(0, 3) = 6.0f;
            translate.set(1, 3) = 5.0f;
            mDotP(xRotation, txCube, xCube);

            Matrix rCube(4, 8);
            mDotP(yRotation, xCube, rCube);

            Matrix tRCube(4, 8);
            mDotP(translate, rCube, tRCube);

            std::cout << "pTCube" << std::endl;
            tRCube.display();

            Matrix pTRCube(4, 8);
            mDotP(projection, tRCube, pTRCube);

            std::cout << "pTRCube" << std::endl;
            pTRCube.display();

            Matrix display(4, 8);
            mDotP(scale, pTRCube, display);
            
            std::cout << "display" << std::endl;
            display.display();


            return paint(hwnd, display);
        }
        case WM_TIMER:
        {   
            ts += 0.05f;
            InvalidateRect(hwnd, NULL, true);
        }
        default:
        {
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }

        return 0;
    }

    return NULL;
}