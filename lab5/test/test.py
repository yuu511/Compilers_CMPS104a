#!/usr/bin/env python3
import glob
import os.path
import subprocess
import sys

EXECUTABLE = "../oc"
EXECUTABLE_ARGS_AST = "-@ast"
EXECUTABLE_ARGS_LEXYACC = "-ly"
VALGRIND = "/usr/bin/valgrind"
files = glob.glob("*.oc")

def test_non_9x(names):
  for f in names:
    outfile = open(f+".out","w")
    errfile = open(f+".err","w")
    memfile = open(f+".valgrind","w")
    result = subprocess.run([EXECUTABLE,f],stderr=errfile,stdout=outfile)
    if (result.returncode != 0):
      sys.stderr.write("%s: ERROR: non-zero exit\n" % f)
    else:
      memcheck = subprocess.run([VALGRIND,EXECUTABLE,f],stderr=memfile)
    outfile.close()
    errfile.close()
    memfile.close()

def test_9x(names):
  for f in names:
    memfile = open(f+".valgrind","w")
    memcheck = subprocess.run([VALGRIND,EXECUTABLE,f],stderr=memfile)
    memfile.close()

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
