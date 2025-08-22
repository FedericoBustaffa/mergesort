#!/bin/bash


for i in 256MB 512MB 1GB 2GB 4GB; do
    for j in 32MB 64MB 128MB 256MB 512MB 1GB 2GB; do
        ./benchmark/read_write.out $i $j
    done
done
