#include "pch.h"

//Internal Pattern Scan
void* PatternScan(char* base, size_t size, const char* pattern, const char* mask)
{
	size_t patternLength = strlen(mask);

	for (size_t i = 0; i < size - patternLength; i++)
	{
		bool found = true;
		for (size_t j = 0; j < patternLength; j++)
		{
			if (mask[j] != '?' && pattern[j] != *(base + i + j))
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			return (void*)(base + i);
		}
	}
	return nullptr;
}
