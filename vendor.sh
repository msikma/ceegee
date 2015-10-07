#!/usr/bin/env bash
# Copyright (C) 2015, Michiel Sikma <michiel@sikma.org>
# MIT License

DEPS=(
    'argparse::https://github.com/Cofyc/argparse.git::v1.0.0'
    'allegro::https://github.com/liballeg/allegro5.git::4.3'
    'xorshift::https://github.com/msikma/xorshift::master'
)
mkdir -p vendor

echo "Downloading vendor code..."
for n in "${DEPS[@]}" ; do
    dep="${n}"
    bits=(${dep//::/ })
    name=${bits[0]}
    url=${bits[1]}
    branch=${bits[2]}

    if [ -d "vendor/$name" ]; then
        echo "The 'vendor/$name' directory already exists; skipped."
    else
        cmd="git clone --depth 1 --branch $branch $url vendor/$name"
        run=$($cmd 2>&1)
        echo "Cloned $url into 'vendor/$name' ('$branch')"
    fi
done
