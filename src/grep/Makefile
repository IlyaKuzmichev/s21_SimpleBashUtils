TARGET1 = ./s21_grep

.PHONY: all build rebuild check cppcheck test clean s21_grep s21_grep_options

SRCS1 = s21_grep.c
SRCS2 = s21_grep_options.c

CC = gcc
CFLAGS = -c -Wall -Wextra -Werror 	#keys for object files
FFLAGS = -Wall -Wextra -Werror 		#keys for fast build

SOURCES = $(SRCS1) $(SRCS2) 
TARGETS = $(TARGET1)
OBJECTS = $(SOURCES:.c=.o)

all: s21_grep

.c.o:
	$(CC) $(CFLAGS) $< -o $@

s21_grep: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

build:
	$(CC) $(FFLAGS) -o $(TARGET1) $(SOURCES)
	

rebuild: clean all

stylecheck:
	clang-format -style=Google -n $(SOURCES) *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem $(SOURCES) *.h

clean:
	@rm -rf $(TARGETS) *.o
