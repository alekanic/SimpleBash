SHELL := /bin/bash # без этой строчки работать не будет


GCC = gcc -Wall -Wextra -Werror 

all: s21_cat 

s21_cat: clean

	$(GCC) s21_cat.c -o s21_cat

tests:

	sh test_func_cat.sh

my_tests:

	sh s21_cat_test.sh

make_style:

	clang-format -i *.c *.h

style:

	clang-format -n *.c *.h

leaks:

	leaks -atExit -- ./s21_grep

clean:

	rm -rf s21_grep
	rm -rf *.o
	rm -rf *.out
	rm -rf *.log

rebuild: clean s21_grep