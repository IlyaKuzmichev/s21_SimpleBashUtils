TARGET1 = ./s21_cat

.PHONY: all build rebuild check cppcheck test clean s21_cat s21_cat_options

SRCS1 = s21_cat.c
SRCS2 = s21_cat_options.c


CC = gcc
CFLAGS = -c -Wall -Wextra -Werror 	#keys for object files
FFLAGS = -Wall -Wextra -Werror 		#keys for fast build

SOURCES = $(SRCS1) $(SRCS2) 
TARGETS = $(TARGET1)
OBJECTS = $(SOURCES:.c=.o)

all: s21_cat

.c.o:
	$(CC) $(CFLAGS) $< -o $@

s21_cat: $(OBJECTS)
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
