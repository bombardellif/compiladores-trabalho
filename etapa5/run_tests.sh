#!/bin/sh

filename=(
'test-cases/declarations_general_invalid.txt'
'test-cases/declarations_general_valid.txt'
'test-cases/empty.txt'
'test-cases/invalid1.txt'
'test-cases/invalid2.txt'
'test-cases/invalid3.txt'
'test-cases/sample.txt'
'test-cases/sample2.txt'
'test-cases/smallest.txt'
'test-cases/valid1.txt'
'test-cases/valid2.txt'
'test-cases/valid3.txt'
'test-cases/valid4.txt'
'test-cases/valid5.txt'
'test-cases/valid6.txt'
'test-cases/valid7.txt'
'test-cases/valid8.txt'
'test-cases/valid9.txt'
'test-cases/valid10.txt'
'test-cases/valid11.txt'
'test-cases/valid12.txt'
'test-cases/valid13.txt'
)

start=0
end=21

for i in $(eval echo "{$start..$end}");
do
  echo ================================
  echo $i = ${filename[$i]}
  cat ${filename[$i]}
  ./etapa5 ${filename[$i]}
done
