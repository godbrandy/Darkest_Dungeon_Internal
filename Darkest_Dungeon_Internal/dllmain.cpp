// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Psapi.h>

extern "C" void StressCheat();
extern "C" void HealthCheat();
extern "C" void EnemyHealthCheat();


DWORD WINAPI MainThread(HMODULE hModule)
{
    // Create the console for the output

    AllocConsole();
    FILE* file;
    freopen_s(&file, "CONOUT$", "w", stdout);
    std::cout << "DLL injected successfully.\n";

    // Get module information
    MODULEINFO mod_info = { 0 };
    HMODULE mod_handle = GetModuleHandle(L"darkest.exe");

    if (mod_handle)
    {
        GetModuleInformation(GetCurrentProcess(), mod_handle, &mod_info, sizeof(MODULEINFO));
    }

    // Find the start and end of the module for the pattern scanning
    uintptr_t baseStart = (uintptr_t)mod_info.lpBaseOfDll;
    uintptr_t baseEnd = baseStart + mod_info.SizeOfImage;

    // Look for patterns and find the correspoding address
    BYTE* stress_hook = (BYTE*)PatternScan((char*)baseStart, baseEnd, 
        "\xF3\x0F\x11\x8E\xE4\x0D\x00\x00\x38", "xxxxxxxxx");

    BYTE* player_health_hook = (BYTE*)PatternScan((char*)baseStart, baseEnd, 
        "\xF3\x0F\x5C\x45\x0C\xF3\x0F\x11\x86\xAC\x0C\x00\x00", "xxxxxxxxxxxxx");

    BYTE* enemy_health_hook = (BYTE*)PatternScan((char*)baseStart, baseEnd, 
        "\xF3\x0F\x5C\xC1\xF3\x0F\x11\x83\xAC\x0C\x00\x00", "xxxxxxxxxxxx");

    // Declare bool variables for the activation of the cheats
    bool bStress = false, bPlayerHealth = false, bEnemyHealth = false;

    // Loop

    while (true)
    {
        if (GetAsyncKeyState(VK_END) & 1)
        {
            break;
        }

        if (GetAsyncKeyState(VK_NUMPAD1) & 1)
        {
            bStress = !bStress; 
            size_t bytes_to_erase = 8;

            if (bStress)
            {
                std::cout << "Stress Cheat activated.\n";
                HookCall((BYTE*)StressCheat, stress_hook, bytes_to_erase);
            }

            else
            {
                std::cout << "Stress Cheat deactivated.\n";
                RestoreBytes(stress_hook, (BYTE*)"\xF3\x0F\x11\x8E\xE4\x0D\x00\x00", bytes_to_erase);
            }
        }

        if (GetAsyncKeyState(VK_NUMPAD2) & 1)
        {
            bPlayerHealth = !bPlayerHealth;
            size_t bytes_to_erase = 5;

            if (bPlayerHealth)
            {
                std::cout << "Player Health Cheat activated.\n";
                HookCall((BYTE*)HealthCheat, player_health_hook, bytes_to_erase);
            }

            else
            {
                std::cout << "Player Health Cheat deactivated.\n";
                RestoreBytes(player_health_hook, (BYTE*)"\xF3\x0F\x5C\x45\x0C", bytes_to_erase);
            }
        }

        if (GetAsyncKeyState(VK_NUMPAD3) & 1)
        {
            bEnemyHealth = !bEnemyHealth;
            size_t bytes_to_erase = 12;

            if (bEnemyHealth)
            {
                std::cout << "Enemy OHKO Cheat activated.\n";
                HookCall((BYTE*)EnemyHealthCheat, enemy_health_hook, bytes_to_erase);
            }

            else
            {
                std::cout << "Enemy OHKO Cheat deactivated.\n";
                RestoreBytes(enemy_health_hook, (BYTE*)"\xF3\x0F\x5C\xC1\xF3\x0F\x11\x83\xAC\x0C\x00\x00", bytes_to_erase);
            }
        }

        Sleep(5);
    }
    
    fclose(file);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;

}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr));
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

