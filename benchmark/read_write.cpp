#include <chrono>
#include <cstdio>
#include <fstream>
#include <random>

#include "utils.hpp"

void init_buffer(char* buffer, size_t length)
{
    std::mt19937 generator;
    std::uniform_int_distribution<char> distribution(0, 127);

    for (size_t i = 0; i < length; i++)
        buffer[i] = distribution(generator);
}

double write_benchmark(const char* buffer, uint64_t bufsize, uint64_t chunksize)
{
    double sum = 0.0;
    for (size_t i = 0; i < 10; i++)
    {
        std::ofstream file("output.bin", std::ios::binary);
        size_t counter = 0;
        auto start = std::chrono::high_resolution_clock::now();
        while (counter < bufsize)
        {
            file.write(buffer + counter, chunksize);
            counter += chunksize;
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        sum += duration.count();
    }

    return sum / 10.0;
}

double read_benchmark(char* buffer, uint64_t bufsize, uint64_t chunksize)
{
    double sum = 0.0;
    for (size_t i = 0; i < 10; i++)
    {
        std::ofstream file("output.bin", std::ios::binary);
        size_t counter = 0;
        auto start = std::chrono::high_resolution_clock::now();
        while (counter < bufsize)
        {
            file.write(buffer + counter, chunksize);
            counter += chunksize;
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        sum += duration.count();
    }

    return sum / 10.0;
}

int main(int argc, const char** argv)
{
    if (argc != 3)
    {
        std::printf("USAGE: %s <bufsize> <chunksize>\n", argv[0]);
        return 1;
    }

    uint64_t bufsize = parse_memory(argv[1]);
    uint64_t chunksize = parse_memory(argv[2]);
    std::printf("bufsize: %s\n", argv[1]);
    std::printf("chunksize: %s\n", argv[2]);

    char* buffer = new char[bufsize];
    init_buffer(buffer, bufsize);

    // write benchmark
    double wtime = write_benchmark(buffer, bufsize, chunksize);
    std::printf("write time: %.6f seconds\n", wtime);

    // read benchmark
    double rtime = read_benchmark(buffer, bufsize, chunksize);
    std::printf("read time: %.6f seconds\n", rtime);

    delete[] buffer;

    std::ofstream results("results/read_write.csv", std::ios::app);
    results << bufsize << ",";
    results << chunksize << ",";
    results << wtime << ",";
    results << rtime << std::endl;

    return 0;
}
