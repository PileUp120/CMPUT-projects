#!/bin/bash
gcc -std=c99 -pedantic -Wall -Wextra -ftrapv -ggdb3 -fsanitize=address -o question3 question3.c && ./question3

