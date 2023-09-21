#pragma once

#include "pch.h"

void HookCall(BYTE* cheat_func, BYTE* byte_to_hook, size_t size);

void RestoreBytes(BYTE* byte_to_hook, BYTE* bytes_to_restore, size_t size);
