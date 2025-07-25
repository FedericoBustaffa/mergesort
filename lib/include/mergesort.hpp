#ifndef MERGESORT_HPP
#define MERGESORT_HPP

#include <vector>

#include "buffer.hpp"
#include "record.hpp"

// --- internal.cpp ---
void mergesort(std::vector<record>& records);

void mergesort(buffer& records);

// --- external.cpp ---
void mergesort(const char* filepath, uint64_t limit);

#endif
