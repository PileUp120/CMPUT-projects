#!/bin/bash
gcc -std=c99 -pedantic -Wall -Wextra -ftrapv -ggdb3 -fsanitize=address -o question5 question5.c && ./question5

