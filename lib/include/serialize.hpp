#ifndef SERIALIZE_HPP
#define SERIALIZE_HPP

#include <fstream>
#include <vector>

#include "record.hpp"

// --- dump.cpp ---
void dump_record(const record& record, std::ofstream& file);

void dump_vector(const std::vector<record>& records, std::ofstream& file);

void dump_vector(const std::vector<record>& records, const char* filepath);

// --- omp_dump.cpp ---
void omp_dump_record(const record& record, size_t offset, std::ofstream& file);

void omp_dump_vector(const std::vector<record>& records, const char* filepath);

// --- load.cpp ---
record load_record(std::ifstream& file);

std::vector<record> load_vector(std::ifstream& file, uint64_t limit = 0);

std::vector<record> load_vector(const char* filepath, uint64_t limit = 0);

#endif
