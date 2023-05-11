#include "s21_cat_options.h"

#define ERROR_1 "No such file or directory\n"
#define ERROR_2 "Illegal option\n"
#define ERROR_3 "No input arguments for s21_cat\n"
#define ERROR_4 "No input files"

void print_error(int error_code);
void cat_no_options(FILE* file);

int main(int argc, char** argv) {
  int error_code = 0;
  Flag_options flags = {0};

  if (argc == 1) {
    error_code = 3;
    print_error(error_code);
  } else {
    error_code = get_options(argc, argv, &flags);
    if (error_code) {
      print_error(error_code);
    } else {
      if (optind == argc) {
        error_code = 4;
        print_error(error_code);
      }
      for (int i = optind; i < argc; i++) {
        FILE* file = fopen(argv[i], "r");
        if (file && flags.flag_counter == 0) {
          cat_no_options(file);
          fclose(file);
        } else if (file && flags.flag_counter) {
          cat_flags(flags, file);
          fclose(file);
        } else {
          error_code = 1;
          print_error(error_code);
        }
      }
    }
  }

  return 0;
}

void print_error(int error_code) {
  switch (error_code) {
    case 1:
      fprintf(stderr, ERROR_1);
      break;
    case 2:
      fprintf(stderr, ERROR_2);
      break;
    case 3:
      fprintf(stderr, ERROR_3);
      break;
    case 4:
      fprintf(stderr, ERROR_4);
      break;
    default:
      break;
  }
}

void cat_no_options(FILE* file) {
  char* buffer = NULL;
  size_t length;
  ssize_t count;

  while ((count = getline(&buffer, &length, file)) != -1) {
    for (int i = 0; i < count; i++) {
      printf("%c", buffer[i]);
    }
  }
  if (buffer) {
    free(buffer);
  }
}