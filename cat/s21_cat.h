#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SHORT_OPTIONS "bnsetv"
#define NO_ARGUMENT 0
#define GETOPT_END -1
#define READ_MODE "r"
#define NONPRINTING_SHIFT 64
#define ASCII_DEL 127

typedef struct {
  bool b;  // нумерует только непустые строки (non_blank_rows)
  bool n;  // нумерует все строки (all_rows)
  bool s;  // сжимает несколько смежных строк до одной (squeezed)
  bool e;  // отображает символы конца строки (show_end)
  bool t;  // отображает табы как ^| (show_tabs)
  bool v;  // отображает скрытые символы (show_all)
  int count_lines;  // можно использовать как идентификатор ошибки не валидных
  int empty_lines;
  bool E;
  bool T;
} options;

void cat_print(FILE *file, options *flags);
void cat_file(int count, char *commands[], options *flags);
void argument_parser(int count, char **commands, options *flags);
void cat_symbol(options *flags, char *current_ch, char *prev_ch, FILE *file);
void non_printed(unsigned char *current_ch, options *flags);
void count_empty_line(char *current_ch, char *prev_ch, options *flags);
void squeeze_line(char *current_ch, FILE *file, options *flags);
void check_the_new(char prev_ch, options *flags);