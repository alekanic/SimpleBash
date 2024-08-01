#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
RESULT=""

tests="test.txt"

# Без флагов

echo "Test 1: cat test.txt | s21_cat test.txt"
./s21_cat test.txt >> s21_log.txt
cat test.txt >> cat_log.txt
RESULT="$(diff -s s21_log.txt cat_log.txt)"
(( COUNTER++ ))
if [ "$RESULT" == "Files s21_log.txt and cat_log.txt are identical" ]
then
    (( SUCCESS++ ))
    echo "$SUCESS \033[32msuccess\033[0m"
else
    (( FAIL++ ))
    echo "$FAIL \033[31mfail\033[0m"
fi
rm s21_log.txt cat_log.txt

# С одним флагом

echo "Test 2: cat -b test.txt | s21_cat -b test.txt"
./s21_cat -b test.txt >> s21_log.txt
cat -b test.txt >> cat_log.txt
RESULT="$(diff -s s21_log.txt cat_log.txt)"
(( COUNTER++ ))
if [ "$RESULT" == "Files s21_log.txt and cat_log.txt are identical" ]
then
    (( SUCCESS++ ))
    echo "$SUCESS \033[32msuccess\033[0m"
else
    (( FAIL++ ))
    echo "$FAIL \033[31mfail\033[0m"
fi
rm s21_log.txt cat_log.txt

echo "Test 3: cat -n test.txt | s21_cat -n test.txt"
./s21_cat -n test.txt >> s21_log.txt
cat -n test.txt >> cat_log.txt
RESULT="$(diff -s s21_log.txt cat_log.txt)"
(( COUNTER++ ))
if [ "$RESULT" == "Files s21_log.txt and cat_log.txt are identical" ]
then
    (( SUCCESS++ ))
    echo "$SUCESS \033[32msuccess\033[0m"
else
    (( FAIL++ ))
    echo "$FAIL \033[31mfail\033[0m"
fi
rm s21_log.txt cat_log.txt

echo "Test 4: cat -s test.txt | s21_cat -s test.txt"
./s21_cat -s test.txt >> s21_log.txt
cat -s test.txt >> cat_log.txt
RESULT="$(diff -s s21_log.txt cat_log.txt)"
(( COUNTER++ ))
if [ "$RESULT" == "Files s21_log.txt and cat_log.txt are identical" ]
then
    (( SUCCESS++ ))
    echo "$SUCESS \033[32msuccess\033[0m"
else
    (( FAIL++ ))
    echo "$FAIL \033[31mfail\033[0m"
fi
rm s21_log.txt cat_log.txt

echo "Test 5: cat -e test.txt | s21_cat -e test.txt"
./s21_cat -e test.txt >> s21_log.txt
cat -e test.txt >> cat_log.txt
RESULT="$(diff -s s21_log.txt cat_log.txt)"
(( COUNTER++ ))
if [ "$RESULT" == "Files s21_log.txt and cat_log.txt are identical" ]
then
    (( SUCCESS++ ))
    echo "$SUCESS \033[32msuccess\033[0m"
else
    (( FAIL++ ))
    echo "$FAIL \033[31mfail\033[0m"
fi
rm s21_log.txt cat_log.txt

echo "Test 6: cat -t test.txt | s21_cat -t test.txt"
./s21_cat -t test.txt >> s21_log.txt
cat -t test.txt >> cat_log.txt
RESULT="$(diff -s s21_log.txt cat_log.txt)"
(( COUNTER++ ))
if [ "$RESULT" == "Files s21_log.txt and cat_log.txt are identical" ]
then
    (( SUCCESS++ ))
    echo "$SUCESS \033[32msuccess\033[0m"
else
    (( FAIL++ ))
    echo "$FAIL \033[31mfail\033[0m"
fi
rm s21_log.txt cat_log.txt

echo "Test 7: cat -v test.txt | s21_cat -v test.txt"
./s21_cat -v test.txt >> s21_log.txt
cat -v test.txt >> cat_log.txt
RESULT="$(diff -s s21_log.txt cat_log.txt)"
(( COUNTER++ ))
if [ "$RESULT" == "Files s21_log.txt and cat_log.txt are identical" ]
then
    (( SUCCESS++ ))
    echo "$SUCESS \033[32msuccess\033[0m"
else
    (( FAIL++ ))
    echo "$FAIL \033[31mfail\033[0m"
fi
rm s21_log.txt cat_log.txt

# С двумя флагами

echo "Test 8: cat -bb test.txt | s21_cat -bb test.txt"
./s21_cat -b test.txt >> s21_log.txt
cat -b test.txt >> cat_log.txt
RESULT="$(diff -s s21_log.txt cat_log.txt)"
(( COUNTER++ ))
if [ "$RESULT" == "Files s21_log.txt and cat_log.txt are identical" ]
then
    (( SUCCESS++ ))
    echo "$SUCESS \033[32msuccess\033[0m"
else
    (( FAIL++ ))
    echo "$FAIL \033[31mfail\033[0m"
fi
rm s21_log.txt cat_log.txt

echo "Test 9: cat -bn test.txt | s21_cat -bn test.txt"
./s21_cat -bn test.txt >> s21_log.txt
cat -bn test.txt >> cat_log.txt
RESULT="$(diff -s s21_log.txt cat_log.txt)"
(( COUNTER++ ))
if [ "$RESULT" == "Files s21_log.txt and cat_log.txt are identical" ]
then
    (( SUCCESS++ ))
    echo "$SUCESS \033[32msuccess\033[0m"
