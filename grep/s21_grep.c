#include "s21_grep.h"

int main(int count, char *commands[]) {
  options arg = argument_parser(count, commands);
  output(&arg, count, commands);
  return 0;
}

options argument_parser(int count, char *commands[]) {
  options arg = {0};
  int opt;
  while ((opt = getopt_long(count, commands, SHORT_OPTIONS, 0, 0)) !=
         GETOPT_END) {
    switch (opt) {
      case 'e':  // добавляем паттерн
        if (optarg != NULL) {
          arg.e = 1;
          if (arg.common_pattern[0] != '\0') {
            strcat(arg.common_pattern, "|");
          }
          strcat(arg.common_pattern, optarg);
        }
        break;
      case 'i':  // игнор различия регистра
        arg.i = 1;
        break;
      case 'v':  // инвертирует смысл поиска соответствий
        arg.v = 1;
        break;
      case 'c':  // выводит только количество совпадающих строк
        arg.c = 1;
        break;
      case 'l':  // выводит только совпадающие файлы
        arg.l = 1;
        break;
      case 'n':  // предваряет каждую строку ывода номером строки из файла ввода
        arg.n = 1;
        break;
      case 'h':  // выводит совпадающие строки, без имен файлов
        arg.h = 1;
        break;
      case 's':  // подавляет сообщения об ошибках о несуществующих или
                 // нечитаемых файлах
        arg.s = 1;
        break;
      case 'f':  // получает регулярные выражения из файла
        if (optarg != NULL) {
          arg.f = 1;
          add_pattern_from_file(&arg, optarg);
        }
        break;
      case 'o':  // печатает только совпадающие (непустые) части совпавшей
                 // строки
        arg.o = 1;
        break;
      default:
        perror("ERROR");
        exit(1);
        break;
    }
  }

  return arg;
}

// вывод из всех файлов
// тут мы компилируем регулярку

void output(options *arg, int count, char **commands) {
  regex_t reg_struct;
  char *pattern = NULL;
  int error;
  int file_index = optind + 1;
  arg->several_files = 0;

  if (arg->e == 1 || arg->f == 1) {
    file_index = optind;
    pattern = arg->common_pattern;
  } else {
    pattern = commands[optind];
  }

  if (file_index < count - 1) {
    arg->several_files = 1;
  }

  // если что-то пошло не так, выводит ошибки
  if (arg->i == 1) {
    error = regcomp(&reg_struct, pattern, REG_ICASE | REG_EXTENDED);
  } else {
    error = regcomp(&reg_struct, pattern, REG_EXTENDED);
  }
  if (error) {
    perror("Error with regcomp in output()\n");
    exit(1);
  }

  // делаем вывод на несколько файлов
  for (int i = file_index; i < count; i++) {
    process_file(arg, commands[i], reg_struct);
  }

  regfree(&reg_struct);
}

/* Если у нас в конце символ переноса на новую строчку, мы ее вручную добавляем,
 * это для поиска */

void output_line(char *line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  // если в конце нашей строчки символ перевода на новую строку,
  if (line[n - 1] != '\n') {
    putchar('\n');
  }
}

void print_match(regex_t *reg_struct, char *line, options *arg, char *path,
                 int line_count) {
  regmatch_t match;
  int offset = 0;
  int iteration = 0;

  while (1) {
    int result = regexec(reg_struct, line + offset, 1, &match, 0);
    if (result != 0) {  // 0 означает, что совпадение есть
      break;
    }

    if (iteration > 0) {
      if (!arg->h && arg->several_files) {
        printf("%s:", path);
      }

      if (arg->n) {
        printf("%d:", line_count);
      }
    }

    for (int i = match.rm_so; i < match.rm_eo; i++) {
      putchar(line[offset + i]);
    }
    putchar('\n');
    offset += match.rm_eo;  // прибавляем значение конца строки, на котором //
                            // остановились
    iteration++;
  }
}

