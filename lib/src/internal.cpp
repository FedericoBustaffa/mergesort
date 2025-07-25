#include "mergesort.hpp"

#include <cmath>

void merge(std::vector<uint64_t>& keys, size_t first, size_t middle,
           size_t last, std::vector<uint64_t>& support,
           std::vector<size_t>& indices)
{
    size_t left = first, right = middle;
    size_t i = first;

    while (left < middle && right < last)
    {
        // merge
        if (keys[left] <= keys[right])
        {
            support[i] = keys[left];
            indices[i++] = left++;
        }
        else
        {
            support[i] = keys[right];
            indices[i++] = right++;
        }

        // consume remaining array
        if (left >= middle)
        {
            while (right < last)
            {
                support[i] = keys[right];
                indices[i++] = right++;
            }
        }
        else
        {
            while (left < middle)
            {
                support[i] = keys[left];
                indices[i++] = left++;
            }
        }

        // copy the support array in the original
        for (size_t i = first; i < last; i++)
            keys[i] = support[i];
    }
}

void sort(std::vector<uint64_t> keys, size_t first, size_t last,
          std::vector<uint64_t>& support, std::vector<size_t>& indices)
{
    if (last - first <= 1)
        return;

    size_t middle = std::ceil((first + last) / 2);
    sort(keys, first, middle, support, indices);
    sort(keys, middle, last, support, indices);
    merge(keys, first, middle, last, support, indices);
}

template <typename T>
void sort_idx(std::vector<T>& v, const std::vector<size_t>& indices)
{
    std::vector<T> support(v.size());
    for (size_t i = 0; i < indices.size(); i++)
        support[i] = v[indices[i]];

    for (size_t i = 0; i < indices.size(); i++)
        v[i] = support[i];
}

void mergesort(buffer& records)
{
    std::vector<uint64_t> support(records.size());
    std::vector<size_t> indices(records.size(), 0);
    for (size_t i = 0; i < indices.size(); i++)
        indices[i] = i;

    sort(records.keys(), 0, records.size(), support, indices);
    sort_idx(records.lengths(), indices);
    sort_idx(records.payloads(), indices);
}
