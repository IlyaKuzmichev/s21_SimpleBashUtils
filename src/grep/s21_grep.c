#include "s21_grep_options.h"

#define ERROR_1 "No such file or directory\n"
#define ERROR_2 "Illegal option\n"
#define ERROR_3 "No input arguments for s21_grep\n"
#define ERROR_4 "No input files\n"
#define ERROR_5 "No such file to read patterns\n"
#define ERROR_6 "Problem with memory allocation"

void print_error(int error_code);
void arg_processing(Flag_options* flags, int argc, char** argv,
                    char* search_templates);

int main(int argc, char** argv) {
  char* search_templates = (char*)malloc(4096 * sizeof(char));
  Flag_options flags = {0};

  arg_processing(&flags, argc, argv, search_templates);
  if (search_templates) {
    free(search_templates);
  }
  return 0;
}

void arg_processing(Flag_options* flags, int argc, char** argv,
                    char* search_templates) {
  int error_code;

  if (argc < 3) {
    error_code = 3;
    print_error(error_code);
  } else if (!search_templates) {
    error_code = 6;
    print_error(error_code);
  } else {
    *search_templates = '\0';
    error_code = get_options(argc, argv, flags, search_templates);
    if (error_code) {
      print_error(error_code);
    } else {
      if (!(flags->e_template || flags->f_fromfile)) {
        strcpy(search_templates, argv[optind]);
        optind++;
      }
      if (optind >= argc) {
        error_code = 4;
        print_error(error_code);
      }
      if (argc - optind < 2) {
        flags->h_hidefilenames = 1;
      }
      for (int i = optind; i < argc; i++) {
        FILE* file = fopen(argv[i], "r");
        if (file) {
          grep_flags(*flags, file, search_templates, argv[i]);
          fclose(file);
        } else {
          if (!flags->s_nofileerrors) {
            error_code = 1;
            print_error(error_code);
          }
        }
      }
    }
  }
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
    case 5:
      fprintf(stderr, ERROR_5);
      break;
    case 6:
      fprintf(stderr, ERROR_6);
      break;
    default:
      break;
  }
}