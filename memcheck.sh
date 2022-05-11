#!/bin/bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./GraphRanker < test/open_tests/input_5 >output
