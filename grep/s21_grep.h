#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GETLINE_END -1
#define GETOPT_END -1
#define READ_MODE "r"

#define SHORT_OPTIONS "e:ivclnhsf:o"

typedef struct options {
  int e;  // шаблон
  int i;  // игнорирует различия регистра
  int v;  // инвертирует смысл поиска соответствий
  int c;  // выводит только количество совпадающих строк
  int l;  // выводит только совпадающие файлы
  int n;  // предваряет каждую строку вывода номером строки из файла ввода
  int h;  // выводит совпадающие строки, не предваряя их именами файлов
  int s;  // подавляет сообщения об ошибках о несуществующих или нечитаемых
          // файлах
  int f;  // получает регулярные выражения из файла
  int o;  // печатает только совпадающие (непустые) части совпавшей строки

  size_t file_count;

  // pattern common_pattern;
  char common_pattern[1024];
  int several_files;

} options;

void pattern_add(options *arg, char *pattern);
void add_pattern_from_file(options *arg, char *filepath);
options argument_parser(int count, char *commands[]);
void output_line(char *line, int n);
void print_match(regex_t *reg_struct, char *line, options *arg, char *path,
                 int line_count);
void process_file(options *arg, char *path, regex_t reg);
void output(options *arg, int count, char **commands);
void additional_print(options *arg, int count, char *path);
