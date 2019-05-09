#!/bin/bash
for errfile in *.err
do
  if [ $(wc -m $errfile|cut -f1 -d' ') -gt 0 ]; then
    echo "** $errfile output:**"
    cat $errfile
    echo ''
  fi
done
