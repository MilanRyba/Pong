#include <stdio.h>
#include <cstdint>
#include <iostream>

// #define APS

int main()
{
	uint32_t point_counter = 3;
	uint32_t left_score = 12;
	uint32_t right_score = 10;

	uint32_t value = 0;
#if defined(APS)
	for (uint32_t i = 0; i < point_counter; i++)
	value = (value << 1) | 1;
#else
	uint32_t left = 0;
	uint32_t right = 0;

	for (uint32_t i = 0; i < 16; i++)
	{
		if (i < right_score)
			right = (right << 1) | 1;
	}

	for (uint32_t i = 0; i < 16; i++)
	{
		if (i < left_score)
			left = (left >> 1) | 0x80000000;
	}

	value = left | right;
#endif

	printf("%x", value);
	std::cin.get();
}