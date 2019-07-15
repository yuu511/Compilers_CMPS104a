import glob
import os.path

TESTDIR = "./test"
files = glob.glob(os.path.join(TESTDIR,"*.oc"))
VERBOSE = 0

def test_non_9x(names):
  for f in names:
    print(os.path.basename(f))

def test_9x(names):
  for f in names:
    print(os.path.basename(f))


if __name__ == '__main__':
  BASEDIR = os.getcwd()
  os.chdir(TESTDIR)
  non_9x = []
  error_9x = []
  for f in files:
    if os.path.basename(f).startswith("9"):
      error_9x.append(f)
    else:
      non_9x.append(f)
  test_non_9x(sorted(non_9x))
  test_9x(sorted(error_9x))
  os.chdir(BASEDIR)
