#include <cassert>
#include <chrono>
#include <cstdio>
#include <filesystem>

#include "mergesort.hpp"
#include "serialize.hpp"
#include "utils.hpp"

namespace fs = std::filesystem;

int main(int argc, const char** argv)
{
    if (argc != 3)
    {
        std::printf("USAGE: %s <E> <L>[K|M|G]B\n", argv[0]);
        return 1;
    }
    uint64_t n = 1ULL << std::stoul(argv[1]);
    uint64_t limit = parse_memory(argv[2]);
    if (limit == 0)
    {
        std::printf("USAGE: %s <E> <L>[K|M|G]B\n", argv[0]);
        return 1;
    }

    // generate and save shuffled vector
    std::vector<record> records = generate_records(n, 256);
    omp_dump_vector(records, "vector.bin");

    // sort and generate a file with sorted array
    auto start = std::chrono::high_resolution_clock::now();
    omp_mergesort("vector.bin", limit);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::printf("time: %.4f s\n", elapsed.count());

    fs::remove("vector.bin");

    return 0;
}
