#!/bin/bash


sizes=(
    1MB
    2MB
    4MB
    8MB
    16MB
    32MB
    64MB
    128MB
    256MB
    512MB
    1GB
    2GB
    4GB
    8GB
)

for i in ${sizes[@]}; do
    ./sequential.out $1 $i
    echo "----------"
done
