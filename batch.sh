#!/bin/bash

# ./batch.sh batch-sample | diff batch-sample.out -

if [ "$1" = "" ]; then
  echo "Problem name is empty"
  exit 1
fi

probname=$1
testcase=$2

if [ "$testcase" = "" ]; then
  testcase=-1
fi

pdir=$PWD
pfilepath="${pdir}/${probname}.cpp"
infilepath="${pdir}/${probname}.in"
`g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG ${pfilepath}`

body=""
t=0
res=""
while IFS='' read -r line || [[ -n "$line" ]]; do
  if [ "$line" = "~" ]; then
    if [ "$testcase" = -1 ] || [ "$t" = "$testcase" ]; then
      echo "${body}" | ${pdir}/a.out
    fi
    body=""
    t=$(( $t+1 ))
  else
    if [ "$body" != "" ]; then
      body="$body"$'\n'
    fi
    body="$body$line"
#    echo "$body"
  fi
done < "$infilepath"
