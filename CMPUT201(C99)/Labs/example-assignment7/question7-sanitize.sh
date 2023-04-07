#!/bin/bash
gcc -std=c99 -pedantic -Wall -Wextra -ftrapv -ggdb3 -fsanitize=address $* -o question7 question7.c && ./question7
