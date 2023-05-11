#include "s21_cat_options.h"

int get_options(int argc, char** argv, Flag_options* flags) {
  int var;
  int error_code = 0;

  while ((var = getopt_long(argc, argv, "bevnstET", long_options, NULL)) !=
         -1) {
    switch (var) {
      case 'b':
        flags->number_nonblank = 1;
        flags->number = 1;
        flags->flag_counter++;
        break;
      case 'e':
        flags->show_endline = 1;
        flags->show_nonprint = 1;
        flags->flag_counter++;
        break;
      case 'v':
        flags->show_nonprint = 1;
        flags->flag_counter++;
        break;
      case 'n':
        flags->number = 1;
        flags->flag_counter++;
        break;
      case 's':
        flags->squeeze_blank = 1;
        flags->flag_counter++;
        break;
      case 't':
        flags->show_tabs = 1;
        flags->show_nonprint = 1;
        flags->flag_counter++;
        break;
      case 'E':
        flags->show_endline = 1;
        flags->flag_counter++;
        break;
      case 'T':
        flags->show_tabs = 1;
        flags->flag_counter++;
        break;
      default:
        error_code = 2;
        break;
    }
  }
  return error_code;
}

void cat_flags(Flag_options flags, FILE* file) {
  int empty_line_counter = 0;
  int string_counter = 1;
  char* buffer = NULL;
  size_t len;
  ssize_t char_count;

  while ((char_count = getline(&buffer, &len, file)) != -1) {
    if (flags.squeeze_blank && empty_line_counter && (buffer[0] == '\n')) {
      empty_line_counter++;
    } else {
      if (buffer[0] == '\n') {
        empty_line_counter = 1;
      } else {
        empty_line_counter = 0;
      }
      if (flags.number_nonblank) {
        if (buffer[0] != '\n') {
          printline_number(string_counter);
          string_counter++;
        }
      } else if (flags.number) {
        printline_number(string_counter);
        string_counter++;
      }
      if (flags.show_nonprint) {
        nonprint(buffer, flags, char_count);
      } else {
        tabs_endline(buffer, flags, char_count);
      }
    }
  }
  if (buffer) {
    free(buffer);
  }
}

void printline_number(int number) { printf("%6d\t", number); }

void nonprint(char* buffer, Flag_options flags, int char_count) {
  for (int i = 0; i < char_count; i++) {
    int symbol = buffer[i];
    if ((i == char_count - 1) && (buffer[i] == '\n')) {
      if (flags.show_endline) {
        printf("$%c", buffer[i]);
      } else {
        printf("%c", buffer[i]);
      }
    } else {
      if (symbol < 0) {
        symbol += 256;
      }
      if ((buffer[i] == '\t') && flags.show_tabs) {
        printf("^I");
      } else if ((buffer[i] == '\t') && !flags.show_tabs) {
        printf("\t");
      } else if (symbol >= 32) {
        if (symbol < 127) {
          printf("%c", symbol);
        } else if (symbol == 127) {
          printf("^?");
        } else {
          printf("M-");
          if (symbol >= 128 + 32) {
            if (symbol < 128 + 127) {
              printf("%c", symbol - 128);
            } else {
              printf("^?");
            }
          } else {
            printf("^%c", symbol - 64);
          }
        }
      } else {
        printf("^%c", buffer[i] + 64);
      }
    }
  }
}

void tabs_endline(char* buffer, Flag_options flags, int char_count) {
  for (int i = 0; i < char_count; i++) {
    if ((i == char_count - 1) && (flags.show_endline) &&
        (buffer[char_count - 1] == '\n')) {
      printf("$");
    }
    if (flags.show_tabs && (buffer[i] == '\t')) {
      printf("^I");
    } else {
      printf("%c", buffer[i]);
    }
  }
}