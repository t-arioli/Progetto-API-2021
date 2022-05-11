#!/bin/bash
gcc -DEVAL -Wall -Werror -std=gnu11 -O2 -pipe -static -s -o GraphRanker GraphRanker.c -lm