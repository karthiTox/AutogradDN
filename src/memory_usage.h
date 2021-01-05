#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <cmath>

struct MemUasge {
	uint32_t allocated = 0;
	uint32_t freed = 0;

	void print_usage();
	uint32_t get_usage();
};

extern MemUasge memoryUsage;

void* operator new(size_t size);

void operator delete(void* mem, size_t size);