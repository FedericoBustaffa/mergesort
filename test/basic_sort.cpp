#include <algorithm>
#include <cassert>
#include <cstdio>
#include <string>

#include "mergesort.hpp"
#include "utils.hpp"

int main(int argc, const char** argv)
{
    if (argc != 2)
    {
        std::printf("USAGE: %s <N>\n", argv[0]);
        return 1;
    }
    uint64_t n = std::stoul(argv[1]);

    // generate randomly initialized records
    std::vector<record> v = generate_records(n, 64);
    assert(!std::is_sorted(v.begin(), v.end()));

    mergesort(v);
    assert(std::is_sorted(v.begin(), v.end()));

    return 0;
}
