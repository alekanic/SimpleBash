SHELL := /bin/bash

FLAG = -Wall -Wextra -Werror

all: s21_grep

s21_grep: clean
	gcc $(FLAG) s21_grep.c -o s21_grep

make_style:

	clang-format -i  *.c *.h

style:

	clang-format -n *.c *.h

leaks:

	leaks -atExit -- ./s21_grep

tests:

	sh test_func_grep.sh

clean:

	rm -rf s21_grep
	rm -rf *.o
	rm -rf *.out
	rm -rf *.log

rebuild: clean s21_grep