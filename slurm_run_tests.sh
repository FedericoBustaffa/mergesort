#!/bin/bash


echo "test record generation"
for i in 10 100 1000 10000 100000; do
    echo "n: ${i}"
    srun ./test/generation.out $i
done
echo "------------------------------"

echo "test record serialization"
for i in 10 100 1000 10000 100000; do
    echo "n: ${i}"
    srun ./test/serialization.out $i
done
echo "------------------------------"

echo "test partial reading with memory limit"
for i in 10 100 1000 10000 100000; do
    for l in 10MB 20MB 50MB 100MB 250MB 500MB 1GB 2GB; do
        echo "n: ${i}, limit: ${l}"
        srun ./test/partial_read.out $i $l
    done
done
echo "------------------------------"

echo "test basic sorting algorithm"
for i in 10 100 1000 10000 100000; do
    echo "n: ${i}"
    srun ./test/basic_sort.out $i
done
echo "------------------------------"

echo "test out-of-core blocks sorting"
for i in 10 100 1000 10000 100000; do
    for l in 10MB 20MB 50MB 100MB 250MB 500MB 1GB 2GB; do
        echo "n: ${i}, limit: ${l}"
        srun ./test/blocks.out $i $l
    done
done
echo "------------------------------"

echo "test out-of-core sorted blocks merging"
for i in 10 15 20; do
    for l in 10MB 20MB 50MB 100MB 250MB 500MB 1GB 2GB; do
        echo "exp: ${i}, limit: ${l}"
        srun ./test/merge_blocks.out $i $l
    done
done
echo "------------------------------"

echo "test out-of-core out-of-core sequential algorithm"
for i in 10 15 20; do
    for l in 10MB 20MB 50MB 100MB 250MB 500MB 1GB 2GB; do
        echo "exp: ${i}, limit: ${l}"
        srun ./test/sequential.out $i $l
    done
done
echo "------------------------------"
