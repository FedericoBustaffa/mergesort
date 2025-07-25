#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <cstdint>
#include <vector>

#include "record.hpp"

class buffer
{
public:
    buffer() = default;

    void add(record&& r)
    {
        m_keys.push_back(r.key());
        m_lengths.push_back(r.length());
        m_payloads.push_back(r.payload());
    }

    inline size_t size() const { return m_keys.size(); }

    inline std::vector<uint64_t>& keys() { return m_keys; }

    inline std::vector<uint32_t>& lengths() { return m_lengths; }

    inline std::vector<const char*>& payloads() { return m_payloads; }

    ~buffer() {}

private:
    std::vector<uint64_t> m_keys;
    std::vector<uint32_t> m_lengths;
    std::vector<const char*> m_payloads;
};

#endif
