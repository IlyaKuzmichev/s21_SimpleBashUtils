#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a multy_testing=(
"for VAR 1_multy_pattern_test.txt"
"for VAR 1_multy_pattern_test.txt 2_multy_pattern_test.txt 1_multy_pattern_test.txt"
"-e a -e b -e c VAR 3_multy_test.txt"
"-e for -e ^int VAR 1_multy_pattern_test.txt 2_multy_pattern_test.txt 1_multy_pattern_test.txt"
"-e for -e ^int -f pattern_testing_1.txt VAR 1_multy_pattern_test.txt 2_multy_pattern_test.txt 1_multy_pattern_test.txt"
"-e for -e ^int -f pattern_testing_1.txt -f pattern_testing_2.txt VAR 1_multy_pattern_test.txt 2_multy_pattern_test.txt 1_multy_pattern_test.txt"
)

declare -a o_mac_testing=(
"for VAR 1_multy_pattern_test.txt"
"for VAR 1_multy_pattern_test.txt 2_multy_pattern_test.txt 1_multy_pattern_test.txt"
"-e a VAR 3_multy_test.txt"
"-e for VAR 1_multy_pattern_test.txt 2_multy_pattern_test.txt 1_multy_pattern_test.txt"
"-f pattern_testing_3.txt VAR 1_multy_pattern_test.txt 2_multy_pattern_test.txt 1_multy_pattern_test.txt"
)

declare -a unique_testing=(
"abc no_file.txt"
"abc -f no_file -ivclnhso no_file.txt"
"-e LEXEME -e INT -i -nh 2_multy_pattern_test.txt 1_multy_pattern_test.txt 2_multy_pattern_test.txt 1_multy_pattern_test.txt"
"-echar -eint -elexeme -v 2_multy_pattern_test.txt 1_multy_pattern_test.txt"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ../s21_grep $t > test_s21_grep.log
    grep $t > test_sys_grep.log
    DIFF_RES="$(diff -s test_s21_grep.log test_sys_grep.log)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_s21_grep.log and test_sys_grep.log are identical" ]
    then
      (( SUCCESS++ ))
        echo "\033[32mTEST\t$COUNTER:\tOK"
        echo "\033[0m grep $t"
    else
      (( FAIL++ ))
        echo "\033[31mTEST\t$COUNTER:\tFAIL"
        echo "\033[0m grep $t"
    fi
    rm test_s21_grep.log test_sys_grep.log
}

for var1 in i v c l n h s
do
  for i in "${multy_testing[@]}"
  do
    var="-$var1"
    testing $i
  done
done

for var1 in i v c l n h s
do
  for var2 in i v c l n h s
  do
    for i in "${multy_testing[@]}"
      do
        var="-$var1$var2"
        testing $i
      done
  done
done

for var1 in i v c l n h s
do
  for var2 in i v c l n h s
  do
    for var3 in i v c l n h s
    do
      for i in "${multy_testing[@]}"
      do
        var="-$var1$var2$var3"
        testing $i
      done   
    done
  done
done

for var1 in i v c l n h s o
do
  for var2 in i v c l n h s o
  do
    for var3 in i v c l n h s o
    do
      for i in "${o_mac_testing[@]}"
      do
        var="-$var1$var2$var3"
        testing $i
      done   
    done
  done
done

for i in "${unique_testing[@]}"
do
    var="-"
    testing $i
done

# tests for -o flag, relised in linux style"
# for var1 in i v c l n h s o 
# do
#   for var2 in i v c l n h s o
#   do
#     for i in "${multy_testing[@]}"
#       do
#         var="-$var1$var2"
#         testing $i
#       done
#   done
# done

echo "\033[31mFAIL: $FAIL\033[0m"
echo "\033[32mSUCCESS: $SUCCESS\033[0m"
echo "ALL: $COUNTER"