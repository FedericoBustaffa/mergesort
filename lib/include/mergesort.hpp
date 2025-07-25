#ifndef MERGESORT_HPP
#define MERGESORT_HPP

#include "buffer.hpp"

// --- internal.cpp ---
void mergesort(buffer& records);

// --- external.cpp ---
void mergesort(const char* filepath, uint64_t limit);

#endif
