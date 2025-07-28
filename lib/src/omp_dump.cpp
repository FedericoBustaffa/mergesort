#include "serialize.hpp"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void omp_dump_record(const record& r, size_t offset, int fd)
{
    pwrite(fd, &r.key(), sizeof(uint64_t), offset);

    offset += sizeof(uint64_t);
    pwrite(fd, &r.length(), sizeof(uint32_t), offset);

    offset += sizeof(uint32_t);
    pwrite(fd, r.payload(), r.length(), offset);
}

void omp_dump_record(const record& r, size_t offset, const char* filepath)
{
    std::ofstream file(filepath,
                       std::ios::in | std::ios::out | std::ios::binary);
    file.seekp(offset);

    file.write(reinterpret_cast<const char*>(&r.key()), sizeof(uint64_t));
    file.write(reinterpret_cast<const char*>(&r.length()), sizeof(uint32_t));
    file.write(r.payload(), r.length());
    file.close();
}

void omp_dump_vector(const std::vector<record>& records, const char* filepath)
{
    size_t size = records.size();
    std::vector<size_t> offsets(size);
    size_t total_size = 0;
    for (size_t i = 0; i < size; ++i)
    {
        offsets[i] = total_size;
        total_size += sizeof(uint64_t) + sizeof(uint32_t) + records[i].length();
    }

    int fd = open(filepath, O_RDWR | O_CREAT, 0644);
#pragma omp parallel for
    for (size_t i = 0; i < size; ++i)
        omp_dump_record(records[i], offsets[i], fd);

    close(fd);
}
