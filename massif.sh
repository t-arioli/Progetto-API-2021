#!/bin/bash
valgrind --tool=massif --massif-out-file=./test/out-files/massif-out-file ./GraphRanker < test/open_tests/input_5 > output
massif-visualizer ./test/out-files/massif-out-file
cd ./test/out-files
cp $"massif-out-file" ./backups/massif/$"$(date +%Y-%m-%d--%H:%M:%S)"
