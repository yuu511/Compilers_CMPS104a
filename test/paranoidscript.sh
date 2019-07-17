#!/bin/bash
comparedir="../../lab3/examples/"
echo "astfile diffs:"
for astfile in *.ast
do
  diff $astfile $comparedir/$astfile >> diffast.err
  check=$?
  if [ "$check" -gt 0 ] 
  then
    echo $astfile
  fi
done

echo "tokfile diffs:"
for tokfile in *.tok
do
  diff $tokfile $comparedir/$tokfile >> difftok.err
  check=$?
  if [ "$check" -gt 0 ] 
  then
    echo $tokfile
  fi
done
