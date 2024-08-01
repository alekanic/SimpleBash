#include "s21_cat.h"

int main(int count, char *commands[]) {
  options flags = {0};

  if (count == 1) {  // если 1 аргумент, то мы построчно дублируем поток ввода
                     // до EOF (^D)
    cat_print(stdin, NULL);
  } else if (commands[1][0] == '-') {  // находим что-то похожее на флаг
    argument_parser(count, commands, &flags);
    if (!flags.count_lines && optind) {  // если не было ошибки и считаны опции
      cat_file(count, commands, &flags);
    }
  } else {
    cat_file(count, commands, NULL);
  }

  return 0;
}

void cat_print(FILE *file, options *flags) {
  char current_ch;
  char prev_ch = '\n';

  if (flags) {  // без этого цикла все ломается
    flags->count_lines = 1;
  }

  while ((current_ch = fgetc(file)) != EOF) {
    if (flags) {
      cat_symbol(flags, &current_ch, &prev_ch, file);
    }
    if (current_ch != EOF) {
      fputc(current_ch, stdout);
      prev_ch = current_ch;
    }
  }
}

/* Функция открывает файл на чтение, либо выводит ошибку */

void cat_file(int count, char *commands[], options *flags) {
  for (int i = optind; i < count; i++) {
    FILE *file = fopen(commands[i], READ_MODE);
    if (file) {
      cat_print(file, flags);
    } else {
      fprintf(stderr, "cat: %s: No such file or directory\n", commands[i]);
    }
    fclose(file);
  }
}

/*
Функция getopt_long() обрабатывает аргументы командной строки и в случае
совпадения с какой-либо из заданных опций возвращает int значение данного
символа. В ином случае возаращает символ '?', если короткая опция, и 0 в случае
длинной опции
*/

void argument_parser(int count, char **commands, options *flags) {
  const struct option long_options[] = {{"b_option", NO_ARGUMENT, NULL, 'b'},
                                        {"n_option", NO_ARGUMENT, NULL, 'n'},
                                        {"s_option", NO_ARGUMENT, NULL, 's'},
                                        {NULL, 0, NULL, 0}};

  int ch;
  while ((ch = getopt_long(count, commands, SHORT_OPTIONS, long_options,
                           NULL)) != GETOPT_END) {
    switch (ch) {
      case 'b':
        flags->b = true;
        break;
      case 'n':
        flags->n = true;
        break;
      case 's':
        flags->s = true;
        break;
      case 'e':
        flags->e = true;
        flags->v = true;
        break;
      case 'E':
        flags->E = true;
      case 't':
        flags->t = true;
        flags->v = true;
        break;
      case 'T':
        flags->t = true;
      case 'v':
        flags->v = true;
        break;
      default:
        flags->count_lines = 1;
        break;
    }
  }
}

void cat_symbol(options *flags, char *current_ch, char *prev_ch, FILE *file) {
  count_empty_line(current_ch, prev_ch, flags);
  squeeze_line(current_ch, file, flags);
  if (*current_ch != EOF) {
    check_the_new(*prev_ch, flags);
    non_printed((unsigned char *)current_ch, flags);
  }
}

/* Функция проверяем началась ли новая строка, и если были использованы флаги -b
 * или -n выводит номера соовтетственно */

void check_the_new(char prev_ch, options *flags) {
  if (prev_ch == '\n' && (flags->b || flags->n)) {
    if (!flags->b) {
      printf("%6d\t", flags->count_lines);
      flags->count_lines++;
    } else {
      flags->n = false;
      if (flags->empty_lines < 1) {
        printf("%6d\t", flags->count_lines);
        flags->count_lines++;
      }
    }
  }
}

void non_printed(unsigned char *current_ch, options *flags) {
  if (flags->e && *current_ch == '\n') {
    printf("$");
  }

  if (flags->t) {
    while (*current_ch == 9) {
      printf("^");
      *current_ch = 73;
    }
  }

  if (flags->v && (*current_ch != '\n' && *current_ch != '\t')) {
    if (*current_ch == '\n' || *current_ch == '\t') {
      *current_ch = *current_ch;
    } else if (*current_ch < 32) {
      printf("^");
      *current_ch += NONPRINTING_SHIFT;
    } else if (*current_ch == ASCII_DEL) {
      printf("^");
      *current_ch = '?';
    } else if (*current_ch >= 128 && *current_ch < 161) {
      printf("M-^");
      *current_ch -= NONPRINTING_SHIFT;
    }
  }
}

/* Функция подчсета пустых строк и обработки флага -s */

void count_empty_line(char *current_ch, char *prev_ch, options *flags) {
  if (*prev_ch == '\n' && *current_ch == '\n') {
    flags->empty_lines++;
  } else {
    flags->empty_lines = 0;
  }
}

/* Будет считывать символы из файла, пока не упрется в непустую строку */

void squeeze_line(char *current_ch, FILE *file, options *flags) {
  if (flags->s && flags->empty_lines > 1) {
    while (*current_ch == '\n') {
      *current_ch = fgetc(file);
    }
    flags->empty_lines = 0;
  }
}