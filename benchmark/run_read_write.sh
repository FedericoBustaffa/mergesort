#!/bin/bash


for i in 1GB 2GB 4GB; do
    for j in 128MB 256MB 512MB; do
        ./benchmark/read_write.out $i $j
    done
done
