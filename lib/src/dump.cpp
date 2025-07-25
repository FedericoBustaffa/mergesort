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

void dump_buffer(const buffer& records, std::ofstream& file)
{
    for (size_t i = 0; i < records.size(); i++)
    {
        file.write(reinterpret_cast<const char*>(&records.keys()[i]),
                   sizeof(uint64_t));

        file.write(reinterpret_cast<const char*>(&records.lengths()[i]),
                   sizeof(uint32_t));

        file.write(records.payloads()[i], records.lengths()[i]);
    }
}

void dump_buffer(const buffer& records, const char* filepath)
{
    std::ofstream file(filepath, std::ios::trunc | std::ios::binary);
    dump_buffer(records, file);
}
