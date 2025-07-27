#!/bin/bash


echo "test record generation"
for i in 10 100 1000 10000; do
    echo "n: ${i}"
    srun ./test/generation.out $i
done
echo "------------------------------"

echo "test record serialization"
for i in 10 100 1000 10000; do
    echo "n: ${i}"
    srun ./test/serialization.out $i
done
echo "------------------------------"

echo "test partial reading with memory limit"
for i in 10 100 1000 10000; do
    for l in 25MB 50MB 100MB 200MB 500MB 1GB; do
        echo "n: ${i}, limit: ${l}"
        srun  ./test/partial_read.out $i $l
    done
done
echo "------------------------------"

echo "test basic sorting algorithm"
for i in 10 100 1000 10000; do
    echo "n: ${i}"
    srun  ./test/basic_sort.out $i
done
echo "------------------------------"

echo "test out-of-core blocks sorting"
for i in 10 100 1000 10000; do
    for l in 25MB 50MB 100MB 200MB 500MB 1GB; do
        echo "n: ${i}, limit: ${l}"
        srun  ./test/blocks.out $i $l
    done
done
echo "------------------------------"

echo "test out-of-core sorted blocks merging"
for i in 10 11 12 13 14 15; do
    for l in 25MB 50MB 100MB 200MB 500MB 1GB; do
        echo "exp: ${i}, limit: ${l}"
        srun  ./test/merge_blocks.out $i $l
    done
done
echo "------------------------------"

echo "test out-of-core sequential algorithm"
for i in 10 11 12 13 14 15; do
    for l in 25MB 50MB 100MB 200MB 500MB 1GB; do
        echo "exp: ${i}, limit: ${l}"
        srun  ./test/sequential.out $i $l
    done
done
echo "------------------------------"


echo "test out-of-core OpenMP algorithm"
export OMP_NUM_THREADS=4
for i in 10 11 12 13 14 15; do
    for l in 25MB 50MB 100MB 200MB 500MB 1GB; do
        echo "exp: ${i}, limit: ${l}"
        srun ./test/omp.out $i $l
    done
done
echo "------------------------------"

