#!/bin/bash
gcc -Wall -Werror -O2 -g3 testVerificator.c -o testVerificator
echo TEST 1
./GraphRanker < test/open_tests/input_1 > output
./testVerificator test/open_tests/output_1
rm output
echo TEST 2
./GraphRanker < test/open_tests/input_2 > output
./testVerificator test/open_tests/output_2
rm output
echo TEST 3
./GraphRanker < test/open_tests/input_3 > output
./testVerificator test/open_tests/output_3
rm output
echo TEST 4
./GraphRanker < test/open_tests/input_4 > output
./testVerificator test/open_tests/output_4
rm output
echo TEST 5
./GraphRanker < test/open_tests/input_5 > output
./testVerificator test/open_tests/output_5
rm output
echo TEST 6
./GraphRanker < test/open_tests/input_6 > output
./testVerificator test/open_tests/output_6

