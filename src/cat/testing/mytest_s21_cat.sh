#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a multy_testing=(
"VAR 1_multy_test.txt"
"VAR 2_multy_test.txt"
"VAR 3_multy_test.txt"
)

declare -a unique_testing=(
"-s no_file.txt"
"-benst no_file.txt"
"-bn 1_multy_test.txt 2_multy_test.txt 1_multy_test.txt 2_multy_test.txt 1_multy_test.txt"
"-benst 1_multy_test.txt 2_multy_test.txt 1_multy_test.txt 2_multy_test.txt 1_multy_test.txt"
"1_multy_test.txt 2_multy_test.txt 1_multy_test.txt 2_multy_test.txt 1_multy_test.txt"
"-bs 1_multy_test.txt 2_multy_test.txt 1_multy_test.txt 2_multy_test.txt 1_multy_test.txt"
"-ns 1_multy_test.txt 2_multy_test.txt 1_multy_test.txt 2_multy_test.txt 1_multy_test.txt"
"-benst 1_multy_test.txt 2_multy_test.txt 1_multy_test.txt 2_multy_test.txt 1_multy_test.txt"
"4_empty_test.txt"
"-benst 4_empty_test.txt"
"-v 4_empty_test.txt"
"4_empty_test.txt 4_empty_test.txt 4_empty_test.txt 4_empty_test.txt"
"-b -e -n -t -s 1_multy_test.txt 2_multy_test.txt no_file.txt 3_multy_test.txt 4_empty_test.txt"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ../s21_cat $t > test_s21_cat.log
    cat $t > test_sys_cat.log
    DIFF_RES="$(diff -s test_s21_cat.log test_sys_cat.log)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_s21_cat.log and test_sys_cat.log are identical" ]
    then
      (( SUCCESS++ ))
        echo "\033[32mTEST\t$COUNTER:\tOK"
        echo "\033[0m cat $t"
    else
      (( FAIL++ ))
        echo "\033[31mTEST\t$COUNTER:\tFAIL"
        echo "\033[0m cat $t"
    fi
    rm test_s21_cat.log test_sys_cat.log
}

for var1 in b e n s t
do
  for i in "${multy_testing[@]}"
  do
    var="-$var1"
    testing $i
  done
done

for var1 in b e n s t
do
  for var2 in b e n s t
  do
    for i in "${multy_testing[@]}"
      do
        var="-$var1$var2"
        testing $i
      done
  done
done

for var1 in b e n s t
do
  for var2 in b e n s t
  do
    for var3 in b e n s t
    do
      for i in "${multy_testing[@]}"
      do
        var="-$var1 -$var2 -$var3"
        testing $i
      done   
    done
  done
done

for var1 in b e n s t
do
  for var2 in b e n s t
   do
    for var3 in b e n s t
    do
      for var4 in b e n s t
      do
        for i in "${multy_testing[@]}"
        do
          var="-$var1$var2$var3$var4"
          testing $i
        done
      done
    done
  done
done

for i in "${unique_testing[@]}"
do
    var="-"
    testing $i
done

echo "\033[31mFAIL: $FAIL\033[0m"
echo "\033[32mSUCCESS: $SUCCESS\033[0m"
echo "ALL: $COUNTER"