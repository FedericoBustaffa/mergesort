#include <algorithm>
#include <cassert>
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
    dump_vector(records, "vector.bin");

    // sort and generate a file with sorted array
    omp_mergesort("vector.bin", limit);

    // check if the array is sorted correctly
    std::vector<record> result = load_vector("vector.bin");

    assert(result.size() == records.size());
    assert(!std::equal(records.begin(), records.end(), result.begin(),
                       result.end()));
    assert(!std::is_sorted(records.begin(), records.end()));
    assert(std::is_sorted(result.begin(), result.end()));

    fs::remove("vector.bin");

    return 0;
}
