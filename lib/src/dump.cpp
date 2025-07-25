#include "serialize.hpp"

void dump_record(const record& record, std::ofstream& file)
{
    file.write(reinterpret_cast<const char*>(&record.key()), sizeof(uint64_t));
    file.write(reinterpret_cast<const char*>(&record.length()),
               sizeof(uint32_t));
    file.write(record.payload(), record.length());
}

void dump_vector(const std::vector<record>& records, std::ofstream& file)
{
    for (const auto& r : records)
        dump_record(r, file);
}

void dump_vector(const std::vector<record>& records, const char* filepath)
{
    std::ofstream file(filepath, std::ios::trunc | std::ios::binary);
    dump_vector(records, file);
}
