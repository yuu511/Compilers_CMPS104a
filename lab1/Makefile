# $Id: Makefile,v 1.1 2019-04-03 17:34:13-07 - - $

WARNING     = -Wall -Wextra -Wpedantic -Wshadow -Wold-style-cast
COMPILECPP = g++ -std=gnu++17 -g -O0 ${WARNING}
MAKEDEPCPP = g++ -std=gnu++17 -MM
VALGRIND   = valgrind --leak-check=full --show-reachable=yes

MKFILE     = Makefile
DEPFILE    = Makefile.dep
SOURCES    = cppstrtok.cpp
OBJECTS    = ${SOURCES:.cpp=.o}
EXECBIN    = cppstrtok
SRCFILES   = ${SOURCES} ${MKFILE}
SMALLFILES = ${DEPFILE} foo.oc foo1.oh foo2.oh
CHECKINS   = ${SRCFILES} ${SMALLFILES}
LISTING    = Listing.ps

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
	- rm ${EXECBIN} ${LISTING} ${LISTING:.ps=.pdf} ${DEPFILE} \
	     test.out misc.lis

${DEPFILE} :
	${MAKEDEPCPP} ${SOURCES} >${DEPFILE}

dep :
	- rm ${DEPFILE}
	${MAKE} --no-print-directory ${DEPFILE}

include Makefile.dep

test : ${EXECBIN}
	${VALGRIND} ${EXECBIN} foo.oc 1>test.out 2>&1

misc.lis : ${DEPFILE} foo.oc foo1.oh foo2.oh
	catnv ${DEPFILE} foo.oc foo1.oh foo2.oh >misc.lis

lis : misc.lis test
	mkpspdf ${LISTING} ${SRCFILES} misc.lis test.out

again :
	${MAKE} spotless dep all test lis

