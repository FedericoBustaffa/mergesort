#include "mergesort.hpp"

#include <cmath>
#include <filesystem>
#include <sstream>

#include "serialize.hpp"

namespace fs = std::filesystem;

void merge(const char* filepath1, const char* filepath2, uint64_t limit)
{
    std::ifstream in1(filepath1, std::ios::binary);
    std::ifstream in2(filepath2, std::ios::binary);

    std::vector<record> blk1 = load_vector(in1, limit / 4);
    std::vector<record> blk2 = load_vector(in2, limit / 4);

    std::vector<record> buffer;
    buffer.reserve((limit / 2) / 20);
    uint64_t bufsize = 0; // in bytes

    size_t i1 = 0, i2 = 0;
    while (!blk1.empty() && !blk2.empty())
    {
        while (i1 < blk1.size() && i2 < blk2.size() && bufsize < limit / 2)
        {
            if (blk1[i1].key() <= blk2[i2].key())
                buffer.push_back(std::move(blk1[i1++]));
            else
                buffer.push_back(std::move(blk2[i2++]));

            bufsize +=
                sizeof(uint64_t) + sizeof(uint32_t) + buffer.back().length();
        }

        if (i1 >= blk1.size())
        {
            blk1 = load_vector(in1, limit / 4);
            i1 = 0;
        }
        else if (i2 >= blk2.size())
        {
            blk2 = load_vector(in2, limit / 4);
            i2 = 0;
        }

        if (bufsize >= limit / 2)
        {
            omp_dump_vector(buffer, "merged.bin");
            buffer.clear();
            bufsize = 0;
        }
    }

    // create some convenience aliases to simplify the code
    std::vector<record>& last_blk = blk1.empty() ? blk2 : blk1;
    size_t idx = blk1.empty() ? i2 : i1;
    std::ifstream& in_last = blk1.empty() ? in2 : in1;

    // consume the remaining file
    while (!last_blk.empty())
    {
        while (idx < last_blk.size() && bufsize < limit / 2)
        {
            buffer.push_back(std::move(last_blk[idx++]));
            bufsize +=
                sizeof(uint64_t) + sizeof(uint32_t) + buffer.back().length();
        }

        if (idx >= last_blk.size())
        {
            last_blk = load_vector(in_last, limit / 2);
            idx = 0;
        }
        else
        {
            omp_dump_vector(buffer, "merged.bin");
            buffer.clear();
            bufsize = 0;
        }
    }

    omp_dump_vector(buffer, "merged.bin");
    in1.close();
    in2.close();

    fs::remove(filepath1);
    fs::remove(filepath2);
    fs::rename("merged.bin", filepath1);
}

void omp_mergesort(const char* filepath, uint64_t limit)
{
    // blocks sorting
    std::ifstream file(filepath, std::ios::binary);
    std::vector<record> block = load_vector(file, limit / 2);

    std::stringstream ss;
    size_t block_counter = 0;
    while (!block.empty())
    {
        // sort the block
        omp_mergesort(block);

        // save the sorted block to a file
        ss << "block_" << block_counter++ << ".bin";
        omp_dump_vector(block, ss.str().c_str());

        // reset the stringstream
        ss.str("");
        ss.clear();

        // read the next block
        block = load_vector(file, limit / 2);
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
