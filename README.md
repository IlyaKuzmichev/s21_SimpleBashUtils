# Simple Bash Utils. 

### Own implementation and Development of Bash text utilities: cat, grep.

| ![1_1](images/cat.jpeg) |
| :---------------------: |


## Contents

1. [Task](#task) \
   1.1. [Part 1](#part-1-working-with-the-cat-utility)  
   1.2. [Part 2](#part-2-working-with-grep-utility)  
   1.3. [Part 3](#part-3-bonus-implementation-of-some-grep-utility-flags)  
   1.4. [Part 4](#part-4-bonus-implementation-of-grep-utility-flag-combinations)
2. [Implementation](#implementation) 

## Task

- The programs must be developed in C language of C11 standard using gcc compiler.
- The program code of the cat and grep must be located on the develop branch in the src/cat/ and src/grep/ folders, respectively  
- Do not use outdated and legacy language constructions and library functions. Pay attention to the legacy and obsolete marks in the official documentation on the language and the libraries used. Use the POSIX.1-2017 standard.
- When writing code it is necessary to follow the Google style
- The programs must be executable files with command line arguments
- The programs must be built with Makefile with appropriate targets: s21_cat, s21_grep
- If third-party libraries are used, there must be build scripts in makefile to connect/load them
- Integration tests must cover all flag variants and input values, based on a comparison with the behavior of real Bash utilities 
- The programs must be developed according to the principles of structured programming
- Code duplication must be avoided, common modules must be reused between the utilities. Common modules can be moved to a separate folder src/common
- You can use standard and non-standard C libraries, or you can use your own developed libraries from other projects
- The statement of the message in the case of an error does not matter
- Input via stdin is not required to be supported

### Part 1. Working with the cat utility

You need to develop a cat utility:
- Support of next flags (including GNU versions):
  | No. | Options                                                        | Description                                  |
  | --- | -------------------------------------------------------------- | -------------------------------------------- |
  | 1   | -b (GNU: --number-nonblank)                                    | numbers only non-empty lines                 |
  | 2   | -e implies -v (GNU only: -E the same, but without implying -v) | but also display end-of-line characters as $ |
  | 3   | -n (GNU: --number)                                             | number all output lines                      |
  | 4   | -s (GNU: --squeeze-blank)                                      | squeeze multiple adjacent blank lines        |
  | 5   | -t implies -v (GNU: -T the same, but without implying -v)      | but also display tabs as ^I                  |
- The source, header, and build files must be placed in the src/cat/ directory
- The resulting executable file must be placed in the directory src/cat/ and named s21_cat

### Part 2. Working with grep utility

### grep Options

  - all grep flags
    | No. | Options | Description                                                    |
    | --- | ------- | -------------------------------------------------------------- |
    | 1   | -e      | pattern                                                        |
    | 2   | -i      | Ignore uppercase vs. lowercase.                                |
    | 3   | -v      | Invert match.                                                  |
    | 4   | -c      | Output count of matching lines only.                           |
    | 5   | -l      | Output matching files only.                                    |
    | 6   | -n      | Precede each matching line with a line number.                 |
    | 7   | -h      | Output matching lines without preceding them by file names.    |
    | 8   | -s      | Suppress error messages about nonexistent or unreadable files. |
    | 9   | -f file | Take regexes from a file.                                      |
    | 10  | -o      | Output the matched parts of a matching line.                   |

You need to develop the grep utility:
- Support of the following flags: `-e`, `-i`, `-v`, `-c`, `-l`, `-n`
- Only pcre or regex libraries can be used for regular expressions
- The source, header and make files must be placed in the src/grep/ directory
- The resulting executable file must be placed in the directory src/grep/ and named s21_grep

### Part 3. Bonus. Implementation of some grep utility flags

Bonus assignment for extra points. You need to develop the grep utility:
- Support of all flags, including: `-h`, `-s`, `-f`, `-o`
- Only pcre or regex libraries can be used for regular expressions
- The source, header and make files must be placed in the src/grep/ directory
- The resulting executable file must be placed in the directory src/grep/ and named s21_grep

### Part 4. Bonus. Implementation of grep utility flag combinations

Bonus assignment for extra points. You need to develop the grep utility:
- Support of all flags, including their _pair_ combinations (e.g. `-iv`, `-in`)
- Only pcre or regex libraries can be used for regular expressions
- The source, header and make files must be placed in the src/grep/ directory
- The resulting executable file must be placed in the directory src/grep/ and named s21_grep

## Implementation

  - The program was developed and implemented on MacOs Big Sur Version 11.6.6 and repeats the behavior of the cat and grep utilities on zsh 5.8 (x86_64-apple-darwin20.0) with minor modifications and my own vision of the correct implementation.
  - You may run the tests for each utility if you change directory to `/src/cat/testing` or `/src/grep/testing` and run the script with `sh` command for better overview.
  ```zsh
  sh mytest_s21_cat.sh
  sh mytest_s21_grep.sh
  ```
  - Testing with my integration tests on Linux will not display the correct result due to the difference in the implementation of standard utilities and the logic in the bash script
  - For style tests and static code analysis, the `clang-format` and `cppcheck` utilities must be installed, respectively.
