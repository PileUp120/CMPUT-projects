#!/bin/bash
gcc -std=c99 -pedantic -Wall -Wextra -ftrapv -ggdb3 -fsanitize=address -o question4 question4.c && ./question4