else
    (( FAIL++ ))
    echo "$FAIL \033[31mfail\033[0m"
fi
rm s21_log.txt cat_log.txt

echo "Test 10: cat -bs test.txt | s21_cat -bs test.txt"
./s21_cat -bs test.txt >> s21_log.txt
cat -bs test.txt >> cat_log.txt
RESULT="$(diff -s s21_log.txt cat_log.txt)"
(( COUNTER++ ))
if [ "$RESULT" == "Files s21_log.txt and cat_log.txt are identical" ]
then
    (( SUCCESS++ ))
    echo "$SUCESS \033[32msuccess\033[0m"
else
    (( FAIL++ ))
    echo "$FAIL \033[31mfail\033[0m"
fi
rm s21_log.txt cat_log.txt

echo "Test 11: cat -bt test.txt | s21_cat -bt test.txt"
./s21_cat -bt test.txt >> s21_log.txt
cat -bt test.txt >> cat_log.txt
RESULT="$(diff -s s21_log.txt cat_log.txt)"
(( COUNTER++ ))
if [ "$RESULT" == "Files s21_log.txt and cat_log.txt are identical" ]
then
    (( SUCCESS++ ))
    echo "$SUCESS \033[32msuccess\033[0m"
else
    (( FAIL++ ))
    echo "$FAIL \033[31mfail\033[0m"
fi
rm s21_log.txt cat_log.txt

echo "Test 12: cat -bv test.txt | s21_cat -bt test.txt"
./s21_cat -bv test.txt >> s21_log.txt
cat -bv test.txt >> cat_log.txt
RESULT="$(diff -s s21_log.txt cat_log.txt)"
(( COUNTER++ ))
if [ "$RESULT" == "Files s21_log.txt and cat_log.txt are identical" ]
then
    (( SUCCESS++ ))
    echo "$SUCESS \033[32msuccess\033[0m"
else
    (( FAIL++ ))
    echo "$FAIL \033[31mfail\033[0m"
fi
rm s21_log.txt cat_log.txt

echo "Test 13: cat -bv test.txt | s21_cat -bv test.txt"
./s21_cat -bv test.txt >> s21_log.txt
cat -bv test.txt >> cat_log.txt
RESULT="$(diff -s s21_log.txt cat_log.txt)"
(( COUNTER++ ))
if [ "$RESULT" == "Files s21_log.txt and cat_log.txt are identical" ]
then
    (( SUCCESS++ ))
    echo "$SUCESS \033[32msuccess\033[0m"
else
    (( FAIL++ ))
    echo "$FAIL \033[31mfail\033[0m"
fi
rm s21_log.txt cat_log.txt

echo "Test 14: cat -ns test.txt | s21_cat -ns test.txt"
./s21_cat -ns test.txt >> s21_log.txt
cat -ns test.txt >> cat_log.txt
RESULT="$(diff -s s21_log.txt cat_log.txt)"
(( COUNTER++ ))
if [ "$RESULT" == "Files s21_log.txt and cat_log.txt are identical" ]
then
    (( SUCCESS++ ))
    echo "$SUCESS \033[32msuccess\033[0m"
else
    (( FAIL++ ))
    echo "$FAIL \033[31mfail\033[0m"
fi
rm s21_log.txt cat_log.txt

echo "Test 15: cat -ne test.txt | s21_cat -ne test.txt"
./s21_cat -ne test.txt >> s21_log.txt
cat -ne test.txt >> cat_log.txt
RESULT="$(diff -s s21_log.txt cat_log.txt)"
(( COUNTER++ ))
if [ "$RESULT" == "Files s21_log.txt and cat_log.txt are identical" ]
then
    (( SUCCESS++ ))
    echo "$SUCESS \033[32msuccess\033[0m"
else
    (( FAIL++ ))
    echo "$FAIL \033[31mfail\033[0m"
fi
rm s21_log.txt cat_log.txt

echo "Test 16: cat -nt test.txt | s21_cat -nt test.txt"
./s21_cat -nt test.txt >> s21_log.txt
cat -nt test.txt >> cat_log.txt
RESULT="$(diff -s s21_log.txt cat_log.txt)"
(( COUNTER++ ))
if [ "$RESULT" == "Files s21_log.txt and cat_log.txt are identical" ]
then
    (( SUCCESS++ ))
    echo "$SUCESS \033[32msuccess\033[0m"
else
    (( FAIL++ ))
    echo "$FAIL \033[31mfail\033[0m"
fi
rm s21_log.txt cat_log.txt

echo "Test 17: cat -nv test.txt | s21_cat -nv test.txt"
./s21_cat -nv test.txt >> s21_log.txt
cat -nv test.txt >> cat_log.txt
RESULT="$(diff -s s21_log.txt cat_log.txt)"
(( COUNTER++ ))
if [ "$RESULT" == "Files s21_log.txt and cat_log.txt are identical" ]
then
    (( SUCCESS++ ))
    echo "$SUCESS \033[32msuccess\033[0m"
else
    (( FAIL++ ))
    echo "$FAIL \033[31mfail\033[0m"
fi
rm s21_log.txt cat_log.txt

echo "\033[31mFAIL: $FAIL\033[0m"
echo "\033[32mSUCCESS: $SUCCESS\033[0m"
echo "ALL: $COUNTER"


#be