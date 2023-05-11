#ifndef S21_GREP_OPTIONS_H_
#define S21_GREP_OPTIONS_H_
#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static struct option const long_options[] = {{NULL, 0, NULL, 0}};

typedef struct flag_options {
  int e_template;
  int i_nocase;
  int v_inverter;
  int c_quantity;
  int l_onlyfilenames;
  int n_stringnumber;
  int h_hidefilenames;
  int s_nofileerrors;
  int f_fromfile;
  int o_onlytemplates;
} Flag_options;

int get_options(int argc, char** argv, Flag_options* flags,
                char* search_templates);
void grep_flags(Flag_options flags, FILE* file, char* search_templates,
                char* filename);
void check_lc_flags(Flag_options flags, int* exit_flag, char* filename);
void add_template(char* search_templates);
int read_template_from_file(char* search_templates);
void print_prefix(Flag_options flags, char* filename, int string_number);
void invert_status(int* status);

#endif  // S21_CAT_OPTIONS_H_