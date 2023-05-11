TARGET1 = ./s21_grep
# TARGET2 = 
# TARGET3 = 


.PHONY: all build rebuild check cppcheck test clean s21_grep s21_grep_options

SRCS1 = s21_grep.c
SRCS2 = s21_grep_options.c
# SRCS3 = 
# SRCS4 = 
# SRCS5 = 
# SRCS6 = 
# SRCS7 = 
# SRCS8 = 
# SRCS9 = 

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
	clang-format -n $(SOURCES) *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem $(SOURCES) *.h

# memcheck:
# 	leaks -atExit -- $(TARGET1)

clean:
	rm -rf $(TARGETS) *.o
