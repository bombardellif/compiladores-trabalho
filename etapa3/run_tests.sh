#!/bin/sh

filename=(
'sample.txt'
'sample2.txt'
'declaration_functions_valid.txt'
'declaration_variables_valid.txt'
'declaration_vectors_valid.txt'
'declaration_variables_invalid.txt'
'invalid_input.txt'
)

start=0
end=6

for i in $(eval echo "{$start..$end}");
do
  echo $i
  # Create result directory if not existent yet
  if [ ! -d "./test-cases/output" ]; then
    #echo "mkdir $i"
    mkdir $i
  fi
  # Run 1
  ./etapa3 ./test-cases/${filename[$i]} ./test-cases/output/${filename[$i]}
  # Run 2
  ./etapa3 ./test-cases/output/${filename[$i]} ./test-cases/output/${filename[$i]}_
done
