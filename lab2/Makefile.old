# $Id: Makefile,v 1.1 2019-04-03 17:34:13-07 - - $

WARNING     = -Wall -Wextra -Wpedantic -Wshadow -Wold-style-cast
COMPILECPP = g++ -std=gnu++17 -g -O0 ${WARNING}
MAKEDEPCPP = g++ -std=gnu++17 -MM
VALGRIND   = valgrind --leak-check=full --show-reachable=yes

MKFILE     = Makefile
DEPFILE    = Makefile.dep
SOURCES    = main.cpp string_set.cpp auxlib.cpp
HEADERS    = string_set.h
OBJECTS    = ${SOURCES:.cpp=.o}
EXECBIN    = oc
EXECFLAGS  = -l -y -D__OCLIBH__
SRCFILES   = ${SOURCES} ${MKFILE}
SMALLFILES = ${DEPFILE} foo.oc foo1.oh foo2.oh
CHECKINS   = ${SRCFILES} ${SMALLFILES}
LISTING    = Listing.ps
local = ./examples
exp = /afs/cats.ucsc.edu/courses/cmps104a-wm/Assignments/code/cppstrtok


all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${COMPILECPP} -o${EXECBIN} ${OBJECTS}

%.o : %.cpp
	${COMPILECPP} -c $<

ci :
	cid + ${CHECKINS}
	checksource ${CHECKINS}

clean :
	- rm ${OBJECTS} 

spotless : clean
	- rm  ${EXECBIN} *.str test.out *.oc *.oc.err *.oc.out *.log 

${DEPFILE} :
	${MAKEDEPCPP} ${SOURCES} >${DEPFILE}

dep :
	- rm ${DEPFILE}
	${MAKE} --no-print-directory ${DEPFILE}

include Makefile.dep

test : ${EXECBIN}
	${VALGRIND} ./${EXECBIN} ${exp}/foo.oc 1>test.out 2>&1

testflags : ${EXECBIN}
	${VALGRIND} ./${EXECBIN} ${EXECFLAGS} \
	${exp}/foo.oc 1>test.out 2>&1

misc.lis : ${DEPFILE} foo.oc foo1.oh foo2.oh
	catnv ${DEPFILE} foo.oc foo1.oh foo2.oh >misc.lis

lis : misc.lis test
	mkpspdf ${LISTING} ${SRCFILES} misc.lis test.out

again :
	${MAKE} spotless dep all test lis

