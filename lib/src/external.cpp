#include "mergesort.hpp"

#include <cmath>
#include <filesystem>
#include <sstream>

#include "serialize.hpp"

namespace fs = std::filesystem;

void merge(const char* filepath1, const char* filepath2, uint64_t limit) {}

void mergesort(const char* filepath, uint64_t limit)
{
    // blocks sorting
    std::ifstream file(filepath, std::ios::binary);
    buffer block = load_buffer(file, limit / 2);

    std::stringstream ss;
    size_t block_counter = 0;
    while (!block.empty())
    {
        std::printf("block size: %lu\n", block.size());

        // sort the block
        mergesort(block);
        std::printf("block size: %lu\n", block.size());

        // save the sorted block to a file
        ss << "block_" << block_counter++ << ".bin";
        dump_buffer(block, ss.str().c_str());

        // reset the stringstream
        ss.str("");
        ss.clear();

        // read the next block
        block = load_buffer(file, limit / 2);
    }

    // blocks merging
    std::string filepath1, filepath2;
    for (size_t i = 0; i < std::ceil(std::log2(block_counter)); i++)
    {
        for (size_t j = 0; j < block_counter; j += 2 * std::pow(2, i))
        {
            // compute second file index
            size_t j2 = j + std::pow(2, i);
            if (j2 < block_counter)
            {
                ss << "block_" << j << ".bin";
                filepath1 = ss.str();
                ss.str("");
                ss.clear();

                ss << "block_" << j2 << ".bin";
                filepath2 = ss.str();
                ss.str("");
                ss.clear();

                merge(filepath1.c_str(), filepath2.c_str(), limit);
            }
        }
    }
    fs::rename("block_0.bin", filepath);
}
