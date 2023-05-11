#ifndef S21_CAT_OPTIONS_H_
#define S21_CAT_OPTIONS_H_
#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct option const long_options[] = {
    {"number-nonblank", no_argument, NULL, 'b'},
    {"number", no_argument, NULL, 'n'},
    {"squeeze-blank", no_argument, NULL, 's'},
    {"show-nonprinting", no_argument, NULL, 'v'},
    {NULL, 0, NULL, 0}};

typedef struct flag_options {
  int number_nonblank;
  int show_endline;
  int number;
  int squeeze_blank;
  int show_tabs;
  int show_nonprint;
  int flag_counter;
} Flag_options;

int get_options(int argc, char** argv, Flag_options* flags);
void cat_flags(Flag_options flags, FILE* file);
void printline_number(int number);
void nonprint(char* buffer, Flag_options flags, int char_count);
void tabs_endline(char* buffer, Flag_options flags, int char_count);

#endif  // S21_CAT_OPTIONS_H_