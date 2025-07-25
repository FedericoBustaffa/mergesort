#include "serialize.hpp"

#include "buffer.hpp"

record load_record(std::ifstream& file)
{
    uint64_t key;
    file.read(reinterpret_cast<char*>(&key), sizeof(uint64_t));
    size_t count = file.gcount();
    if (count < sizeof(uint64_t))
    {
        file.seekg(count - sizeof(uint64_t), std::ios::cur);
        return record();
    }

    uint32_t length;
    file.read(reinterpret_cast<char*>(&length), sizeof(uint32_t));
    count = file.gcount();
    if (count < sizeof(uint32_t))
    {
        file.seekg(count - sizeof(uint64_t) - sizeof(uint32_t), std::ios::cur);
        return record();
    }

    char* payload = new char[length];
    file.read(payload, length);
    count = file.gcount();
    if (count < length)
    {
        file.seekg(count - sizeof(uint64_t) - sizeof(uint32_t) - length);
        return record();
    }

    return record(key, length, payload);
}

std::vector<record> load_vector(std::ifstream& file, uint64_t limit)
{
    std::vector<record> buffer;
    record temp;
    uint64_t index = 0;
    while (true)
    {
        if (limit > 0 && limit - index < 20) // minimum record size
            return buffer;

        temp = load_record(file);
        if (!temp.is_valid())
            break;

        index += temp.size();
        if (limit > 0 && index > limit)
        {
            // rollback in case of exceeded limit
            file.seekg(-temp.size(), std::ios::cur);
            return buffer;
        }
        buffer.push_back(std::move(temp));
    }

    return buffer;
}

std::vector<record> load_vector(const char* filepath, uint64_t limit)
{
    std::ifstream file(filepath, std::ios::binary);
    return load_vector(file, limit);
}

buffer load_buffer(std::ifstream& file, uint64_t limit)
{
    buffer records;
    record temp;
    uint64_t index = 0;
    while (true)
    {
        if (limit > 0 && limit - index < 20)
            return records;

        temp = load_record(file);
        if (!temp.is_valid())
            break;

        index += temp.size();
        if (limit > 0 && index > limit)
        {
            file.seekg(-temp.size(), std::ios::cur);
            return records;
        }
        records.add(std::move(temp));
    }

    return records;
}

buffer load_buffer(const char* filepath, uint64_t limit)
{
    std::ifstream file(filepath, std::ios::binary);
    return load_buffer(file, limit);
}
