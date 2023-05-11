#include "s21_grep_options.h"

int get_options(int argc, char** argv, Flag_options* flags,
                char* search_templates) {
  int var;
  int error_code = 0;

  while (((var = getopt_long(argc, argv, "e:ivclnhsf:o", long_options, NULL)) !=
          -1) &&
         (!error_code)) {
    switch (var) {
      case 'e':
        add_template(search_templates);
        flags->e_template++;
        break;
      case 'i':
        flags->i_nocase++;
        break;
      case 'v':
        flags->v_inverter++;
        break;
      case 'c':
        flags->c_quantity++;
        break;
      case 'l':
        flags->l_onlyfilenames++;
        break;
      case 'n':
        flags->n_stringnumber++;
        break;
      case 'h':
        flags->h_hidefilenames++;
        break;
      case 's':
        flags->s_nofileerrors++;
        break;
      case 'f':
        error_code = read_template_from_file(search_templates);
        flags->f_fromfile++;
        break;
      case 'o':
        flags->o_onlytemplates++;
        break;
      default:
        error_code = 2;
        break;
    }
  }
  return error_code;
}

void add_template(char* search_templates) {
  if (*search_templates != '\0') {
    strcat(search_templates, "|");
    strcat(search_templates, optarg);
  } else {
    strcpy(search_templates, optarg);
  }
}

int read_template_from_file(char* search_templates) {
  int error_code = 0;
  FILE* fp = fopen(optarg, "r");
  if (fp) {
    char temp_string[1024];
    while (fgets(temp_string, 1024, fp)) {
      int length;
      if ((length = strlen(temp_string)) > 0) {
        if (temp_string[length - 1] == '\n') {
          temp_string[length - 1] = '\0';
        }
        if (*search_templates != '\0') {
          strcat(search_templates, "|");
          strcat(search_templates, temp_string);
        } else {
          strcpy(search_templates, temp_string);
        }
      }
    }
    fclose(fp);
  } else {
    error_code = 5;
  }
  return error_code;
}

void grep_flags(Flag_options flags, FILE* file, char* search_templates,
                char* filename) {
  int status;
  int cflags = REG_EXTENDED;
  regex_t reg;
  regmatch_t pmatch;
  char* get_string = NULL;
  size_t string_size;
  int exit_flag = 1;
  int quantity = 0, string_number = 1;

  if (flags.i_nocase) {
    cflags = REG_EXTENDED | REG_ICASE;
  }
  regcomp(&reg, search_templates, cflags);
  while ((getline(&get_string, &string_size, file) != -1) && exit_flag) {
    status = regexec(&reg, get_string, 1, &pmatch, 0);
    if (flags.v_inverter) {
      invert_status(&status);
    }
    if (status == 0) {
      quantity++;
      check_lc_flags(flags, &exit_flag, filename);
    }
    if (exit_flag && !flags.c_quantity && !status) {
      if (flags.o_onlytemplates && !flags.v_inverter) {
        int temp_counter = 1;
        char* temp_string = get_string;
        do {
          if (temp_counter) {
            print_prefix(flags, filename, string_number);
            temp_counter = 0;
          }
          for (int i = pmatch.rm_so; i < pmatch.rm_eo; i++) {
            printf("%c", temp_string[i]);
          }
          printf("\n");
          temp_string += pmatch.rm_eo + 1;
        } while ((status = regexec(&reg, temp_string, 1, &pmatch, 0)) == 0);
      } else {
        print_prefix(flags, filename, string_number);
        printf("%s", get_string);
        if (get_string[strlen(get_string) - 1] != '\n') {
          printf("\n");
        }
      }
    }
    string_number++;
  }
  if (exit_flag && flags.c_quantity) {
    print_prefix(flags, filename, 1);
    printf("%d\n", quantity);
  }
  if (get_string) {
    free(get_string);
  }
  regfree(&reg);
}

void check_lc_flags(Flag_options flags, int* exit_flag, char* filename) {
  if (flags.l_onlyfilenames) {
    *exit_flag = 0;
    if (flags.c_quantity) {
      if (!flags.h_hidefilenames) {
        printf("%s:1\n%s\n", filename, filename);
      } else {
        printf("1\n%s\n", filename);
      }
    } else {
      printf("%s\n", filename);
    }
  }
}

void print_prefix(Flag_options flags, char* filename, int string_number) {
  if (!flags.h_hidefilenames) {
    printf("%s:", filename);
  }
  if (flags.n_stringnumber && !flags.c_quantity) {
    printf("%d:", string_number);
  }
}

void invert_status(int* status) {
  if (*status == REG_NOMATCH) {
    *status = 0;
  } else if (*status == 0) {
    *status = REG_NOMATCH;
  }
}
