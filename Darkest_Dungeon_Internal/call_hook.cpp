#include "call_hook.h"
#include "pch.h"

void HookCall(BYTE* cheat_func, BYTE* byte_to_hook, size_t size)
{
    DWORD old_protection;
    VirtualProtect(byte_to_hook, size, PAGE_EXECUTE_READWRITE, &old_protection);
    memset(byte_to_hook, 0x90, size);

    uintptr_t relative_addr = (uintptr_t)cheat_func - (uintptr_t)byte_to_hook - 5;

    *byte_to_hook = 0xE8;
    *(uintptr_t*)(byte_to_hook + 1) = relative_addr;

    VirtualProtect(byte_to_hook, size, old_protection, &old_protection);
}

void RestoreBytes(BYTE* byte_to_hook, BYTE* bytes_to_restore, size_t size)
{
    DWORD old_protection;
    VirtualProtect(byte_to_hook, size, PAGE_EXECUTE_READWRITE, &old_protection);
    memcpy(byte_to_hook, bytes_to_restore, size);
    VirtualProtect(byte_to_hook, size, old_protection, &old_protection);
}
