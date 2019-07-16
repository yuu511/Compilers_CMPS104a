#!/usr/bin/env python3
import glob
import os.path
import subprocess

EXECUTABLE = "../oc"
EXECUTABLE_ARGS_AST = "-@ast"
EXECUTABLE_ARGS_LEXYACC = "-ly"
files = glob.glob("*.oc")
VERBOSE = 0

def test_non_9x(names):
  for f in names:
    subprocess.run([EXECUTABLE,f],stderr=subprocess.STDOUT)

def test_9x(names):
  pass  

if __name__ == '__main__':
  non_9x = []
  error_9x = []
  for f in files:
    if os.path.basename(f).startswith("9"):
      error_9x.append(f)
    else:
      non_9x.append(f)
  test_non_9x(sorted(non_9x))
  test_9x(sorted(error_9x))
