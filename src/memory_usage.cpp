#include <iostream>
#include <vector>
#include <functional>
#include <cmath>

#include "memory_usage.h"

void MemUasge::print_usage() {
	uint32_t u = allocated - freed;
	std::cout << "Memory Usage: " << u << " bytes" << std::endl;
}

uint32_t MemUasge::get_usage() {
	uint32_t u = allocated - freed;
	return u;
}

MemUasge memoryUsage;

void* operator new(size_t size) {
	memoryUsage.allocated += 1;

	return malloc(size);
}


void operator delete(void* mem, size_t size) {
	memoryUsage.freed += 1;

	free(mem);
}

void operator delete(void* mem) {
	memoryUsage.freed += 1;

	free(mem);
}