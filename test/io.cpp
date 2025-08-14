#include <chrono>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <random>

#include "utils.hpp"

namespace fs = std::filesystem;

int main(int argc, const char** argv)
{
    if (argc != 2)
    {
        std::printf("USAGE: %s <mem>\n", argv[0]);
        return 1;
    }
    uint64_t memory = parse_memory(argv[1]);

    char* buffer = new char[memory];
    std::mt19937 generator(42);
    std::uniform_int_distribution<char> dist(0, 127);
    for (uint64_t i = 0; i < memory; i++)
        buffer[i] = dist(generator);

    std::ofstream out("temp.txt", std::ios::trunc | std::ios::binary);
    auto start = std::chrono::high_resolution_clock::now();
    out.write(reinterpret_cast<const char*>(buffer), memory);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::printf("%lu written in %.4f seconds\n", memory, elapsed.count());
    out.close();

    std::ifstream in("temp.txt", std::ios::binary);
    start = std::chrono::high_resolution_clock::now();
    in.read(buffer, memory);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::printf("%lu read in %.4f seconds\n", memory, elapsed.count());
    in.close();

    delete[] buffer;

    fs::remove("temp.txt");

    return 0;
}
