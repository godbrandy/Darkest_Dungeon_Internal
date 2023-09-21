#pragma once
#include "pch.h"

void* PatternScan(char* base, size_t size, const char* pattern, const char* mask);

void* PatternScanEx(HANDLE hProcess, uintptr_t begin, uintptr_t end, char* pattern, char* mask);

void* PatternScanExModule(HANDLE hProcess, wchar_t* exeName, wchar_t* module, char* pattern, char* mask);