void add_pattern_from_file(options *arg, char *filepath) {
  FILE *file = fopen(filepath, READ_MODE);
  if (file == NULL) {
    if (!arg->c) {
      perror(filepath);
    }
    exit(1);
  }

  // создание переменных для функции getline
  char *line = NULL;
  int size;
  size_t memlen = 0;
  ssize_t read = getline(&line, &memlen, file);

  /*
   Если наш паттерн оканчивается на перенос строки по какой-то причине, то его
   не найдет наша программа Поэтому мы меняем паттерн так, чтобы он находился
  */

  while (read != GETLINE_END) {
    size = strlen(line);

    if (line[size - 1] == '\n' && read > 0) {
      line[size - 1] = '\0';
    }

    if (arg->common_pattern[0] != '\0') {
      strcat(arg->common_pattern, "|");
    }

    strcat(arg->common_pattern, line);
    // pattern_add(arg, line);

    read = getline(&line, &memlen, file);
  }

  free(line);
  fclose(file);
}

void process_file(options *arg, char *path, regex_t reg) {
  FILE *file = fopen(path, READ_MODE);
  if (file == NULL) {
    if (!arg->s) {
      perror(path);
    }
    exit(1);
  }

  char *line = NULL;
  size_t memlen = 0;
  ssize_t read = getline(&line, &memlen, file);
  size_t nmatch = 1;
  regmatch_t pmatch[1];
  int line_count = 1;
  int count = 0;  // в случае если совпадения найдено, делаем с + 1

  while (read != GETLINE_END) {
    // создаем переменную, которая будет хранить результат выполнения функции
    int result = regexec(&reg, line, nmatch, pmatch, 0);

    // если найдено совпадение сравниваем (0 - если совпадение найдено)
    if ((result == 0 && !arg->v) || (arg->v && result != 0)) {
      if (!arg->c && !arg->l) {
        if (!arg->h && arg->several_files) {
          printf("%s:", path);
        }

        if (arg->n) {
          printf("%d:", line_count);
        }

        if (arg->o && !arg->v) {
          print_match(&reg, line, arg, path, line_count);
        } else {
          output_line(line, read);
        }
      }
      count++;
    }

    read = getline(&line, &memlen, file);
    line_count++;
  }

  additional_print(arg, count, path);
  free(line);
  fclose(file);
}

void additional_print(options *arg, int count, char *path) {
  if (arg->several_files != 1) {  // если один файл
    if (arg->c && !arg->l) {
      printf("%d\n", count);
    } else if (arg->c && arg->l) {
      printf("%s\n%s\n", "1", path);
    }
  } else {  // если файлов несколько
    if (arg->c && !arg->l && !arg->h) {
      printf("%s:%d\n", path, count);
    } else if (arg->c && !arg->l && arg->h) {
      printf("%d\n", count);
    } else if (arg->c && arg->l) {
      if (count != 0) {
        printf("%s:%s\n%s\n", path, "1", path);
      } else {
        printf("%s:%d\n", path, count);
      }
    }
  }

  if (arg->l && !arg->c && count > 0) {
    printf("%s\n", path);
  }
}

/*

1. regex_t *prog: указатель на предварительно скомпилированное регулярное
выражение. Это выражение должно быть скомпилировано функцией regcomp перед
использованием regexec

2. const char *string - указатель на строку, в которой будет выполняться поиск
совпадений с регулярным выражением

3. size_t nmatch - максимальное количество совпадений, которые будут заполнены в
массиве pmatch. Если мы не заинтересованы в получении информации о
местоположении совпадений, установите это значение в 0

4. regmatch_t pmatch[] - массив структур regmatch который будет использован для
хранения информации о местоположении каждого совпадения в строке. Каждый элемент
массива содержит поля rm_so и rm_oo которые указывают начало и конец совпадения
Если match равно 0, pmatch может быть NULL

5. int eflags - дополнительные флаги, влияющие на выполнение поиска. Обычно
устанавливается в 0, но может принимать значения вроде "REG_NOTBOL" и
'REG_NOTEOL', которые указывают, что начало и конец строки не должны
рассматриваться как начало и конец буфера

regexec возвращает 0 при успешном сопоставлении, REG_NOMATCH, если совпадения не
найдены, или другой код ошибки при возникновении ошибки в процессе сопоставления

*/

/*
Обработка флага -о

regmatch_t match - структура для хранения позции совпадения
Так как мы не знаем, какое количество совпадений нам нужно обработать, мы
начинаем бесконечный цикл while (1)

Если находим совпадение в строке - смещаемся на offset
Ищем только одно совпадение, потому что пока нет смысла больше
Если нет совпадений - завершаем цикл

print_flags - печатаем номер строки или файла если есть соответствующие флаги
(выводит само совпадение с шаблоном используя переменные rm_so и end_so)

двигаем наш offset чтобы продолжить со следующего места

*/