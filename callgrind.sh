#!/bin/bash
valgrind --tool=callgrind --callgrind-out-file=./test/out-files/callgrind-out-file ./GraphRanker <test/open_tests/input_1 >output
kcachegrind test/out-files/callgrind-out-file
cd ./test/out-files
cp $"callgrind-out-file" ./backups/callgrind/$"$(date +%Y-%m-%d--%H:%M:%S)"
cd ../../
valgrind --tool=callgrind --callgrind-out-file=./test/out-files/callgrind-out-file ./GraphRanker <test/open_tests/input_2 >output
kcachegrind test/out-files/callgrind-out-file
cd ./test/out-files
cp $"callgrind-out-file" ./backups/callgrind/$"$(date +%Y-%m-%d--%H:%M:%S)"
cd ../../
valgrind --tool=callgrind --callgrind-out-file=./test/out-files/callgrind-out-file ./GraphRanker <test/open_tests/input_3 >output
kcachegrind test/out-files/callgrind-out-file
cd ./test/out-files
cp $"callgrind-out-file" ./backups/callgrind/$"$(date +%Y-%m-%d--%H:%M:%S)"
cd ../../
valgrind --tool=callgrind --callgrind-out-file=./test/out-files/callgrind-out-file ./GraphRanker <test/open_tests/input_4 >output
kcachegrind test/out-files/callgrind-out-file
cd ./test/out-files
cp $"callgrind-out-file" ./backups/callgrind/$"$(date +%Y-%m-%d--%H:%M:%S)"
cd ../../
valgrind --tool=callgrind --callgrind-out-file=./test/out-files/callgrind-out-file ./GraphRanker <test/open_tests/input_5 >output
kcachegrind test/out-files/callgrind-out-file
cd ./test/out-files
cp $"callgrind-out-file" ./backups/callgrind/$"$(date +%Y-%m-%d--%H:%M:%S)"
cd ../../
valgrind --tool=callgrind --callgrind-out-file=./test/out-files/callgrind-out-file ./GraphRanker <test/open_tests/input_6 >output
kcachegrind test/out-files/callgrind-out-file
cd ./test/out-files
cp $"callgrind-out-file" ./backups/callgrind/$"$(date +%Y-%m-%d--%H:%M:%S)"
cd ../../


