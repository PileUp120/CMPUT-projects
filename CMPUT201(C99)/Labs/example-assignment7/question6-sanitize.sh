#!/bin/bash
gcc -std=c99 -pedantic -Wall -Wextra -ftrapv -ggdb3 -fsanitize=address -o question6 question6.c && ./question6

