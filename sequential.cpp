#include <algorithm>
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
    uint64_t limit = parse_mem_limit(argv[2]);
    if (limit == 0)
    {
        std::printf("USAGE: %s <E> <L>[K|M|G]B\n", argv[0]);
        return 1;
    }

    // generate and save shuffled vector
    std::vector<record> records = generate_records(n, 256);
    dump_vector(records, "vector.bin");

    // sort and generate a file with sorted array
    auto start = std::chrono::high_resolution_clock::now();
    mergesort("vector.bin", limit);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // check if the array is sorted correctly
    std::vector<record> result = load_vector("vector.bin");

    assert(result.size() == records.size());
    assert(!std::equal(records.begin(), records.end(), result.begin(),
                       result.end()));
    assert(!std::is_sorted(records.begin(), records.end()));
    assert(std::is_sorted(result.begin(), result.end()));

    uint64_t filesize = fs::file_size("vector.bin");
    std::printf("file size: %s\n", bytes_to_string(filesize).c_str());
    std::printf("elements: %lu\n", n);
    std::printf("limit: %s\n", argv[2]);
    std::printf("time: %.4f seconds\n", duration.count());

    return 0;
}
