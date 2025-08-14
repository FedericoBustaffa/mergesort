#include <cassert>
#include <cstdio>
#include <filesystem>
#include <fstream>

#include "record.hpp"
#include "serialize.hpp"
#include "utils.hpp"

namespace fs = std::filesystem;

int main(int argc, const char** argv)
{
    if (argc != 3)
    {
        std::printf("USAGE: %s <N> <L>\n", argv[0]);
        return 1;
    }
    uint64_t n = std::stoull(argv[1]);      // # of records
    uint64_t limit = parse_memory(argv[2]); // max bytes

    // generate and save records to a file
    std::vector<record> records = generate_records(n, 64);
    uint64_t bytes = mem_usage(records);
    // std::printf("total bytes produced: %lu\n", bytes);

    std::ofstream out("records.bin", std::ios::binary);
    dump_vector(records, out);
    out.close();

    // partial reading with limits
    std::vector<record> temp;
    std::vector<record> records2;
    std::ifstream in("records.bin", std::ios::binary);
    while (true)
    {
        temp = load_vector(in, limit);
        if (temp.empty())
            break;

        bytes = mem_usage(temp);
        for (const auto& i : temp)
            records2.push_back(std::move(i));

        assert(bytes <= limit);
        // std::printf("bytes: %lu\n", bytes);
    }
    in.close();

    assert(std::equal(records.begin(), records.end(), records2.begin(),
                      records2.end()));

    fs::remove("records.bin");

    return 0;
}
