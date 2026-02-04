/*
 * Prototype DLL injection for Hades (Supergiant Games)
 * For educational and reverse-engineering research purposes.
 *
 * Author: Hamada Trichine
 */

#include <Windows.h>
#include <stdio.h>

void LoadOriginalXInput()
{
    char sysPath[MAX_PATH];
    GetSystemDirectoryA(sysPath, MAX_PATH);
    lstrcatA(sysPath, "\\xinput1_4.dll");

    LoadLibraryA(sysPath);
}

bool init()
{
    LoadOriginalXInput();
    AllocConsole();

    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    freopen_s(&f, "CONOUT$", "w", stderr);
    freopen_s(&f, "CONIN$", "r", stdin);

    SetConsoleTitleA("Hades Injected DLL Console");

    printf("Console allocated successfully!\n");
    printf("PID: %lu\n", GetCurrentProcessId());
    return true;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD ul_reason_for_call,
    LPVOID)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        init();
        return TRUE;
    }
    return false;
}
