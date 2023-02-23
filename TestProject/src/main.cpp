#include <iostream>
#include <string>
#include <Windows.h>
#include <tchar.h>
#include <math.h>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include "..\headers\simpleMatrices.h"
#include "..\headers\graphicsProcessing.h"
#include "..\headers\objects.h"

LRESULT CALLBACK wProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lparam);
float ts = 0.9f;

Camera* c;
bool keys[4]= { false, false, false, false};

namespace colour{
    const COLORREF red = 0x000000FF;
    const COLORREF green = 0x0000FF00;
    const COLORREF purple = 0x00FF00FF;
    const COLORREF yellow = 0x0000FFFF;
    const COLORREF white = 0x00FFFFFF;
    const COLORREF black = 0x00000000;

    COLORREF currentColour = green;
}

BOOL paint(HWND hwnd, HDC hdc, PAINTSTRUCT ps, GameObject& display) {
    HBRUSH brush = CreateSolidBrush(colour::white);
    GetClientRect(hwnd, &ps.rcPaint);

    for (int i = 0; i < display.obj->returnRows(); i++) {
        for (int u = 0; u < display.obj->returnColumns(); u++) {
            display.obj->set(i, u) = (int) round(display.obj->get(i, u));
        }
    }

    for (int i = 0; i < display.obj->returnColumns(); i++) {
        display.obj->set(0, i) += ps.rcPaint.right / 2;
        display.obj->set(1, i) += ps.rcPaint.bottom / 2;
    }


    display.calculateNormals();
    for (int i = 0; i < display.faceCount; i++) {
        int v1 = display.objFaces[i].vertex[0];
        int v2 = display.objFaces[i].vertex[1];
        int v3 = display.objFaces[i].vertex[2];

        if (display.objFaces[i].normal[0] * (display.obj->get(0, v1) - c->x) + display.objFaces[i].normal[1] * (display.obj->get(1, v1) - c->y) + display.objFaces[i].normal[2] * (display.obj->get(2, v1) + c->z) > 0.0f) {

            MoveToEx(hdc, display.obj->get(0, v1), display.obj->get(1, v1), NULL);
            LineTo(hdc, display.obj->get(0, v2), display.obj->get(1, v2));
            LineTo(hdc, display.obj->get(0, v3), display.obj->get(1, v3));
            LineTo(hdc, display.obj->get(0, v1), display.obj->get(1, v1));
        }
    }


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

    RECT rect = {};
    GetClientRect(hwnd, &rect);
    Camera cam(rect.right, rect.bottom);

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    c = &cam;

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
        case WM_KEYDOWN:
        {
            if ((wchar_t)wParam == 'W') keys[0] = true;
            if ((wchar_t)wParam == 'S') keys[2] = true;
            if ((wchar_t)wParam == 'A') keys[1] = true;
            if ((wchar_t)wParam == 'D') keys[3] = true;

            return true;
        }
        case WM_KEYUP:
        {
            if ((wchar_t)wParam == 'W') keys[0] = false;
            if ((wchar_t)wParam == 'S') keys[2] = false;
            if ((wchar_t)wParam == 'A') keys[1] = false;
            if ((wchar_t)wParam == 'D') keys[3] = false;

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

            std::filesystem::path cwd = std::filesystem::current_path() / "models";
            std::filesystem::path cubeFile = cwd / "teapot.obj";

            GameObject testCube(cubeFile.string());
            mRotate(*testCube.obj, 0, 100 * ts, 0);
            mTranslate(*testCube.obj, 0, -3, 5);
            c->projectToScreen(*testCube.obj, client.right, client.bottom);

            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, CreateSolidBrush(colour::black));
            SelectObject(hdc, CreatePen(0, 1, colour::white));

            paint(hwnd, hdc, ps, testCube);

            EndPaint(hwnd, &ps);
            return true;
        }
        case WM_TIMER:
        {   
            ts += 0.1f;
            if (keys[0]) c->z += 0.1;
            if (keys[1]) c->x -= 0.1;
            if (keys[2]) c->z -= 0.1;
            if (keys[3]) c->x += 0.1;

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